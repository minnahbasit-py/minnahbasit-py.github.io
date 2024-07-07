//
//  UberMapViewRepresentable.swift
//  UberClone
//
//  Created by Mia Basit on 4/7/24.
//

import Foundation
// allows us to create a view using UIKit and represent thru SwiftUI
import SwiftUI
import MapKit
struct UberMapViewRepresentable: UIViewRepresentable {
    let mapView = MKMapView()
    // UIkit map view kit
    let locationManager = LocationManager()
    @EnvironmentObject var locationViewModel : LocationSearchViewModel
    // this instance wont know abt any updates so we need to create an environment object
    //
    func makeUIView(context: Context) -> some UIView {
        mapView.delegate = context.coordinator
        // coordinator gives us access to coordinator in makeCoordinator
        // gives us mapkit functionality
        // can communicate thru coordinator which has mapkit in the ubermapview class 
        mapView.isRotateEnabled = false
        mapView.showsUserLocation = true
        mapView.userTrackingMode = .follow
        
        return mapView
        // func in charge of making map view
    }
    func updateUIView(_ uiView: UIViewType, context: Context) {
        // updates our map view in certain situations
        // when user selects location -> get direction to loc
        // this func triggered
        if let coordinate = locationViewModel.selectedLocationCoordinate {
            context.coordinator.addAndSelectAnnotation(withCoordinate: coordinate)
            // using context object thru coordinator which gives us access to addandselectannotion function
            //print("debug: selected location in map view \(selectedLocation)")
        }
    }
    func makeCoordinator() -> MapCoordinator {
        
        // will return custom class -> mapcoord
        return MapCoordinator(parent:self)
    }
}
//wrapper for a UIKit view that you use to integrate that view into ur SwiftUi view hierarchy
extension UberMapViewRepresentable {
    class MapCoordinator: NSObject, MKMapViewDelegate {
        // find out how protocols and delegates
        // coordinator is middleman between uiview and uikit frameowkr
        
        // map viewdeleg has generating directions
        // generating polylines cant use swiftUi component for this
        
        // PROPERTIES
        let parent: UberMapViewRepresentable
        // parent communicates with ubermapview and representable class
        // LIFECYCLE
        
        init(parent: UberMapViewRepresentable) {
            self.parent = parent
            super.init()
        }
        // MKMAPVIEW DELEGATE
        func mapView(_ mapView: MKMapView, didUpdate userLocation: MKUserLocation) {
            // want to access userloc and create region and this way we will zoom in on user loc and display it
            let region = MKCoordinateRegion(
                center: CLLocationCoordinate2D(latitude: userLocation.coordinate.latitude, longitude: userLocation.coordinate.longitude),
                span: MKCoordinateSpan(latitudeDelta: 0.05, longitudeDelta: 0.05)
                )
            parent.mapView.setRegion(region, animated: true)
            //
        }
        // HELPERS
        func addAndSelectAnnotation(withCoordinate coordinate: CLLocationCoordinate2D) {
            parent.mapView.removeAnnotations(parent.mapView.annotations)
            let anno = MKPointAnnotation()
            anno.coordinate = coordinate
            parent.mapView.addAnnotation(anno)
            parent.mapView.selectAnnotation(anno, animated:true)
            // select and jiggle animation
            parent.mapView.showAnnotations(parent.mapView.annotations, animated: true)
        }
        
        func getDestinationRoute(from userLocation:CLLocationCoordinate2D, to destination: CLLocationCoordinate2D, completion: @escaping(MKRoute) -> Void ) {
             //
            let userPlacemark = MKPlacemark(coordinate: userLocation)
            let request = MKDirections.Request()
        }
    }
}
