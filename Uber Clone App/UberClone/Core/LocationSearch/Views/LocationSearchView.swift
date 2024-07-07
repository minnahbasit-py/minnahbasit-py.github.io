//
//  LocationSearchView.swift
//  UberClone
//
//  Created by Mia Basit on 4/7/24.
//

import SwiftUI

struct LocationSearchView: View {
    @State private var startLocationText = ""
    @Binding var showLocationSearchView: Bool
    @EnvironmentObject var viewModel: LocationSearchViewModel
    // use singular instance in ubercloneapp
    // link text field in header view (where to) with query fragment property
    var body: some View {
        VStack {
            // header view
            HStack {
                VStack {
                    Circle()
                        .fill(Color(.systemGray3))
                        .frame(width: 6,height: 6)
                    Rectangle()
                        .fill(Color(.systemGray3))
                        .frame(width: 1,height: 24)
                    // destination and curr loc
                    Rectangle()
                        .fill(.black)
                    // darker circle for arrive ->UI touch
                        .frame(width: 6,height: 6)
                }
                VStack {
                    TextField("Current location", text:
                                $startLocationText)
                                .frame(height:32)
                                .background(Color(.systemGroupedBackground))
                                .padding(.trailing)
                    TextField("Where to?", text:
                                $viewModel.queryFragment)
                                .frame(height:32)
                                .background(Color(.systemGray4))
                    // nackground
                                .padding(.trailing)
                }
            }
            .padding(.horizontal)
            .padding(.top, 64)
            Divider()
                .padding(.vertical)
            ScrollView {
                VStack(alignment: .leading) {
                    ForEach(viewModel.results, id: \.self) {
                        result in
                        // loop through viewmodel results
                        // we will still have dummy data until we populate results cell
                        LocationSearchResultCell(
                            title: result.title,
                            subtitle:result.subtitle)
                        .onTapGesture {
                            viewModel.selectLocation(result)
                            showLocationSearchView.toggle()
                            // we will pass state property into presentation logic for loc search view
                        }
                        // populate this^ cell w data aka title and subtitle
                    }
                }
            }
            // even padding
        }
        .background(.white)
    }
}

#Preview {
    LocationSearchView(showLocationSearchView: .constant(false))
}
