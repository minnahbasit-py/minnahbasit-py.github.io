//
//  DataStore.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//


import Foundation

class DataStore: ObservableObject {
    static let shared = DataStore() // Singleton for easy global access
    
    // Published properties that the UI will listen to
    @Published var transactions: [Transaction] = []
    @Published var categories: [BudgetCategory] = []
    
    init() {
        loadInitialData()
    }
    
    // Load initial or demo data
    private func loadInitialData() {
        // Transactions
        transactions = [
            Transaction(date: Date().addingTimeInterval(-86400), description: "Grocery Shopping", amount: -30.25, category: "Groceries"),
            Transaction(date: Date().addingTimeInterval(-86400 * 2), description: "Salary", amount: 2000, category: "Income"),
            Transaction(date: Date().addingTimeInterval(-86400 * 3), description: "Cafe", amount: -5.75, category: "Eating Out"),
            Transaction(date: Date().addingTimeInterval(-86400 * 4), description: "Internet Bill", amount: -60, category: "Utilities")
        ]
        
        // Budget categories
        categories = [
                BudgetCategory(id: UUID(), name: "Dining", budget: 150, spent: 50),
                BudgetCategory(id: UUID(), name: "Utilities", budget: 100, spent: 75),
                BudgetCategory(id: UUID(), name: "Entertainment", budget: 200, spent: 150)
        ]
        categories.forEach { category in
            print("Loaded category ID: \(category.id)")
        }
        
        
    }
    
    // Add, update, or delete transactions
    func addTransaction(_ transaction: Transaction) {
        transactions.append(transaction)
    }
    
    func updateTransaction(_ transaction: Transaction) {
        if let index = transactions.firstIndex(where: { $0.id == transaction.id }) {
            transactions[index] = transaction
        }
    }
    
    func deleteTransaction(_ transaction: Transaction) {
        transactions.removeAll { $0.id == transaction.id }
    }
    
    // Add, update, or delete categories
    func addCategory(_ category: BudgetCategory) {
        categories.append(category)
    }
    
    func updateCategory(_ category: BudgetCategory) {
        if let index = categories.firstIndex(where: { $0.id == category.id }) {
            categories[index] = category
        }
    }
    
    func deleteCategory(_ category: BudgetCategory) {
        categories.removeAll { $0.id == category.id }
    }
}
