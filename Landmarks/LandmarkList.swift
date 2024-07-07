//
//  LandmarkList.swift
//  Landmarks
//
//  Created by Mia Basit on 5/27/24.
//

import SwiftUI

struct LandmarkList: View {//
    // conforming to the view protocol
    // allows landmark list to be used as a view anywhere
    var body: some View {
        NavigationSplitView {
            // navigationsplitview is a custom swiftui view that
            // provides a split view layout with detail interface
            // content here is displayed in master view
            List(landmarks) { landmark in
                // initialize list view w landmarks as data src
                NavigationLink {
                    LandmarkDetail(landmark: landmark)
                    // in each nav link, display landmark row view, pass landmark in
                } label: {
                    LandmarkRow(landmark: landmark)
                }
            }
            .navigationTitle("Landmarks")
            // srt nav title of view to landmarks
        }
        detail: {
             //detail is displayed in detail view
            Text("Select a Landmark")
        }
    }
}


#Preview {
    LandmarkList()
}
