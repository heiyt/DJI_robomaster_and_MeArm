package com.example.bysj;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import java.util.ArrayList;
import java.util.List;

public class SpeedDatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "speed.db";
    private static final int DATABASE_VERSION = 1;
    public static final String TABLE_NAME = "speed";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_CMD = "cmd";
    public static final String COLUMN_HEAD = "head";
    public static final String COLUMN_SPEED_X = "speed_x";
    public static final String COLUMN_SPEED_Y = "speed_y";
    public static final String COLUMN_Z = "z";
    public static final String COLUMN_END = "e";
    public static final String COLUMN_TIME = "time";
    public SpeedDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = "CREATE TABLE " + TABLE_NAME + " (" +
                COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COLUMN_CMD + " TEXT, " +
                COLUMN_HEAD + " TEXT, " +
                COLUMN_SPEED_X + " TEXT, " +
                COLUMN_SPEED_Y + " TEXT, " +
                COLUMN_Z + " TEXT, " +
                COLUMN_END + " TEXT, " +
                COLUMN_TIME + " TEXT)";
        db.execSQL(createTable);
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
    public void insertSpeeds(String cmd,String head, String speedX, String speedY,String z,String e,String time) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(COLUMN_CMD, cmd);
        values.put(COLUMN_HEAD, head);
        values.put(COLUMN_SPEED_X, speedX);
        values.put(COLUMN_SPEED_Y, speedY);
        values.put(COLUMN_Z,z);
        values.put(COLUMN_END,e);
        values.put(COLUMN_TIME, time);
        db.insert(TABLE_NAME, null, values);
        db.close();
    }
    public List<SpeedRecord> getAllSpeeds() {
        List<SpeedRecord> speedList = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, null, null, null, null, null, null);
        if (cursor.moveToFirst()) {
            do {
                @SuppressLint("Range") String cmd = cursor.getString(cursor.getColumnIndex(COLUMN_CMD));
                @SuppressLint("Range") String head = cursor.getString(cursor.getColumnIndex(COLUMN_HEAD));
                @SuppressLint("Range") String speedX = cursor.getString(cursor.getColumnIndex(COLUMN_SPEED_X));
                @SuppressLint("Range") String speedY = cursor.getString(cursor.getColumnIndex(COLUMN_SPEED_Y));
                @SuppressLint("Range") String z = cursor.getString(cursor.getColumnIndex(COLUMN_Z));
                @SuppressLint("Range") String e = cursor.getString(cursor.getColumnIndex(COLUMN_END));
                @SuppressLint("Range") String time = cursor.getString(cursor.getColumnIndex(COLUMN_TIME));
                speedList.add(new SpeedRecord(cmd, head, speedX, speedY, z, e, time));
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return speedList;
    }
    public void deleteLastSpeed() {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_NAME, COLUMN_ID + " = (SELECT MAX(" + COLUMN_ID + ") FROM " + TABLE_NAME + ")", null);
        db.close();
    }
    public static class SpeedRecord {
        private final String cmd;
        private final String head;
        private final String speedX;
        private final String speedY;
        private final String z;
        private final String e;
        private final String time;
        public SpeedRecord(String cmd, String head, String speedX, String speedY, String z, String e, String time) {
            this.cmd = cmd;
            this.head = head;
            this.speedX = speedX;
            this.speedY = speedY;
            this.z = z;
            this.e = e;
            this.time = time;
        }
        public String getCmd() {
            return cmd;
        }
        public String getHead() {
            return head;
        }
        public String getSpeedX() {
            return speedX;
        }
        public String getSpeedY() {
            return speedY;
        }
        public String getZ() {
            return z;
        }
        public String getE() {
            return e;
        }
        public String getTime() {
            return time;
        }
    }
}