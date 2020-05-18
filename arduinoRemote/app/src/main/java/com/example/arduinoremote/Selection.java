package com.example.arduinoremote;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Selection extends AppCompatActivity implements View.OnClickListener {

    Button driverBut, userBut;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_selection);

        driverBut = (Button) findViewById(R.id.driverBut);
        userBut = (Button) findViewById(R.id.userBut);

        driverBut.setOnClickListener(this);
        userBut.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {

        switch (v.getId()) {

            case R.id.driverBut:
                Intent intentDriver = new Intent(this, MainActivity.class);
                startActivity(intentDriver);

            case R.id.userBut:
                Intent intentUser = new Intent(this, MapsActivity.class);
                startActivity(intentUser);
        }

    }
}
