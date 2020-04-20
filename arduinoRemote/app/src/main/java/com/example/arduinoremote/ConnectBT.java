package com.example.arduinoremote;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

public class ConnectBT extends AsyncTask<Void, Void, Void> {
    private boolean ConnectSuccess = true; //if it's here, it's almost connected
    String address = "24:6F:28:B6:09:A2"; //this should be the arduino cars bt address
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("25dd9b13-b489-4c34-a9b7-31fad9f63b4b");


    @Override
    protected Void doInBackground(Void... devices) { //while the progress dialog is shown, the connection is done in background
        try {
            Log.d("Testing","Background");

            if (btSocket == null || !isBtConnected) {
                Log.d("Testing","IF");
                myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                BluetoothDevice enhet = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                btSocket = enhet.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                btSocket.connect();//start connection
            }
        }
        catch (IOException e) {
            ConnectSuccess = false;//if the try failed, you can check the exception here
        }
        return null;
    }
}