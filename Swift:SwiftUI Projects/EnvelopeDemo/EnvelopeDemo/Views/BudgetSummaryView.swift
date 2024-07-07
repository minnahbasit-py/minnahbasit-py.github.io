//
//  SwiftUIView.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//

import SwiftUI

struct BudgetSummaryView: View {
    @EnvironmentObject var dataStore: DataStore

    var body: some View {
        List(dataStore.categories) { category in
            BudgetProgressBarView(categoryId: category.id)
        }
        .navigationTitle("Budget Summary")
    }
}

struct BudgetSummaryView_Previews: PreviewProvider {
    static var previews: some View {
        BudgetSummaryView()
            .environmentObject(DataStore.shared)
    }
}
