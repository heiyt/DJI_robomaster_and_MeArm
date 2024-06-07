package com.example.bysj;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;

public class WeightDatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "weight.db";
    private static final int DATABASE_VERSION = 1;
    public static final String TABLE_NAME = "weight";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_NUMBER = "number";
    public WeightDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = "CREATE TABLE " + TABLE_NAME + " (" +
                COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COLUMN_NUMBER + " TEXT)";
        db.execSQL(createTable);
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
    public void insertWeight(String number) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(COLUMN_NUMBER, number);
        db.insert(TABLE_NAME, null, values);
        db.close();
    }
    public List<WeightDatabaseHelper.WeightRecord> getAllWeights() {
        List<WeightDatabaseHelper.WeightRecord> weightList = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, null, null, null, null, null, null);
        if (cursor.moveToFirst()) {
            do {
                @SuppressLint("Range") String number = cursor.getString(cursor.getColumnIndex(COLUMN_NUMBER));
                weightList.add(new WeightDatabaseHelper.WeightRecord(number));
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return weightList;
    }
    public void deleteLastWeight() {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_NAME, COLUMN_ID + " = (SELECT MAX(" + COLUMN_ID + ") FROM " + TABLE_NAME + ")", null);
        db.close();
    }
    public static class WeightRecord {
        private final String number;
        public WeightRecord(String number) {
            this.number = number;
        }
        public String getWeight() {
            return number;
        }
    }
}
