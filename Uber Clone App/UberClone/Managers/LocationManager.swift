//
//  LocationManager.swift
//  UberClone
//
//  Created by Mia Basit on 4/7/24.
//

import CoreLocation

// handles

class LocationManager: NSObject, ObservableObject {
    private let locationManager = CLLocationManager()
    
    override init() {
        super.init()
        // what does super init do
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        // gives us most accurate loc
        locationManager.requestWhenInUseAuthorization()
        // allows us to request user loc permissions
        locationManager.startUpdatingLocation()
        //updates users loc and updates it
    }
}

extension LocationManager: CLLocationManagerDelegate {
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        // want to make sure loc array isnt empty
        guard !locations.isEmpty else { return }
        locationManager.stopUpdatingLocation()
        //print(locations.first)
        // in console u can see you will keep on getting users location
        // users loc is constantly updated but when u get it we should
        // stop udating thru locationmanager.stopupdating
    }
    // function gets called when users location updates
}
