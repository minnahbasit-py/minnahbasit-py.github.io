//
//  TransactionViewModel.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//

import Foundation

class TransactionViewModel: ObservableObject {
    // observable makes it so that we can update views when data changes
    @Published var transactions: [Transaction] = []
    //var can be changed if another view uses transactions
    // empty arr of transactions

    init() {
        loadTransactions()
        // load in dummy data
    }

    func loadTransactions() {
        // In a real app, fetch data from a database or API
        // For demonstration, we'll use hardcoded data
        transactions = [
            Transaction(date: Date().addingTimeInterval(-86400 * 1), description: "Grocery Shopping", amount: -30.25, category: "Groceries"),
            // can also use calendar API but have to declare new vars yesterday twodaysago etc
            Transaction(date: Date().addingTimeInterval(-86400 * 2), description: "Salary", amount: 2000.00, category: "Income"),
            Transaction(date: Date().addingTimeInterval(-86400 * 3), description: "Cafe", amount: -5.75, category: "Eating Out"),
            Transaction(date: Date().addingTimeInterval(-86400 * 4), description: "Internet Bill", amount: -60.00, category: "Utilities")
        ]
    }

    func sortTransactions(ascending: Bool) {
        if ascending {
            transactions.sort 
            { 
                $0.date < $1.date
            }
        } 
        else {
            transactions.sort
            {
                $0.date > $1.date
            }
        }
    }
}

