import SwiftUI

struct BudgetProgressBarView: View {
    @EnvironmentObject var dataStore: DataStore
    var categoryId: UUID
    //var category: BudgetCategory
    // Computed property to extract the category from the data store
    var category: BudgetCategory? {
        dataStore.categories.first { $0.id == categoryId }
    }

    var body: some View {
        VStack(alignment: .leading) {
            if let category = category {
                Text(category.name)
                ProgressView(value: category.spent, total: category.budget)
                    .progressViewStyle(LinearProgressViewStyle(tint: progressColor(category)))
                budgetInfo(category)
            } else {
                Text("Category not found")
            }
        }
        .padding()
    }
    
    // This function returns detailed budget info for a given category
    private func budgetInfo(_ category: BudgetCategory) -> some View {
        HStack {
            Text("$\(category.spent, specifier: "%.2f") spent of $\(category.budget, specifier: "%.2f")")
            Spacer()
            Text("\(Int(category.percentageUsed))%")
        }
        .font(.caption)
    }

    // Determines the color of the progress bar based on budget usage
    private func progressColor(_ category: BudgetCategory) -> Color {
        category.spent > category.budget ? .red : .blue
    }
}

// Providing a sample preview with a mock data store if needed
struct BudgetProgressBarView_Previews: PreviewProvider {
    static var previews: some View {
        let dataStore = DataStore.shared
        return BudgetProgressBarView(categoryId: dataStore.categories.first!.id)
            .environmentObject(dataStore)
    }
}

//struct BudgetProgressBarView_Previews: PreviewProvider {
//    static var previews: some View {
//        // Creating a List to display each category in a separate BudgetProgressBarView using ForEach
//        List {
//            ForEach(demoCategories, id: \.id) { category in
//                BudgetProgressBarView(category: category)
//            }
//        }
//    }
//}
//
//// Example categories for previewing the component
//let demoCategories = [
//    BudgetCategory(name: "Dining", budget: 150, spent: 50),
//    BudgetCategory(name: "Utilities", budget: 100, spent: 75),
//    BudgetCategory(name: "Entertainment", budget: 200, spent: 150)
//]
