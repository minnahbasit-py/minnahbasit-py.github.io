//
//  Transaction.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//

import Foundation

struct Transaction: Identifiable {
    // transaction must conform to identifiable protocol -> needs id
    let id: UUID
    // universally unique identiifer
    let date: Date
    let description: String
    // descrip of transaction -> type of transaction
    let amount: Double
    let category: String
    // envelopes categories -> groceries, rent etc
    
    // initialize values
    init(id: UUID = UUID(), date: Date, description: String, amount: Double, category: String) {
        self.id = id
        self.date = date
        self.description = description
        self.amount = amount
        self.category = category
    }
}
