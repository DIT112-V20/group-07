package com.example.arduinoremote;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

import java.io.IOException;
import java.util.UUID;

//import the bluetooth connectivity thing from the bluetooth group!! (***btSocket*** or whatever name they choose)
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static String instruction = "s";
    static int REQUEST_ENABLE_BT = 1;
    Button forwardBut, stopBut;
    String address = "24:6F:28:B6:09:A2"; //this should be the arduino cars bt address
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("25dd9b13-b489-4c34-a9b7-31fad9f63b4b");


    protected void doInBackground(Void... devices) {

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        forwardBut = (Button) findViewById(R.id.forwardBut);
        stopBut = (Button) findViewById(R.id.stopBut);
        forwardBut.setOnClickListener(this);
        stopBut.setOnClickListener(this);


    }

    @Override
    public void onClick(View v) {
        //do something when the button is clicked
        if (btSocket != null) {


            switch (v.getId()) {
                case R.id.forwardBut:
                    instruction = "f";
                    try {
                        btSocket.getOutputStream().write(instruction.getBytes());
                    } catch (IOException ignored) {
                    }
                    break;

                case R.id.stopBut:
                    instruction = "s";
                    try {
                        btSocket.getOutputStream().write(instruction.getBytes());
                    } catch (IOException ignored) {
                    }
                    break;
            }
        }


    }
}

