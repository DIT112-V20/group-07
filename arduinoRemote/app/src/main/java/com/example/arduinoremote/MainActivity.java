package com.example.arduinoremote;

import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

//import the bluetooth connectivity thing from the bluetooth group!! (***btSocket*** or whatever name they choose)

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static char instruction = 's';

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button forwardBut = (Button)findViewById(R.id.forwardBut);
        Button stopBut = (Button)findViewById(R.id.stopBut);
        forwardBut.setOnClickListener(this);
        stopBut.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        //do something when the button is clicked
        switch (v.getId()) {
            case R.id.forwardBut:
                instruction = 'f';
                btSocket.getOutputStream().write(instruction);
                break;

            case R.id.stopBut:
                instruction = 's';
                btSocket.getOutputStream().write(instruction);
                break;
        }


    }
}
