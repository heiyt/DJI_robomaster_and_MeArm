package com.example.bysj;

import android.Manifest;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.LocationManager;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import pub.devrel.easypermissions.EasyPermissions;

//蓝牙对象的几个回调函数
interface ECBluetoothAdapterStateChangeCallback {   //蓝牙适配器改变之后的回调函数
    void callback(boolean ok, int errCode, String errMsg);
}
interface ECBluetoothDeviceFoundCallback {  //蓝牙设别找到之后的回调函数
    void callback(String id, String name, String mac, int rssi);
}
interface ECBLEConnectionStateChangeCallback {  //蓝牙连接状态改变之后的回调函数
    void callback(boolean ok, int errCode, String errMsg);
}
interface ECBLECharacteristicValueChangeCallback {  //改变蓝牙发送的值的回调函数
    void callback(String str, String strHex);
}
public class BLE {
    //中文的转化之类的
    private static final String ECBLEChineseTypeUTF8 = "utf8";
    private static final String ECBLEChineseTypeGBK = "gbk";
    private static String ecBLEChineseType = ECBLEChineseTypeGBK;
    static void setChineseTypeUTF8() {
        ecBLEChineseType = ECBLEChineseTypeUTF8;
    }
    static void setChineseTypeGBK() {
        ecBLEChineseType = ECBLEChineseTypeGBK;
    }
    //蓝牙适配器对象初始化，回调函数对象初始化
    private static BluetoothAdapter bluetoothAdapter = null;
    private static ECBluetoothAdapterStateChangeCallback ecBluetoothAdapterStateChangeCallback = (boolean ok, int errCode, String errMsg) -> {
    };
    static void onBluetoothAdapterStateChange(ECBluetoothAdapterStateChangeCallback cb) {
        ecBluetoothAdapterStateChangeCallback = cb;
    }
    static void openBluetoothAdapter(AppCompatActivity ctx) {
        //初始化蓝牙适配器
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();//安卓12用这个也没问题
        if (bluetoothAdapter == null) {
            ecBluetoothAdapterStateChangeCallback.callback(false, 10000, "此设备不支持蓝牙");
            return;
        }
        if (!bluetoothAdapter.isEnabled()) {
            ecBluetoothAdapterStateChangeCallback.callback(false, 10001, "请打开设备蓝牙开关");
            return;
        }
        //初始化定位
        LocationManager locationManager = (LocationManager) ctx.getSystemService(Context.LOCATION_SERVICE);
        boolean gps = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        boolean network = locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
        if (!(gps || network)) {
            ecBluetoothAdapterStateChangeCallback.callback(false, 10002, "请打开设备定位开关");
            return;
        }
        //请求蓝牙方面的权限
        String[] perms_loc = new String[]{
                Manifest.permission.BLUETOOTH_SCAN,
                Manifest.permission.BLUETOOTH_ADVERTISE,
                Manifest.permission.BLUETOOTH_CONNECT,
                Manifest.permission.BLUETOOTH,
        };
        if (!EasyPermissions.hasPermissions(ctx, perms_loc)) {
            EasyPermissions.requestPermissions(ctx, "请打开应用的蓝牙权限，允许应用使用蓝牙连接附近的设备", 0xECB002, perms_loc);
            return;
        }
        //请求定位方面的权限
        String[] perms_ble = new String[]{
                Manifest.permission.ACCESS_FINE_LOCATION,
                Manifest.permission.ACCESS_COARSE_LOCATION
        };
        if (!EasyPermissions.hasPermissions(ctx, perms_ble)) {
            EasyPermissions.requestPermissions(ctx, "请打开应用的定位权限", 0xECB001, perms_ble);
            return;
        }
        ecBluetoothAdapterStateChangeCallback.callback(true, 0, "");
        //在 Android 中，当你与蓝牙低功耗（BLE）设备建立连接后，会得到一个 BluetoothGatt 对象，
        // 通过这个对象你可以进行数据交换、读写操作等。
        // 当不再需要与设备通信时，可以调用 close() 方法来关闭连接。
        if (bluetoothGatt != null) {
            if (ActivityCompat.checkSelfPermission(ctx, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                return;
            }
            bluetoothGatt.close();
        }
    }
    //检查权限被授予的情况
    static void onPermissionsGranted(AppCompatActivity ctx, int requestCode, @NonNull List<String> perms) {
        //获取定位权限失败 or 获取蓝牙连接附近设备的权限失败
        if (requestCode == 0xECB001 || requestCode == 0xECB002) {
            openBluetoothAdapter(ctx);
        }
    }
    //处理权限未未授予的情况
    static void onPermissionsDenied(int requestCode, @NonNull List<String> perms) {
        if (requestCode == 0xECB001) {//获取定位权限失败
            ecBluetoothAdapterStateChangeCallback.callback(false, 10003, "请打开设备定位权限");
        }
        if (requestCode == 0xECB002) {//获取蓝牙连接附近设备的权限失败
            ecBluetoothAdapterStateChangeCallback.callback(false, 10004, "请打开设备蓝牙权限");
        }
    }

    //搜索到的设备的列表
    private static final List<BluetoothDevice> deviceList = new ArrayList<>();
    private static boolean scanFlag = false;
    private static ECBluetoothDeviceFoundCallback ecBluetoothDeviceFoundCallback = (String id, String name, String mac, int rssi) -> {
    };
    static void onBluetoothDeviceFound(ECBluetoothDeviceFoundCallback cb) {
        ecBluetoothDeviceFoundCallback = cb;
    }
    //搜索的函数
    private static final BluetoothAdapter.LeScanCallback leScanCallback = (BluetoothDevice bluetoothDevice, int rssi, byte[] bytes) -> {
        try {
            @SuppressLint("MissingPermission")
            String name = bluetoothDevice.getName();
            if (name == null || name.isEmpty()) return;
            String mac = bluetoothDevice.getAddress();
            if (mac == null || mac.isEmpty()) return;
            mac = mac.replace(":", "");
            boolean isExist = false;
            for (BluetoothDevice tempDevice : deviceList) {
                if (tempDevice.getAddress().replace(":", "").equals(mac)) {
                    isExist = true;
                    break;
                }
            }
            if (!isExist) {
                deviceList.add(bluetoothDevice);
            }
            ecBluetoothDeviceFoundCallback.callback(mac, name, mac, rssi);
        } catch (Throwable e) {
            Log.e("LeScanCallback", "Throwable");
        }
    };
    //开始搜索
    static void startBluetoothDevicesDiscovery(Context ctx) {
        if (!scanFlag) {
            if (ActivityCompat.checkSelfPermission(ctx, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
                return;
            }
            if (bluetoothAdapter != null) {
                bluetoothAdapter.startLeScan(leScanCallback);
                scanFlag = true;
            }
        }
    }
    //停止搜索
    static void stopBluetoothDevicesDiscovery(Context ctx) {
        if (scanFlag) {
            if (ActivityCompat.checkSelfPermission(ctx, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
                return;
            }
            if (bluetoothAdapter != null) {
                bluetoothAdapter.stopLeScan(leScanCallback);
                scanFlag = false;
            }
        }
    }

    //进入发送数据页面之后干的事情
    private static BluetoothGatt bluetoothGatt = null;
    private static boolean connectFlag = false;
    private static int reconnectTime = 0;
    private static ECBLEConnectionStateChangeCallback ecBLEConnectionStateChangeCallback = (boolean ok, int errCode, String errMsg) -> {
    };
    static void onBLEConnectionStateChange(ECBLEConnectionStateChangeCallback cb) {
        ecBLEConnectionStateChangeCallback = cb;
    }
    private static ECBLEConnectionStateChangeCallback connectCallback = (boolean ok, int errCode, String errMsg) -> {
    };
    private static ECBLECharacteristicValueChangeCallback ecBLECharacteristicValueChangeCallback = (String str, String hexStr) -> {
    };
    static void onBLECharacteristicValueChange(ECBLECharacteristicValueChangeCallback cb) {
        ecBLECharacteristicValueChangeCallback = cb;
    }
    private static final String ecCharacteristicWriteUUID = "0000ffe2-0000-1000-8000-00805f9b34fb";
    private static final String ecCharacteristicNotifyUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";
    private static BluetoothGattCharacteristic ecCharacteristicWrite;
    //蓝牙gatt的各种回调
    private static final BluetoothGattCallback bluetoothGattCallback = new BluetoothGattCallback() {
        @SuppressLint("MissingPermission")
        //连接状态切换的时候，调用这个回调函数
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            super.onConnectionStateChange(gatt, status, newState);
            if (status != BluetoothGatt.GATT_SUCCESS) {
                gatt.close();
                if (connectFlag) {
                    ecBLEConnectionStateChangeCallback.callback(false, 10000, "onConnectionStateChange:" + status + "|" + newState);
                } else {
                    connectCallback.callback(false, 10000, "onConnectionStateChange:" + status + "|" + newState);
                }
                connectFlag = false;
                return;
            }
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                gatt.discoverServices();
                connectCallback.callback(true, 0, "");
                ecBLEConnectionStateChangeCallback.callback(true, 0, "");
                connectFlag = true;
                return;
            }
            if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                gatt.close();
                if (connectFlag) {
                    ecBLEConnectionStateChangeCallback.callback(false, 0, "");
                } else {
                    connectCallback.callback(false, 0, "");
                }
                connectFlag = false;
            }
        }
        //发现蓝牙时调用这个回调函数，一个一个装进列表,300ms刷新一次列表
        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            super.onServicesDiscovered(gatt, status);
            bluetoothGatt = gatt;
            List<BluetoothGattService> bluetoothGattServices = bluetoothGatt.getServices();
            new Thread(() -> {
                try {
                    for (BluetoothGattService service : bluetoothGattServices) {
                        List<BluetoothGattCharacteristic> listGattCharacteristic = service.getCharacteristics();
                        for (BluetoothGattCharacteristic characteristic : listGattCharacteristic) {
                            if (characteristic.getUuid().toString().equals(ecCharacteristicNotifyUUID)) {
                                notifyBLECharacteristicValueChange(characteristic);
                            }
                            if (characteristic.getUuid().toString().equals(ecCharacteristicWriteUUID)) {
                                ecCharacteristicWrite = characteristic;
                            }
                        }
                    }
                } catch (Throwable ignored) {
                }
            }).start();
            new Thread(() -> {
                try {
                    Thread.sleep(300);
                    setMtu();
                } catch (Throwable ignored) {
                }
            }).start();
        }
        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
            super.onCharacteristicChanged(gatt, characteristic);
            byte[] bytes = characteristic.getValue();
            if (bytes != null) {
                String str = "";
                if (Objects.equals(ecBLEChineseType, ECBLEChineseTypeGBK)) {
                    try {
                        str = new String(bytes, "GBK");
                    } catch (Throwable ignored) {
                    }
                } else {
                    str = new String(bytes);
                }
                String strHex = bytesToHexString(bytes);
                ecBLECharacteristicValueChangeCallback.callback(str, strHex);
            }
        }
        @Override
        public void onMtuChanged(BluetoothGatt gatt, int mtu, int status) {
            super.onMtuChanged(gatt, mtu, status);
            if (BluetoothGatt.GATT_SUCCESS == status) {
                Log.e("BLEService", "onMtuChanged success MTU = " + mtu);
            } else {
                Log.e("BLEService", "onMtuChanged fail ");
            }
        }
    };
    @SuppressLint("MissingPermission")
    private static void notifyBLECharacteristicValueChange(BluetoothGattCharacteristic characteristic) {
        boolean res = bluetoothGatt.setCharacteristicNotification(characteristic, true);
        if (!res) {
            return;
        }
        for (BluetoothGattDescriptor dp : characteristic.getDescriptors()) {
            dp.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
            bluetoothGatt.writeDescriptor(dp);
        }
    }
    @SuppressLint("MissingPermission")
    private static void setMtu() {
        bluetoothGatt.requestMtu(64);
    }
    @SuppressLint("MissingPermission")
    static void closeBLEConnection() {
        if (bluetoothGatt != null) {
            bluetoothGatt.disconnect();
        };
    }
    private static void _createBLEConnection(Context ctx, String id) {
        if (ActivityCompat.checkSelfPermission(ctx, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
            connectCallback.callback(false, 10001, "permission error");
            return;
        }
        if (bluetoothGatt != null) {
            bluetoothGatt.close();
        }
        for (BluetoothDevice tempDevice : deviceList) {
            if (tempDevice.getAddress().replace(":", "").equals(id)) {
                bluetoothGatt = tempDevice.connectGatt(ctx, false, bluetoothGattCallback);
                return;
            }
        }
        connectCallback.callback(false, 10002, "id error");
    }
    static void createBLEConnection(Context ctx, String id) {
        reconnectTime = 0;
        connectCallback = (boolean ok, int errCode, String errMsg) -> {
            Log.e("connectCallback", ok + "|" + errCode + "|" + errMsg);
            if (!ok) {
                reconnectTime = reconnectTime + 1;
                if (reconnectTime > 4) {
                    reconnectTime = 0;
                    ecBLEConnectionStateChangeCallback.callback(false, errCode, errMsg);
                } else {
                    new Thread(() -> {
                        try {
                            Thread.sleep(300);
                            _createBLEConnection(ctx, id);
                        } catch (Throwable ignored) {
                        }
                    }).start();
                }
            }
        };
        _createBLEConnection(ctx, id);
    }
    @SuppressLint("MissingPermission")
    static void writeBLECharacteristicValue(String data, boolean isHex) {
        byte[] byteArray;
        if (isHex) {
            byteArray = hexStrToBytes(data);
        } else {
            if (Objects.equals(ecBLEChineseType, ECBLEChineseTypeGBK)) {
                try {
                    byteArray = data.getBytes("GBK");
                } catch (Throwable e) {
                    return;
                }
            } else {
                byteArray = data.getBytes();
            }
        }
        if (ecCharacteristicWrite != null) {
            ecCharacteristicWrite.setValue(byteArray);
            //设置回复形式
            ecCharacteristicWrite.setWriteType(BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE);
            //开始写数据
            if (bluetoothGatt != null) {
                bluetoothGatt.writeCharacteristic(ecCharacteristicWrite);
            }
        }
    }
    @NonNull
    private static String bytesToHexString(byte[] bytes) {
        if (bytes == null) return "";
        StringBuilder str = new StringBuilder();
        for (byte b : bytes) {
            str.append(String.format("%02X", b));
        }
        return str.toString();
    }
    @NonNull
    private static byte[] hexStrToBytes(@NonNull String hexString) {
        int len = hexString.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(hexString.charAt(i), 16) << 4)
                    + Character.digit(hexString.charAt(i + 1), 16));
        }
        return data;
    }
    @NonNull
    private static String getBluetoothName(byte[] bytes) {
        for (int i = 0; i < 62; i++) {
            if (i >= bytes.length) return "";
            int tempLen = bytes[i];
            int tempType = bytes[i + 1];
            if ((tempLen == 0) || (tempLen > 30)) {
                return "";
            }
            if ((tempType == 9) || (tempType == 8)) {
                byte[] nameBytes = new byte[tempLen - 1];
                System.arraycopy(bytes, i + 2, nameBytes, 0, tempLen - 1);
                return new String(nameBytes);
            }
            i += tempLen;
        }
        return "";
    }

}
