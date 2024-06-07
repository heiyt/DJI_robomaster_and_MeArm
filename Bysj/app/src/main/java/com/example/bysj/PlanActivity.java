package com.example.bysj;

import static java.lang.Math.cos;
import static java.lang.Math.sin;
import static java.lang.Math.toRadians;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.List;


public class PlanActivity extends AppCompatActivity {
    boolean isRunning = false;
    SpeedDatabaseHelper dbHelper;
    WeightDatabaseHelper weightDatabaseHelper;
    List<SpeedDatabaseHelper.SpeedRecord> speedInfo_run;;
    List<WeightDatabaseHelper.WeightRecord> weightInfo;;
    TextView cmd;
    TextView Weight_Tv;
    int speedInfo_size;
    int delayms = 50;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_plan);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        ui_init();

        BLE.onBLECharacteristicValueChange((String str, String strHex)-> runOnUiThread(()->{
            if (strHex.startsWith("08")) {
                if (isRunning) {
                    showAlert("遇到障碍物",()->{});
                    isRunning = false;
                }
            }
            if (strHex.startsWith("02")) {
                weightDatabaseHelper.insertWeight(strHex.substring(2,10)+"g\n");
                refresh_weight();
            }
        }));
    }

    void ui_init(){
        cmd = findViewById(R.id.textView);
        Weight_Tv = findViewById(R.id.Weight_Tv);
        dbHelper = new SpeedDatabaseHelper(PlanActivity.this);
        weightDatabaseHelper = new WeightDatabaseHelper(PlanActivity.this);
        speedInfo_run = dbHelper.getAllSpeeds();
        weightInfo = weightDatabaseHelper.getAllWeights();
        speedInfo_size = speedInfo_run.size();
        findViewById(R.id.plan_forward_button).setOnClickListener((View v) -> {
            FloorDialogSet(1);
        });
        findViewById(R.id.plan_back_button).setOnClickListener((View v) -> {
            FloorDialogSet(2);
        });
        findViewById(R.id.plan_left_button).setOnClickListener((View v) -> {
            FloorDialogSet(3);
        });
        findViewById(R.id.plan_right_button).setOnClickListener((View v) -> {
            FloorDialogSet(4);
        });
        findViewById(R.id.left_forward).setOnClickListener((View v) -> {
            FloorDialogSet(5);
        });
        findViewById(R.id.left_backward).setOnClickListener((View v) -> {
            FloorDialogSet(6);
        });
        findViewById(R.id.right_forward).setOnClickListener((View v) -> {
            FloorDialogSet(7);
        });
        findViewById(R.id.right_backward).setOnClickListener((View v) -> {
            FloorDialogSet(8);
        });
        findViewById(R.id.plan_floor_button).setOnClickListener((View v) -> {
            FloorDialogSet(9);
        });
        findViewById(R.id.plan_floor_rotate).setOnClickListener((View v) -> {
            FloorDialogSet(10);
        });
        findViewById(R.id.plan_arm_button).setOnClickListener((View v) -> {
            FloorDialogSet(11);
        });
        findViewById(R.id.plan_zhua_button).setOnClickListener((View v) -> {
            FloorDialogSet(12);
        });
        findViewById(R.id.plan_del_button).setOnClickListener((View v) -> {
            dbHelper.deleteLastSpeed();
            refresh_cmd();
        });
        findViewById(R.id.plan_begin_button).setOnClickListener((View v) -> {
            if (!isRunning) {
                speedInfo_run = dbHelper.getAllSpeeds();
                speedInfo_size = speedInfo_run.size();
                isRunning = true;
            }
        });
        findViewById(R.id.plan_stop_button).setOnClickListener((View v) -> {
            isRunning = false;
        });
        findViewById(R.id.getWeight_button).setOnClickListener((View v) -> {
            dbHelper.insertSpeeds("开始称重\n", "08", "0000", "0000", "0000", "00", delayms * 2 + "");
            refresh_cmd();
        });
        findViewById(R.id.plan_del_weight_button).setOnClickListener((View v)->{
            weightDatabaseHelper.deleteLastWeight();
            refresh_weight();
        });
        refresh_cmd();
        refresh_weight();
        running(0, 0);
    }
    void FloorDialogSet(int fx){
        String fx_str = "底盘运动";
        if (fx != 9 && fx != 10 && fx != 11 && fx != 12) {
            if (fx == 1) {
                fx_str = "向前运动";
            }
            if (fx == 2) {
                fx_str = "向后运动";
            }
            if (fx == 3) {
                fx_str = "向左运动";
            }
            if (fx == 4) {
                fx_str = "向右运动";
            }
            if (fx == 5) {
                fx_str = "向左前运动";
            }
            if (fx == 6) {
                fx_str = "向左后运动";
            }
            if (fx == 7) {
                fx_str = "向右前运动";
            }
            if (fx == 8) {
                fx_str = "向右后运动";
            }
            @SuppressLint("InflateParams")
            View dialogView = LayoutInflater.from(PlanActivity.this).inflate(R.layout.plan_floor_dialog_simple, null);
            AlertDialog.Builder builder = new AlertDialog.Builder(PlanActivity.this);
            Spinner spinner = dialogView.findViewById(R.id.spinner);
            EditText distance_ev = dialogView.findViewById(R.id.distance_editView_simple);
            String finalFx_str = fx_str;
            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (!(distance_ev.getText().toString().isEmpty())) {
                        String speed_x = "0000";
                        String speed_y = "0000";
                        String time;
                        if (fx == 1 || fx == 5 || fx == 7) {
                            if (fx != 1) {
                                speed_y = String.format("%04x", (int) (Double.parseDouble(spinner.getSelectedItem().toString()) * 1.4));
                            } else {
                                speed_y = String.format("%04x", Integer.parseInt(spinner.getSelectedItem().toString()) * 2);
                            }
                        }
                        if (fx == 2 || fx == 6 || fx == 8) {
                            if (fx != 2) {
                                speed_y = String.format("%04x", (-(int) (Double.parseDouble(spinner.getSelectedItem().toString()) * 1.4)) & 0xffff);
                            } else {
                                speed_y = String.format("%04x", (-Integer.parseInt(spinner.getSelectedItem().toString()) * 2) & 0xffff);
                            }
                        }
                        if (fx == 3 || fx == 5 || fx == 6) {
                            if (fx != 3) {
                                speed_x = String.format("%04x", (int) (Double.parseDouble(spinner.getSelectedItem().toString()) * 1.4));
                            } else {
                                speed_x = String.format("%04x", Integer.parseInt(spinner.getSelectedItem().toString()) * 2);
                            }
                        }
                        if (fx == 4 || fx == 7 || fx == 8) {
                            if (fx != 4) {
                                speed_x = String.format("%04x", (-(int) (Double.parseDouble(spinner.getSelectedItem().toString()) * 1.4)) & 0xffff);
                            } else {
                                speed_x = String.format("%04x", (-Integer.parseInt(spinner.getSelectedItem().toString()) * 2) & 0xffff);
                            }
                        }
                        int Sd = Integer.parseInt(spinner.getSelectedItem().toString());
                        if (Sd != 0) {
                            time =  String.valueOf(1000 * Integer.parseInt(distance_ev.getText().toString()) / Sd);
                        } else {
                            time = "0";
                        }
                        String cmd_str = finalFx_str + distance_ev.getText().toString() + "cm 速度:" + spinner.getSelectedItem() + "cm/s\n";
                        dbHelper.insertSpeeds(cmd_str, "01", speed_x, speed_y, "0000", "00", time);
                        refresh_cmd();
                    }
                }
            });
            builder.setNegativeButton("取消", (dialog, which) -> {});
            builder.setTitle(fx_str);
            builder.setView(dialogView);
            builder.create().show();
        }
        if (fx == 9) {
            fx_str = "底盘运动";
            LayoutInflater inflater = LayoutInflater.from(this);
            @SuppressLint("InflateParams")
            View dialogView = inflater.inflate(R.layout.plan_floor_dialog, null);
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            EditText distance_ev = dialogView.findViewById(R.id.distance_Et);
            EditText angle_ev = dialogView.findViewById(R.id.angle_Et);
            Spinner spinner = dialogView.findViewById(R.id.spinner_2);
            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (!(distance_ev.getText().toString().isEmpty() || angle_ev.getText().toString().isEmpty())) {
                        String speed_x = String.format("%04x", (int) (Double.parseDouble(spinner.getSelectedItem().toString()) * 2 * sin(toRadians(Integer.parseInt(angle_ev.getText().toString())))) & 0xffff);
                        String speed_y = String.format("%04x", (int) (Double.parseDouble(spinner.getSelectedItem().toString()) * 2 * cos(toRadians(Integer.parseInt(angle_ev.getText().toString())))) & 0xffff);
                        String time = "0";
                        int Sd = Integer.parseInt(spinner.getSelectedItem().toString());
                        if (Sd != 0) {
                            time = String.valueOf(1000 * Integer.parseInt(distance_ev.getText().toString()) / Sd);
                        } else {
                            time = "0";
                        }
                        String cmd_str = angle_ev.getText().toString() + "°方向运动" + distance_ev.getText().toString() + "cm 速度:" + spinner.getSelectedItem().toString() + "cm/s\n";
                        dbHelper.insertSpeeds(cmd_str, "01", speed_x, speed_y, "0000", "00", time);
                        refresh_cmd();
                    }
                }
            });
            builder.setNegativeButton("取消", (dialog, which) -> {});
            builder.setTitle(fx_str);
            builder.setView(dialogView);
            builder.create().show();
        }
        if (fx == 10) {
            fx_str = "底盘旋转";
            LayoutInflater inflater = LayoutInflater.from(this);
            @SuppressLint("InflateParams")
            View dialogView = inflater.inflate(R.layout.plan_floor_dialog_rotate, null);
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            EditText angle = dialogView.findViewById(R.id.angle);
            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (!(angle.getText().toString().isEmpty())) {
                        int an = Integer.parseInt(angle.getText().toString()) % 360;
                        if (an > 180) {
                            an = 360 - an;
                            String time = (100 * an / 3) + "";
                            String cmd_str = "旋转-" + an + "°\n";
                            dbHelper.insertSpeeds(cmd_str, "03", "0001", "0015", "0000", "00", time);
                        } else {
                            String time = (100 * an / 3) + "";
                            String cmd_str = "旋转" + an + "°\n";
                            dbHelper.insertSpeeds(cmd_str, "03", "0000", "0015", "0000", "00", time);
                        }
                        refresh_cmd();
                    }
                }
            });
            builder.setNegativeButton("取消", (dialog, which) -> {});
            builder.setTitle(fx_str);
            builder.setView(dialogView);
            builder.create().show();
        }
        if (fx == 11) {
            fx_str = "机械臂运动";
            LayoutInflater inflater = LayoutInflater.from(this);
            @SuppressLint("InflateParams")
            View dialogView = inflater.inflate(R.layout.plan_arm_dialog, null);
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            EditText x = dialogView.findViewById(R.id.x_Et);
            EditText y = dialogView.findViewById(R.id.y_Et);
            EditText z = dialogView.findViewById(R.id.z_Et);
            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (!(x.getText().toString().isEmpty()||y.getText().toString().isEmpty()||z.getText().toString().isEmpty())) {
                        String speedX = String.format("%04x", Integer.parseInt(x.getText().toString()) & 0xffff);
                        String speedY = String.format("%04x", Integer.parseInt(y.getText().toString()) & 0xffff);
                        String zz = String.format("%04x", Integer.parseInt(z.getText().toString()) & 0xffff);
                        String cmd_str = String.format("机械臂运动到(%s,%s,%s)\n", (short) Integer.parseInt(speedX, 16), (short) Integer.parseInt(speedY, 16), (short) Integer.parseInt(zz, 16));
                        dbHelper.insertSpeeds(cmd_str, "06", speedX, speedY, zz, "00", 2 * delayms + "");
                        refresh_cmd();
                    }
                }
            });
            builder.setNegativeButton("取消", (dialog, which) -> {});
            builder.setTitle(fx_str);
            builder.setView(dialogView);
            builder.create().show();
        }
        if (fx == 12) {
            fx_str = "机械臂夹爪";
            LayoutInflater inflater = LayoutInflater.from(this);
            @SuppressLint("InflateParams")
            View dialogView = inflater.inflate(R.layout.plan_arm_dialog_zhua, null);
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            EditText zhua = dialogView.findViewById(R.id.zhua_Et);
            builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (!(zhua.getText().toString().isEmpty())) {
                        String cmd_str = "夹爪角度：" + zhua.getText().toString() + "度\n";
                        dbHelper.insertSpeeds(cmd_str, "07", String.format("%04x", Integer.parseInt(zhua.getText().toString()) & 0xffff), "0000", "0000", "00", 2 * delayms + "");
                        refresh_cmd();
                    }
                }
            });
            builder.setNegativeButton("取消", (dialog, which) -> {});
            builder.setTitle(fx_str);
            builder.setView(dialogView);
            builder.create().show();
        }
    }
    void running(int cmd_wz,int Xh){
        new Handler().postDelayed(() -> {
            if (isRunning) {
                int j = Integer.parseInt(speedInfo_run.get(cmd_wz).getTime()) / delayms;
                String data = speedInfo_run.get(cmd_wz).getHead() +
                        speedInfo_run.get(cmd_wz).getSpeedX() +
                        speedInfo_run.get(cmd_wz).getSpeedY() +
                        speedInfo_run.get(cmd_wz).getZ() +
                        speedInfo_run.get(cmd_wz).getE();
                BLE.writeBLECharacteristicValue(data, true);
                if (Xh + 1 < j) {
                    running(cmd_wz, Xh + 1);
                } else if (cmd_wz + 1 < speedInfo_size) {
                    running(cmd_wz + 1, 0);
                } else {
                    isRunning = false;
                    running(0, 0);
                }
            } else {
                running(0, 0);
                BLE.writeBLECharacteristicValue("0400000000000000", true);
            }
        }, delayms);
    }
    void refresh_cmd() {
        StringBuilder show = new StringBuilder();
        List<SpeedDatabaseHelper.SpeedRecord> speedInfo = dbHelper.getAllSpeeds();
        for (int i = 0; i < speedInfo.size(); i++) {
            String formattedCmd = String.format("%s", speedInfo.get(i).getCmd());
            show.append(formattedCmd);
        }
        cmd.setText(show);
    }
    void refresh_weight(){
        StringBuilder show = new StringBuilder();
        List<WeightDatabaseHelper.WeightRecord> weightInfo = weightDatabaseHelper.getAllWeights();
        if (!weightInfo.isEmpty()) {
            for (int i = 0; i < weightInfo.size(); i++) {
                String formattedCmd = String.format("%s", weightInfo.get(i).getWeight());
                show.append(formattedCmd);
            }
        }
        Weight_Tv.setText(show);
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        BLE.onBLECharacteristicValueChange((str, strHex)->{});
        BLE.onBLEConnectionStateChange((ok, errCode, errMsg)->{});
        BLE.closeBLEConnection();
    }
    @Override
    protected void onPause() {
        super.onPause();
        finish();
    }
    void showAlert(String content, Runnable callback){
        new androidx.appcompat.app.AlertDialog.Builder(this)
                .setTitle("提示")
                .setMessage(content)
                .setPositiveButton("OK",  (dialogInterface , i)-> new Thread(callback).start())
                .setCancelable(false)
                .create().show();
    }
}