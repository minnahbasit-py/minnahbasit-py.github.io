//
//  Landmark.swift
//  Landmarks
//
//  Created by Mia Basit on 5/26/24.
//


import Foundation
import SwiftUI
import CoreLocation

struct Landmark: Hashable, Codable, Identifiable {
    // codable makes it easier to move data btwn structure and a data file
    var id: Int
    var name: String
    var park: String
    var state: String
    var description: String
    private var imageName: String
    var image: Image {
        Image(imageName)
    }
    private var coordinates: Coordinates
    // will reflect json data structure
    var locationCoordinate: CLLocationCoordinate2D {
            CLLocationCoordinate2D(
                latitude: coordinates.latitude,
                longitude: coordinates.longitude)
        }
    struct Coordinates: Hashable, Codable {
        var latitude: Double
        var longitude: Double
    }
}
