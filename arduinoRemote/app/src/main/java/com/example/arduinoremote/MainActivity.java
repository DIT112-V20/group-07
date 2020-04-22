package com.example.arduinoremote;

import android.bluetooth.BluetoothSocket;
import android.os.Build;
import android.util.Log;
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
    SeekBar steeringBar;
    TextView accelText;
    TextView steeringText;
    BluetoothSocket btSocket = null;
    boolean isReversed = false;
    ConnectBT connection;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d("Testing","Build");
        connection = new ConnectBT();
        connection.execute();

        // Setting up the buttons
        forwardBut = (Button) findViewById(R.id.forwardBut);
        stopBut = (Button) findViewById(R.id.stopBut);
        accelBar = (SeekBar) findViewById(R.id.accelBar);
        steeringBar = (SeekBar) findViewById(R.id.steeringBar);
        accelText = (TextView) findViewById(R.id.accelText);
        steeringText = (TextView) findViewById(R.id.steeringText);
        reverseBut = (Button) findViewById(R.id.reverseBut);

        // Configuring accelBar
        accelBar.setProgress(0);
        accelBar.setMin(0);
        accelBar.setMax(5);

        //configuring steeringBar
        steeringBar.setProgress(0);
        steeringBar.setMin(-18);
        steeringBar.setMax(18);

        // Enabling all buttons to be able to handle inputs
        enableSeekbar(accelBar);
        enableSeekbar(steeringBar);
        forwardBut.setOnClickListener(this);
        stopBut.setOnClickListener(this);
        reverseBut.setOnClickListener(this);
    }



    public void enableSeekbar(final SeekBar seekbar) {
        seekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                if (seekBar == accelBar){
                    int btAccelValue = 0;
                String speedText = "" + progress;

                // if reverse mode is on, show and send negative values, otherwise show and send positive values
                if (!isReversed) {
                    accelText.setText(speedText);

                    btAccelValue = (progress * 20);
                    instruction = "v" + btAccelValue;
                } else {
                    if (progress != 0) {
                        speedText = "-" + progress;
                    }
                    accelText.setText(speedText);

                    btAccelValue = (progress * 20);
                    instruction = "b" + btAccelValue;
                }

                    try {
                        connection.btOutputStream.write(instruction.getBytes());
                    } catch (IOException ignored) {
                    }

            }else if(seekBar == steeringBar){
                     int btTurnValue = progress*5;
                    instruction = "t" + btTurnValue;
                    String angleText = "" + (progress*5);
                    steeringText.setText(angleText);
                        try {
                            connection.btOutputStream.write(instruction.getBytes());
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

        // that's why buttons are not clickable ;)

            switch (v.getId()) {

                //send instruction to go forward
                case R.id.forwardBut:
                    instruction = "f";
                    try {
                        Log.d("Buttontest", "BUTTON F WORKS" + instruction);
                        connection.btOutputStream.write(instruction.getBytes());
                    } catch (IOException ignored) {
                    }
                    break;

                    //send instruction to go backward
                case R.id.stopBut:
                    instruction = "s";
                    try {
                    Log.d("Buttontest", "BUTTON S WORKS" + instruction);
                      connection.btOutputStream.write(instruction.getBytes());
                    } catch (IOException ignored) {
                    }
                    break;

                    // Put the car in reverse mode and stop the car, and vice versa.
                case R.id.reverseBut:
                    if (!isReversed){
                        isReversed = true;
                        reverseBut.setText(R.string.forward_mode_but);
                        accelBar.setProgress(0);
                        steeringBar.setProgress(0);
            }else{
                    isReversed = false;
                    reverseBut.setText(R.string.reverse_mode_but);
                    accelBar.setProgress(0);
                    steeringBar.setProgress(0);
                    }
                    break;
            }
    }
}

