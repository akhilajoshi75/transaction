#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Transaction {
public:
    Transaction(const std::string& description, double amount, bool isIncome)
        : description(description), amount(amount), isIncome(isIncome) {}

    double getAmount() const { return amount; }
    bool isIncomeTransaction() const { return isIncome; }

    std::string getTransactionType() const {
        return isIncome ? "Income" : "Expense";
    }

    std::string getDescription() const { return description; }

private:
    std::string description;
    double amount;
    bool isIncome;
};

class BudgetTracker {
public:
    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
        checkForAlert(transaction);
    }

    double calculateTotalIncome() {
        double totalIncome = 0.0;
        for (const Transaction& transaction : transactions) {
            if (transaction.isIncomeTransaction()) {
                totalIncome += transaction.getAmount();
            }
        }
        return totalIncome;
    }

    double calculateTotalExpenses() {
        double totalExpenses = 0.0;
        for (const Transaction& transaction : transactions) {
            if (!transaction.isIncomeTransaction()) {
                totalExpenses += transaction.getAmount();
            }
        }
        return totalExpenses;
    }

    void displaySummary() {
        std::cout << "\n--- Budget Summary ---" << std::endl;
        std::cout << "Total Income: $" << calculateTotalIncome() << std::endl;
        std::cout << "Total Expenses: $" << calculateTotalExpenses() << std::endl;
        std::cout << "Balance: $" << calculateTotalIncome() - calculateTotalExpenses() << std::endl;
    }

    void checkForAlert(const Transaction& transaction) {
        double balance = calculateTotalIncome() - calculateTotalExpenses();
        if (balance < 0) {
            std::cout << "Alert: Your balance is negative! Consider adjusting your budget." << std::endl;
        }
    }

    void provideSuggestions() {
        double balance = calculateTotalIncome() - calculateTotalExpenses();
        if (balance >= 0) {
            std::cout << "Suggestions: You have a positive balance. Consider saving or investing some of it." << std::endl;
        } else {
            std::cout << "Suggestions: Review your expenses, reduce unnecessary spending, and create a budget plan to increase your savings." << std::endl;
        }
    }

private:
    std::vector<Transaction> transactions;
};

int main() {
    BudgetTracker budgetTracker;

    while (true) {
        std::string description;
        double amount;
        char transactionType;

        std::cout << "\nEnter transaction description: ";
        std::cin.ignore();
        std::getline(std::cin, description); // Allow for multi-word descriptions

        std::cout << "Enter transaction amount: $";
        while (!(std::cin >> amount) || amount < 0) {
            std::cout << "Invalid amount. Please enter a positive number: $";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Is this an income transaction? (Y/N): ";
        std::cin >> transactionType;
        while (transactionType != 'Y' && transactionType != 'y' && transactionType != 'N' && transactionType != 'n') {
            std::cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No: ";
            std::cin >> transactionType;
        }

        bool isIncome = (transactionType == 'Y' || transactionType == 'y');
        Transaction transaction(description, amount, isIncome);
        budgetTracker.addTransaction(transaction);

        char another;
        std::cout << "Do you want to add another transaction? (Y/N): ";
        std::cin >> another;
        while (another != 'Y' && another != 'y' && another != 'N' && another != 'n') {
            std::cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No: ";
            std::cin >> another;
        }

        if (another != 'Y' && another != 'y') {
            break;
        }
    }

    budgetTracker.displaySummary();
    budgetTracker.provideSuggestions();

    return 0;
}
