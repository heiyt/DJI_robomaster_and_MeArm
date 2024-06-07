package com.example.bysj;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import com.shy.rockerview.MyRockerView;

public class BLE_ControlActivity extends AppCompatActivity{
    //控制器
    MyRockerView mRockerViewXY;
    MyRockerView mRockerViewXY_Arm;
    String directionXY = "";
    String directionXY_Arm = "";
    int levelXY = 0;
    int levelXY_Arm = 0;
    int f = 0;
    int a = 0;
    boolean isRunning = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_device);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.activity_device), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        control_ui_Init();
        // 蓝牙断开连接
        BLE.onBLEConnectionStateChange((boolean ok, int errCode, String errMsg)-> runOnUiThread(()->{
            showAlert("蓝牙断开连接",()->{});
        }));
        // 接收到数据
        BLE.onBLECharacteristicValueChange((String str, String strHex)-> runOnUiThread(()->{
            if (strHex.equals("08")) {
                showAlert("遇到障碍物",()->{});
            }
        }));
    }

    void control_ui_Init() {
        mRockerViewXY = findViewById(R.id.rocker_view_left);
        mRockerViewXY_Arm = findViewById(R.id.rocker_view_right);

        mRockerViewXY.setOnShakeListener(MyRockerView.DirectionMode.DIRECTION_8, new MyRockerView.OnShakeListener() {
            @Override
            public void onStart() {
                f = 1;
            }
            @Override
            public void direction(MyRockerView.Direction direction) {
                switch (direction) {
                    case DIRECTION_LEFT:
                        directionXY = "left";
                        break;
                    case DIRECTION_RIGHT:
                        directionXY = "right";
                        break;
                    case DIRECTION_UP:
                        directionXY = "up";
                        break;
                    case DIRECTION_DOWN:
                        directionXY = "down";
                        break;
                    case DIRECTION_UP_LEFT:
                        directionXY = "left_up";
                        break;
                    case DIRECTION_UP_RIGHT:
                        directionXY = "right_up";
                        break;
                    case DIRECTION_DOWN_LEFT:
                        directionXY = "left_down";
                        break;
                    case DIRECTION_DOWN_RIGHT:
                        directionXY = "right_down";
                        break;
                    case DIRECTION_CENTER:
                        directionXY = "center";
                        break;
                }
            }
            @Override
            public void onFinish() {
                directionXY = "center";
                levelXY = 0;
                f = 0;
            }
        });
        mRockerViewXY.setOnDistanceLevelListener(new MyRockerView.OnDistanceLevelListener() {
            @Override
            public void onDistanceLevel(int level) {
                levelXY = level;
            }
        });
        mRockerViewXY_Arm.setOnShakeListener(MyRockerView.DirectionMode.DIRECTION_8, new MyRockerView.OnShakeListener() {
            @Override
            public void onStart() {
                a = 1;
            }
            @Override
            public void direction(MyRockerView.Direction direction) {
                switch (direction) {
                    case DIRECTION_LEFT:
                        directionXY_Arm = "left";
                        break;
                    case DIRECTION_RIGHT:
                        directionXY_Arm = "right";
                        break;
                    case DIRECTION_UP:
                        directionXY_Arm = "up";
                        break;
                    case DIRECTION_DOWN:
                        directionXY_Arm = "down";
                        break;
                    case DIRECTION_CENTER:
                        directionXY_Arm = "center";
                        break;
                }
            }
            @Override
            public void onFinish() {
                directionXY_Arm = "center";
                levelXY_Arm = 0;
                a = 0;
            }
        });
        mRockerViewXY_Arm.setOnDistanceLevelListener(new MyRockerView.OnDistanceLevelListener() {
            @Override
            public void onDistanceLevel(int level) {
                levelXY_Arm = level;
            }
        });
        findViewById(R.id.button_floor_left).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    f = 3;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    f = 0;
                }
                return false;
            }
        });
        findViewById(R.id.button_floor_right).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    f = 4;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    f = 0;
                }
                return false;
            }
        });
        findViewById(R.id.button_arm_up).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    a = 2;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    a = 0;
                }
                return false;
            }
        });
        findViewById(R.id.button_arm_down).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    a = 3;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    a = 0;
                }
                return false;
            }
        });
        findViewById(R.id.button_zhua).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    if (a == 4) {
                        a = 5;
                    } else {
                        a = 4;
                    }
                }
                return false;
            }
        });
        findViewById(R.id.enter_plan_panel_button).setOnClickListener((View view)->{
            Intent intent = new Intent(BLE_ControlActivity.this,PlanActivity.class);
            startActivity(intent);
        });
        control_send_cmd();
    }
    String data;
    void control_send_cmd(){
        new Handler().postDelayed(() -> {
            if (isRunning) {
                if (f == 0) {
                    data = "0400000000000000";
                }
                if (f == 1) {
                    String speed = "", speed_f = "";
                    data = "";
                    switch (levelXY) {
                        case 0:
                            speed = "0000";
                            speed_f = "0000";
                            break;
                        case 1:
                            speed = "0010";
                            speed_f = "fff0";
                            break;
                        case 2:
                            speed = "0012";
                            speed_f = "ffee";
                            break;
                        case 3:
                            speed = "0014";
                            speed_f = "ffec";
                            break;
                        case 4:
                            speed = "0016";
                            speed_f = "ffea";
                            break;
                        case 5:
                            speed = "0018";
                            speed_f = "ffe8";
                            break;
                        case 6:
                            speed = "001a";
                            speed_f = "ffe6";
                            break;
                        case 7:
                            speed = "001c";
                            speed_f = "ffe4";
                            break;
                        case 8:
                            speed = "001e";
                            speed_f = "ffe2";
                            break;
                        case 9:
                            speed = "0020";
                            speed_f = "ffe0";
                            break;
                    }
                    if (directionXY.equals("left")) {
                        data = "01" + speed + "0000";
                    }
                    if (directionXY.equals("right")) {
                        data = "01" + speed_f + "0000";
                    }
                    if (directionXY.equals("up")) {
                        data = "01" + "0000" + speed;
                    }
                    if (directionXY.equals("down")) {
                        data = "01" + "0000" + speed_f;
                    }
                    if (directionXY.equals("left_up")) {
                        data = "01" + speed + speed;
                    }
                    if (directionXY.equals("right_up")) {
                        data = "01" + speed_f + speed;
                    }
                    if (directionXY.equals("left_down")) {
                        data = "01" + speed + speed_f;
                    }
                    if (directionXY.equals("right_down")) {
                        data = "01" + speed_f + speed_f;
                    }
                    data = data + "000000";
                }
                if (f == 3) {
                    data = "030001001c000000";
                }
                if (f == 4) {
                    data = "030000001c000000";
                }
                if (a != 0) {
                    if (a == 1) {
                        String speed_arm = "00";
                        data = "";
                        switch (levelXY_Arm) {
                            case 1:case 2:case 3:
                                speed_arm = "01";
                                break;
                            case 4:case 5:case 6:
                                speed_arm = "02";
                                break;
                            case 7: case 8:case 9:
                                speed_arm = "03";
                                break;
                        }
                        if (directionXY_Arm.equals("left")) {
                            data = "05" + "0000" + "00" + speed_arm + "000000";
                        }
                        if (directionXY_Arm.equals("right")) {
                            data = "05" + "0000" + "01" + speed_arm + "000000";
                        }
                        if (directionXY_Arm.equals("up")) {
                            data = "05" + "00" + speed_arm + "0000" + "000000";
                        }
                        if (directionXY_Arm.equals("down")) {
                            data = "05" + "01" + speed_arm + "0000" + "000000";
                        }
                    }
                    if (a == 2) {
                        data = "0500000000000100";
                    }
                    if (a == 3) {
                        data = "0500000000010100";
                    }
                    if (a == 4) {
                        data = "0500000000000004";
                    }
                    if (a == 5) {
                        data = "0500000000000005";
                    }
                }
                BLE.writeBLECharacteristicValue(data, true);
            }
            control_send_cmd();
        }, 50);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        BLE.onBLECharacteristicValueChange((str, strHex)->{});
        BLE.onBLEConnectionStateChange((ok, errCode, errMsg)->{});
        BLE.closeBLEConnection();
    }
    @Override
    protected void onResume() {
        super.onResume();
        isRunning = true;
    }
    @Override
    protected void onPause() {
        super.onPause();
        isRunning = false;
    }
    void showAlert(String content, Runnable callback){
        new AlertDialog.Builder(this)
                .setTitle("提示")
                .setMessage(content)
                .setPositiveButton("OK",  (dialogInterface , i)-> new Thread(callback).start())
                .setCancelable(false)
                .create().show();
    }
}