package com.example.arduinoremote;

import android.bluetooth.BluetoothSocket;
import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.TextView;

import java.io.IOException;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static String instruction = "s";
    Button forwardBut, stopBut;
    SeekBar accelBar;
    TextView accelText;
    BluetoothSocket btSocket = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (btSocket == null) {
        //    new ConnectBT().execute();
        }

        forwardBut = (Button) findViewById(R.id.forwardBut);
        stopBut = (Button) findViewById(R.id.stopBut);
        accelBar = (SeekBar) findViewById(R.id.accelBar);
        accelText = (TextView) findViewById(R.id.accelText);
        accelBar.setProgress(50);
        enableSeekbar(accelBar);
        forwardBut.setOnClickListener(this);
        stopBut.setOnClickListener(this);
    }



    public void enableSeekbar(SeekBar seekbar) {
        seekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                int accelValue = 0;


                if(progress == 0 ){
                    accelValue = -5;
                }else if (progress < 11){
                    accelValue = -4;
                }else if (progress < 22){
                    accelValue = -3;
                }else if (progress < 33){
                    accelValue = -2;
                }else if (progress < 44){
                    accelValue = -1;
                }else if (progress < 55){
                    accelValue = 0;
                }else if (progress < 66){
                    accelValue = 1;
                }else if (progress < 77){
                    accelValue = 2;
                }else if (progress < 88){
                    accelValue = 3;
                }else if (progress < 99){
                    accelValue = 4;
                }else if (progress == 100){
                    accelValue = 5;
                }
                accelText.setText("" + accelValue + "");

                int btAccelValue = (accelValue * 20);

                instruction = "V" + btAccelValue;
                try {
                    btSocket.getOutputStream().write(instruction.getBytes());
                } catch (IOException ignored) {
                }

            }

            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        }
        );
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

