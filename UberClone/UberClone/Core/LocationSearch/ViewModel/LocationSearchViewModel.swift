//
//  LocationSearchViewModel.swift
//  UberClone
//
//  Created by Mia Basit on 4/7/24.
//

import Foundation
import MapKit


// SwiftUI framework for being able to search locations


class LocationSearchViewModel: NSObject, ObservableObject {
    // properties
    
    @Published var results = [MKLocalSearchCompletion()]
    @Published var selectedLocationCoordinate: CLLocationCoordinate2D?
    // search up mkloclasearchcompletion code
    
    // intiialized as a blank arr
    private let searchCompleter = MKLocalSearchCompleter()
    // obkect we will use to search for locs
    var queryFragment: String = "" {
        didSet {
            //print("DEBUG: query fragment is \(queryFragment)")
        // getting query fragment in our view model now
            searchCompleter.queryFragment = queryFragment
        }
    }
    // figure out how to update queryfragment
    override init() {
        super.init()
        // what is this for^
        searchCompleter.delegate = self
        searchCompleter.queryFragment = queryFragment
        // will finish our query frag when searching locs
    }
    // helpers
    func selectLocation(_ localSearch: MKLocalSearchCompletion) {
        // select loc
        locationSearch(forLocalSearchCompletion: localSearch) { response, error in
            if let error = error {
                print("DEBUG: Loc search failed with error \(error.localizedDescription)")
                return
                // dont continue executing
            }
            
            guard let item = response?.mapItems.first else { return}
            let coordinate = item.placemark.coordinate
            self.selectedLocationCoordinate = coordinate
            // here we access completion handle
            
        }
        //self.selectedLocation = location
        //print("DEBUG: selected loc is \(self.selectedLocation)")
        // we are storing loc somewhere now
    }
    // bc select loc only gives us address
    // helper function to take location to search for loc and geerate loc object
    func locationSearch(forLocalSearchCompletion localSearch: MKLocalSearchCompletion, completion: @escaping MKLocalSearch.CompletionHandler) {
        // configure search request
        let searchRequest = MKLocalSearch.Request()
        searchRequest.naturalLanguageQuery = localSearch.title.appending(localSearch.subtitle)
        // search request will us enatural lang query to search
        let search = MKLocalSearch(request: searchRequest)
        search.start(completionHandler: completion)
    }
    // this search uses API to give back results and it comes with the completion handler
    // using search request we'll make an actual loc object w lat and long
    
}


// section for mklocalsearchcompleterdelegate
extension LocationSearchViewModel: MKLocalSearchCompleterDelegate {
    func completerDidUpdateResults(_ completer: MKLocalSearchCompleter) {
        // mklocationsearchcompleter framwowrk, when it executes search under query fragment, this function is called, and then results are given back UNDER the hood
        // takes query fragment, executes search in background, once search results r populated, then it calls delegate method under the hood, then we can do what we want with th eresults
        self.results = completer.results
        // set results array
    }
}
