package com.example.arduinoremote;

import android.bluetooth.BluetoothSocket;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import java.io.IOException;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    char instruction = 's';
    Button forwardBut, stopBut;
    ConnectBT connection;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d("Testing","Build");
        connection = new ConnectBT();
        connection.execute();

        forwardBut = (Button) findViewById(R.id.forwardBut);
        stopBut = (Button) findViewById(R.id.stopBut);
        forwardBut.setOnClickListener(this);
        stopBut.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        //do something when the button is clicked

        // that's why buttons are not clickable ;)

            switch (v.getId()) {
                case R.id.forwardBut:
                    instruction = 'f';
                    try {
                        Log.d("Buttontest", "BUTTON F WORKS" + instruction);
                        connection.btOutputStream.write(instruction);
                    } catch (IOException ignored) {
                    }
                    break;

                case R.id.stopBut:
                    instruction = 's';
                    try {
                    Log.d("Buttontest", "BUTTON S WORKS" + instruction);
                      connection.btOutputStream.write(instruction);
                    } catch (IOException ignored) {
                    }
                    break;
            }

    }
}

