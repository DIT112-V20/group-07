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
import android.widget.Toast;

import java.io.IOError;
import java.io.IOException;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    String instruction = getResources().getString(R.string.forward_speed_character)+getResources().getString(R.string.base_value);
    Button forwardBut, stopBut, reverseBut, connectBut;
    SeekBar accelBar;
    SeekBar steeringBar;
    TextView accelText;
    TextView steeringText;
    boolean isReversed = false;
    ConnectBT connection;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d("Testing", "Build");

        // Setting up the buttons
        forwardBut = (Button) findViewById(R.id.forwardBut);
        stopBut = (Button) findViewById(R.id.stopBut);
        accelBar = (SeekBar) findViewById(R.id.accelBar);
        steeringBar = (SeekBar) findViewById(R.id.steeringBar);
        accelText = (TextView) findViewById(R.id.accelText);
        steeringText = (TextView) findViewById(R.id.steeringText);
        reverseBut = (Button) findViewById(R.id.reverseBut);
        connectBut = (Button) findViewById(R.id.connectBut);

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
        connectBut.setOnClickListener(this);
    }


    public void enableSeekbar(final SeekBar seekbar) {
        seekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                if (seekBar == accelBar) {
                    int btAccelValue = 0;
                    final int MULTIPLIER = 20;
                    String speedText = getResources().getString(R.string.gear_string) + progress;

                    // if reverse mode is on, show negative values and send b+speed, otherwise show positive values and send v+speed.
                    if (!isReversed) {
                        accelText.setText(speedText);

                        btAccelValue = (progress * MULTIPLIER);
                        instruction = getResources().getString(R.string.forward_speed_character) + btAccelValue + "\n";
                    } else {
                        if (progress != 0) {
                            speedText = getResources().getString(R.string.gear_string) + "-" + progress;
                        }
                        accelText.setText(speedText);

                        btAccelValue = (progress * MULTIPLIER);
                        instruction = getResources().getString(R.string.backward_speed_character) + btAccelValue + "\n";
                    }
                    if (connection != null)
                        try {
                            connection.btOutputStream.write(instruction.getBytes());
                        } catch (IOException ignored) {
                        }

                    // show the angle and send t+angle to the car.
                } else if (seekBar == steeringBar) {
                    final int MULTIPLIER = 5;
                    int btTurnValue = progress * MULTIPLIER;
                    instruction = getResources().getString(R.string.steering_character) + btTurnValue + "\n";
                    String angleText = getResources().getString(R.string.angle_string) + (progress * MULTIPLIER) + getResources().getString(R.string.angle_symbol);
                    steeringText.setText(angleText);
                    if (connection != null)
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
                if (accelBar.getProgress() == 0)
                    accelBar.setProgress(1);
                break;

            //send instruction to go backward
            case R.id.stopBut:
                accelBar.setProgress(0);
                break;

            // Put the car in reverse mode and stop the car, and vice versa.
            case R.id.reverseBut:
                if (!isReversed) {
                    isReversed = true;
                    reverseBut.setText(R.string.forward_mode_but);
                    accelBar.setProgress(0);
                    steeringBar.setProgress(0);
                } else {
                    isReversed = false;
                    reverseBut.setText(R.string.reverse_mode_but);
                    accelBar.setProgress(0);
                    steeringBar.setProgress(0);
                }
                break;

            //connect the app to the car via bluetooth
            case R.id.connectBut:
                connection = new ConnectBT();
                connection.execute();
                if (connection != null)
                    connectBut.setVisibility(View.INVISIBLE);
        }
    }
}

