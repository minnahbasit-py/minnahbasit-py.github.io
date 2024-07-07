//
//  CircleImage.swift
//  Landmarks
//
//  Created by Mia Basit on 5/26/24.
//

import SwiftUI

struct CircleImage: View {
    var image: Image
    var body: some View {
        image
            .clipShape(Circle())
                        .overlay {
                            Circle().stroke(.white, lineWidth: 4)
                        }
                        .shadow(radius: 7)
            
//        Image("uber")
//            .resizable()
//            .scaledToFit()
//            .clipShape(Circle())
    }
}

#Preview {
    CircleImage(image: Image("uber"))
}
