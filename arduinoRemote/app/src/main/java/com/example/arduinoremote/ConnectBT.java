package com.example.arduinoremote;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.InputStream;
import java.io.OutputStream;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.util.Set;
import java.util.UUID;

public class ConnectBT extends AsyncTask<Void, Void, Void> {
    String carName = "Smartcar"; //this should be the arduino cars bt address
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    BluetoothDevice device = null;
    OutputStream btOutputStream;
    InputStream btInputStream;
    Boolean stopWorker = false;
    final char DELIMITER = '\n';
    byte[] readBuffer = new byte[256];
    int readBufferPosition;
    static double[] coordinates = new double[2];

    public static double[] getCoordinates(){
        return coordinates;
    }

    @Override
    protected Void doInBackground(Void... devices) { //while the progress dialog is shown, the connection is done in background
        try {
            Log.d("Testing","Background");

            myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device

            Set<BluetoothDevice> pairedDevices = myBluetooth.getBondedDevices();

            if(pairedDevices.size() > 0) {

                for(BluetoothDevice device: pairedDevices) {

                    if(device.getName().equals(carName)) {
                        this.device = device;
                        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
                        btSocket = device.createRfcommSocketToServiceRecord(uuid);
                        btSocket.connect();
                        btOutputStream = btSocket.getOutputStream();
                        btInputStream = btSocket.getInputStream();

                        workerThread thread = new workerThread(); // creates a new thread for bluetooth input
                        new Thread(thread).start(); // starts the thread for bluetooth input
                        break;
                    }
                }
            }
        }
        catch (IOException ignored) {
        }
        return null;
    }

    // Defines Thread for btInput
    class workerThread implements Runnable{
        public void run() {
            while (!Thread.currentThread().isInterrupted() && !stopWorker) {
                try{
                    int bytesAvailable = btInputStream.available(); // Number of availabe bytes
                    if (bytesAvailable > 0) {
                        byte[] packetBytes = new byte[bytesAvailable]; // Array for all incoming bytes with the size of available bytes
                        btInputStream.read(packetBytes); // Copies available bytes from btInputStream to the packetBytes Array

                        // goes through the packetBytes Array
                        for(int i=0;i<bytesAvailable;i++) {
                            byte b = packetBytes[i];
                            if(b == DELIMITER) //checks if current byte is the end-message symbol (end of one message)
                            {
                                byte[] encodedBytes = new byte[readBufferPosition]; // creates a new Array with the size of the current message
                                System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length); // copies the buffer array to the encoded bytes array
                                final String data = new String(encodedBytes, "US-ASCII"); // makes a String of the encodedBytes Array
                                readBufferPosition = 0; // resets the readBuffer pointer

                                //The variable data now contains our full command

                                Log.d("Input", data);

                                String[] separated = data.split("#");
                                Log.d("Input", separated[0]);
                                Log.d("Input", separated[1]);

                                coordinates[0] = Double.parseDouble(separated[0]); //latitude
                                coordinates[1] = Double.parseDouble(separated[1]); //longitude
                            }
                            else
                            {
                                // If the current byte is not the end-message symbol, it places the currenty byte (b) in the readBuffer array and increments the pointer by 1
                                readBuffer[readBufferPosition++] = b;
                            }
                        }
                    }


                } catch (IOException e){
                    Log.e("Input", e.toString());
                }
            }
        }
    }
}