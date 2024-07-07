//
//  MapViewActionButton.swift
//  UberClone
//
//  Created by Mia Basit on 4/7/24.
//

import SwiftUI

struct MapViewActionButton: View {
    @Binding var showLocationSearchView: Bool
    
    //we need to provide preview with a value bc everytime we initialize the view we have to pass in this boolean to see if we should show this
    var body: some View {
        Button {
            withAnimation(.spring()) {
                showLocationSearchView.toggle()
                // spring animation from map view to location view
            }
            // bc it is bound to homeview state property it will change in homeview
            // homeview will reconfigure 
        }
        label: {
            Image(systemName: showLocationSearchView ? "arrow.left" : "line.3.horizontal")
            // when we show locasearch view then show back arrow 
            // makes box of asking user where they are going
                .font(.title2)
                .foregroundColor(.black)
                .padding()
                .background(.white)
                .clipShape(Circle())
                .shadow(color: .black, radius: 6)
        }
        .frame(maxWidth: .infinity, alignment: .leading)
    }
}

#Preview {
    MapViewActionButton(showLocationSearchView: .constant(true))
}
