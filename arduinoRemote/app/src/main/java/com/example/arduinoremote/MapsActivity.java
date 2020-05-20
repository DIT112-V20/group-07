package com.example.arduinoremote;

import androidx.fragment.app.FragmentActivity;

import android.graphics.Color;
import android.nfc.Tag;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;

import com.google.android.gms.common.api.Status;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.BitSet;
import java.util.HashMap;
import java.util.List;
import com.google.android.libraries.places.api.Places;
import com.google.android.libraries.places.api.model.Place;
import com.google.android.libraries.places.widget.AutocompleteSupportFragment;
import com.google.android.libraries.places.widget.listener.PlaceSelectionListener;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

    }

    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;
        final ArrayList<LatLng> MarkerPoints = new ArrayList<>();

        // Marker is set at Car position and the camera is there as well
         LatLng carPosition = new LatLng((ConnectBT.getCoordinates()[0]), ConnectBT.getCoordinates()[1] );
        mMap.addMarker(new MarkerOptions().position(carPosition).title("Marker at Car").icon((BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN))));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(carPosition));
        mMap.setOnMapClickListener(new GoogleMap.OnMapClickListener() {

            @Override
            public void onMapClick(LatLng point) {
addPoint(MarkerPoints, point);
addPath(MarkerPoints);
            }
        });

        /**
         * Initialize Places. For simplicity, the API key is hard-coded. In a production
         * environment we recommend using a secure mechanism to manage API keys.
         */
        if (!Places.isInitialized()) {
            Places.initialize(getApplicationContext(), getResources().getString(R.string.google_maps_key));
        }


// Initialize the AutocompleteSupportFragment.
        AutocompleteSupportFragment autocompleteFragment = (AutocompleteSupportFragment)
                getSupportFragmentManager().findFragmentById(R.id.autocomplete_fragment);

        autocompleteFragment.setPlaceFields(Arrays.asList(Place.Field.ID, Place.Field.NAME,Place.Field.LAT_LNG));

        autocompleteFragment.setOnPlaceSelectedListener(new PlaceSelectionListener() {
            @Override
            public void onPlaceSelected(Place place) {
                if (place.getLatLng() != null){
                    addPoint(MarkerPoints, place.getLatLng());
                    addPath(MarkerPoints);
                }
                Log.i("PlaceLog", "Place: " + place.getName() + ", " + place.getId() + "," +place.getLatLng()) ;
            }

            @Override
            public void onError(Status status) {
                // TODO: Handle the error.
                Log.i("PlaceLog", "An error occurred: " + status);
            }
        });
    }

    public void addPoint(ArrayList<LatLng> MarkerPoints, LatLng point){
        LatLng carPosition = new LatLng((ConnectBT.getCoordinates()[0]), ConnectBT.getCoordinates()[1] );
        mMap.addMarker(new MarkerOptions().position(carPosition).title("Marker at Car").icon((BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN))));

        // Already one location
        if (MarkerPoints.size() > 0) {
            MarkerPoints.clear();
            mMap.clear();
            mMap.addMarker(new MarkerOptions().position(carPosition).title("Marker at Car").icon((BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN))));
        }

        // Adding new item to the ArrayList
        MarkerPoints.add(point);

        // Creating MarkerOptions
        MarkerOptions options = new MarkerOptions();

        // Setting the position of the marker
        options.position(point);

        /**
         * For the start location, the color of marker is GREEN and
         * for the end location, the color of marker is RED.
         */
        if (MarkerPoints.size() == 1) {
            options.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED));

        }


        // Add new marker to the Google Map Android API V2
        mMap.addMarker(options);


    }

    public void addPath(ArrayList<LatLng> MarkerPoints){
        // Checks, whether start and end locations are captured
        if (MarkerPoints.size() >= 1) {
            LatLng origin = new LatLng((ConnectBT.getCoordinates()[0]), ConnectBT.getCoordinates()[1] );
            LatLng dest = MarkerPoints.get(0);

            //Prepare request to Google Directions API
            String url = getUrl(origin, dest);
            Log.d("onMapClick", url);
            FetchUrl FetchUrl = new FetchUrl(mMap);

            // Start downloading json data from Google Directions API
            FetchUrl.execute(url);


            //move map camera
            mMap.moveCamera(CameraUpdateFactory.newLatLng(origin));
            mMap.animateCamera(CameraUpdateFactory.zoomTo(15));
        }
    }

    private String getUrl(LatLng origin, LatLng dest) {
        return "https://maps.googleapis.com/maps/api/directions/json?" +
                "origin=" + origin.latitude + ","+ origin.longitude + "&destination=" + dest.latitude +","+ dest.longitude +
                "&key="+ getResources().getString(R.string.google_maps_key);
    }
}

