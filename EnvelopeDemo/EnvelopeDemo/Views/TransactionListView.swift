//
//  TransactionListView.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//

import SwiftUI


struct TransactionListView: View {
    // create obj that an observable objectwill view & own
    // intiializes new instance of transvm class
    //@StateObject private var viewModel = TransactionViewModel()
    // used later t make price red or green
    @State private var sortAscending: Bool = true
    // changes to state var isnt reflected to other part os app, local var
    @EnvironmentObject var dataStore: DataStore
    var body: some View {
        NavigationView {
            List {
                // loop through transactions in list
                ForEach(dataStore.transactions) {
                    transaction in
                    TransactionRow(transaction:transaction)
                }
//                ForEach(viewModel.transactions) { transaction in
//                    // display every transaction using the transacrowview
//                    TransactionRow(transaction: transaction)
//                }
            }
            .navigationTitle("Transactions") // title of nav bar
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    // button
                    Button(action: {
                        sortAscending.toggle() // for toggling sorting order
                    }) {
                        // change text to what user picks
                        if sortAscending {
                            Text("Sort Descending") // offer otjher
                        } else {
                            Text("Sort Ascending")
                        }
                    }
                }
            }
        }
    }
    private func sortTransactions() {
        if sortAscending 
        {
            dataStore.transactions.sort { $0.date < $1.date }
            // earliest transactions come first
        }
        else
        {
            dataStore.transactions.sort { $0.date > $1.date }
        }
    }
    // realized we wouldnt need to delete transactions if we are aiming to keep user accountable
//    private func deleteTransaction(at offsets: IndexSet) {
//        offsets.forEach { index in
//            // iterate over index set
//            dataStore.transactions.remove(at: index)
//        }
//    }
}


// View for displaying a single transaction
struct TransactionRow: View {
    var transaction: Transaction
    // reference to transaction object
    var body: some View {
        HStack {
            // hstack to align everything horizontally placed wrto eachother (children)
            VStack(alignment: .leading) {
                // aligns to left
                Text(transaction.description)
                    .font(.headline)
                // grocery shopping
                Text(transaction.category)
                    .font(.subheadline)
                // groceries
            }
            Spacer()
            // puts space between previous and next v stack
            VStack(alignment: .trailing) {
                // aligns children to right
                Text(transaction.amount, format: .currency(code: "USD"))
                    .foregroundColor(amountColor(transaction.amount))
                Text(transaction.date.formatted(date: .abbreviated, time: .omitted))
                    .font(.caption)
            }
        }
    }
    
    // if transaction.amount == neg return red else green
    private func amountColor(_ amount: Double) -> Color {
        if amount < 0 {
            return .red
        } else {
            return .green
        }
    }
    
}

struct TransactionListView_Previews: PreviewProvider {
    static var previews: some View {
        TransactionListView().environmentObject(DataStore.shared)
    }
}
