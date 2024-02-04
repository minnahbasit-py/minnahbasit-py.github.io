//
//  SplitSCFirebase.swift
//  SplitSCApp
//
//  Created by Mia Basit on 1/30/24.
//

import SwiftUI
import Firebase


struct SplitSCFirebaseView: View {
    var body: some View {
        AuthenticationView()
    }
}

struct SplitSCFirebaseView_Previews: PreviewProvider {
    static var previews: some View {
        AuthenticationView()
    }
}

@main
struct SplitSCFirebase: App {
    @UIApplicationDelegateAdaptor(AppDelegate.self) var delegate
    
    var body: some Scene {
        WindowGroup {
            NavigationStack {
                AuthenticationView()
            }
        }
    }
}
class AppDelegate: NSObject, UIApplicationDelegate {
    // these functions are defined in app delegate
  func application(_ application: UIApplication,
                   didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
    FirebaseApp.configure()
    //print("Configured Firebase")
      
    return true
  }
}

//struct SplitSCFirebaseView: View {
//    var body: some View {
//        Text("Hello, World!")
//            .padding()
//    }
//}

//struct SplitSCFirebaseView_Previews: PreviewProvider {
//    static var previews: some View {
//        SplitSCFirebaseView()
//    }
//}
//


