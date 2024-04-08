 //
//  HomeView.swift
//  UberClone
//
//  Created by Mia Basit on 4/7/24.
//

import SwiftUI

struct HomeView: View {
    @State private var showLocationSearchView = false
    // if false show activation view if true show activation view
    var body: some View {
        ZStack(alignment: .top) {
            UberMapViewRepresentable()
                .ignoresSafeArea()
            // stretches to fit screen
            if showLocationSearchView {
                LocationSearchView(showLocationSearchView: $showLocationSearchView)
            }
            else {
                LocationSearchActivationView()
                    .padding(.top, 72)
                    .onTapGesture {
                        withAnimation(.spring()) {
                            showLocationSearchView.toggle()
                        }
                    }
            }
            MapViewActionButton(showLocationSearchView: $showLocationSearchView)
                // when property changes in mapviewactionbtn class it will change here too and then go through logic
                .padding(.leading)
                .padding(.top,4)
        }
    }
}

#Preview {
    HomeView()
}
