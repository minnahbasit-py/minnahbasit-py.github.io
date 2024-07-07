//
//  BudgetCategory.swift
//  EnvelopeDemo
//
//  Created by Mia Basit on 5/27/24.
//

import Foundation

struct BudgetCategory: Identifiable {
    // for types that need to be uniquely identified - > id
    var id = UUID()
    var name: String
    var budget: Double
    var spent: Double
    
    var remaining: Double {
        budget - spent
    }
    var percentageUsed: Double {
        if budget > 0 {
            return (spent / budget) * 100
        } 
        else {
            return 0
        }
    }
}
