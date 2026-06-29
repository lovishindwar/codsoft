#include <iostream>
#include <limits>

using namespace std;

// Function prototypes
void showMenu();
void clearInputBuffer();

int main() {
    double num1, num2;
    int choice;

    cout << "--- Simple C++ Calculator ---" << endl;

    while (true) {
        showMenu();
        cin >> choice;

        // Check for invalid input (e.g., if the user types a letter)
        if (cin.fail()) {
            cout << "Invalid choice! Please enter a number between 1 and 5." << endl;
            clearInputBuffer();
            continue;
        }

        if (choice == 5) {
            cout << "Exiting the calculator. Goodbye!" << endl;
            break;
        }

        if (choice >= 1 && choice <= 4) {
            cout << "Enter first number: ";
            cin >> num1;
            cout << "Enter second number: ";
            cin >> num2;

            // Check if number inputs are valid
            if (cin.fail()) {
                cout << "Invalid input! Numbers must be numeric values." << endl;
                clearInputBuffer();
                continue;
            }

            // Perform operation based on user choice
            switch (choice) {
                case 1:
                    cout << "Result: " << num1 << " + " << num2 << " = " << (num1 + num2) << endl;
                    break;
                case 2:
                    cout << "Result: " << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
                    break;
                case 3:
                    cout << "Result: " << num1 << " * " << num2 << " = " << (num1 * num2) << endl;
                    break;
                case 4:
                    if (num2 == 0) {
                        cout << "Error! Division by zero is not allowed." << endl;
                    } else {
                        cout << "Result: " << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
                    }
                    break;
            }
        } else {
            cout << "Invalid choice! Please select a valid option (1-5)." << endl;
        }
    }

    return 0;
}

// Function to display the menu options
void showMenu() {
    cout << "\nSelect an operation:" << endl;
    cout << "1. Addition (+)" << endl;
    cout << "2. Subtraction (-)" << endl;
    cout << "3. Multiplication (*)" << endl;
    cout << "4. Division (/)" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice (1-5): ";
}

// Helper function to clear input stream errors and buffer
void clearInputBuffer() {
    cin.clear(); // clear error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
}