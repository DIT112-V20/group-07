package com.example.arduinoremote;

import android.bluetooth.BluetoothSocket;
import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import java.io.IOException;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static String instruction = "s";
    Button forwardBut, stopBut;
    BluetoothSocket btSocket = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (btSocket == null) {
            new ConnectBT().execute();
        }

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

