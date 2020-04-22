package com.example.arduinoremote;

import android.bluetooth.BluetoothSocket;
import android.os.Build;
import android.view.View;
import android.widget.Button;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.TextView;

import java.io.IOException;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static String instruction = "s";
    Button forwardBut, stopBut, reverseBut;
    SeekBar accelBar;
    TextView accelText;
    BluetoothSocket btSocket = null;
    boolean isReversed = false;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (btSocket == null) {
           // new ConnectBT().execute();
        }

        forwardBut = (Button) findViewById(R.id.forwardBut);
        stopBut = (Button) findViewById(R.id.stopBut);
        accelBar = (SeekBar) findViewById(R.id.accelBar);
        accelText = (TextView) findViewById(R.id.accelText);
        reverseBut = (Button) findViewById(R.id.reverseBut);
        accelBar.setProgress(0);
        accelBar.setMin(0);
        accelBar.setMax(5);
        enableSeekbar(accelBar);
        forwardBut.setOnClickListener(this);
        stopBut.setOnClickListener(this);
        reverseBut.setOnClickListener(this);
    }



    public void enableSeekbar(SeekBar seekbar) {
        seekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

               int btAccelValue=0;
                String speedText = "" + progress;
               if(!isReversed) {
                   accelText.setText(speedText);

                   btAccelValue = (progress * 20);
               }else{
                   if (progress != 0){
                   speedText = "-" + progress;}
                   accelText.setText(speedText);

                   btAccelValue = (progress * -20);
               }

                instruction = "V" + btAccelValue;
                if (btSocket != null) {
                    try {
                        btSocket.getOutputStream().write(instruction.getBytes());
                    } catch (IOException ignored) {
                    }
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

            switch (v.getId()) {
                case R.id.forwardBut:
                    instruction = "f";
                    if (btSocket != null) {
                        try {
                            btSocket.getOutputStream().write(instruction.getBytes());
                        } catch (IOException ignored) {
                        }
                    }
                    break;

                case R.id.stopBut:
                    instruction = "s";
                    if (btSocket != null) {
                        try {
                            btSocket.getOutputStream().write(instruction.getBytes());
                        } catch (IOException ignored) {
                        }
                    }
                    break;

                case R.id.reverseBut:
                    if (!isReversed){
                        isReversed = true;
                        reverseBut.setText(" Switch to Forward mode");
                        accelBar.setProgress(0);
            }else{
                    isReversed = false;
                    reverseBut.setText("Switch to Reverse mode");
                    accelBar.setProgress(0);
                    }
                    break;
            }
    }
}

