//
//  EnvelopeDemoApp.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//
import SwiftUI

@main
struct EnvelopeDemoApp: App {
    // entry point of app
    @StateObject var dataStore = DataStore.shared
    
    var body: some Scene {
        // returns apps interface
        WindowGroup {
            ContentView()
            // finish this, root view of app
                .environmentObject(dataStore)
        }
    }
}
