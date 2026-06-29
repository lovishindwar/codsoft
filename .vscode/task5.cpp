#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// ==========================================
// 1. CLASSSES & STRUCTURES
// ==========================================

class Book {
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;

public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}

    // Getters and Setters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }

    void display() const {
        cout << left << setw(25) << title 
             << setw(20) << author 
             << setw(15) << isbn 
             << (isAvailable ? "Available" : "Checked Out") << "\n";
    }
};

struct Transaction {
    string isbn;
    string borrowerName;
    int checkoutDay;
    bool isActive;
};

// ==========================================
// 2. LIBRARY SYSTEM CLASS
// ==========================================
class Library {
private:
    vector<Book> books;
    vector<Transaction> transactions;
    int currentDay; // Simulating a timeline for fine calculation
    const int RENTAL_PERIOD = 14;
    const double FINE_PER_DAY = 1.00;

public:
    Library() : currentDay(1) {}

    void incrementDay() {
        currentDay++;
        cout << "\n📆 Time passes... It is now Day " << currentDay << ".\n";
    }

    int getCurrentDay() const { return currentDay; }

    // Add Book
    void addBook(const string& title, const string& author, const string& isbn) {
        books.push_back(Book(title, author, isbn));
        cout << "📚 Book added successfully!\n";
    }

    // Search Books
    void searchBooks(const string& query) const {
        string lowerQuery = query;
        transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

        cout << "\n-------------------------------------------------------------------\n";
        cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "ISBN" << "Status\n";
        cout << "-------------------------------------------------------------------\n";

        bool found = false;
        for (const auto& book : books) {
            string title = book.getTitle();
            string author = book.getAuthor();
            transform(title.begin(), title.end(), title.begin(), ::tolower);
            transform(author.begin(), author.end(), author.begin(), ::tolower);

            if (title.find(lowerQuery) != string::npos || 
                author.find(lowerQuery) != string::npos || 
                book.getIsbn() == query) {
                book.display();
                found = true;
            }
        }
        if (!found) cout << "No matching books found.\n";
        cout << "-------------------------------------------------------------------\n";
    }

    // Checkout Book
    void checkoutBook(const string& isbn, const string& borrower) {
        for (auto& book : books) {
            if (book.getIsbn() == isbn) {
                if (!book.getAvailability()) {
                    cout << "❌ Error: This book is already checked out!\n";
                    return;
                }
                book.setAvailability(false);
                transactions.push_back({isbn, borrower, currentDay, true});
                cout << "✅ Success: \"" << book.getTitle() << "\" checked out to " << borrower << " on Day " << currentDay << ".\n";
                cout << "ℹ️ Due Date: Day " << (currentDay + RENTAL_PERIOD) << "\n";
                return;
            }
        }
        cout << "❌ Error: Book with ISBN " << isbn << " not found.\n";
    }

    // Return Book & Calculate Fines
    void returnBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getIsbn() == isbn) {
                if (book.getAvailability()) {
                    cout << "❌ Error: This book is already inside the library.\n";
                    return;
                }

                // Find active transaction
                for (auto& tx : transactions) {
                    if (tx.isbn == isbn && tx.isActive) {
                        tx.isActive = false;
                        book.setAvailability(true);

                        int daysKept = currentDay - tx.checkoutDay;
                        cout << "✅ Success: \"" << book.getTitle() << "\" returned on Day " << currentDay << ".\n";
                        cout << "ℹ️ Days kept: " << daysKept << " (Max allowed: " << RENTAL_PERIOD << ")\n";

                        if (daysKept > RENTAL_PERIOD) {
                            int overdueDays = daysKept - RENTAL_PERIOD;
                            double fine = overdueDays * FINE_PER_DAY;
                            cout << "⚠️ OVERDUE FINE: " << overdueDays << " days late. Fine incurred: $" << fixed << setprecision(2) << fine << "\n";
                        } else {
                            cout << "🎉 Returned on time! No fines applied.\n";
                        }
                        return;
                    }
                }
            }
        }
        cout << "❌ Error: Transaction details matching ISBN " << isbn << " not found.\n";
    }

    // Display entire catalog
    void displayInventory() const {
        if (books.empty()) {
            cout << "\n📭 The library inventory is currently empty.\n";
            return;
        }
        cout << "\n--- Complete Library Catalog ---\n";
        cout << left << setw(25) << "Title" << setw(20) << "Author" << setw(15) << "ISBN" << "Status\n";
        cout << "-------------------------------------------------------------------\n";
        for (const auto& book : books) {
            book.display();
        }
    }
};

// ==========================================
// 3. USER INTERFACE HELPERS
// ==========================================
void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Library lib;
    
    // Seed data
    lib.addBook("The Great Gatsby", "F. Scott Fitzgerald", "1111");
    lib.addBook("1984", "George Orwell", "2222");
    lib.addBook("To Kill a Mockingbird", "Harper Lee", "3333");

    int choice;
    while (true) {
        cout << "\n=========================================\n";
        cout << "       🏛️  LIBRARY MANAGEMENT SYSTEM     \n";
        cout << "       Simulated Day Tracker: Day [" << lib.getCurrentDay() << "]\n";
        cout << "=========================================\n";
        cout << "1. Search for a Book\n";
        cout << "2. Check Out a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. Add a New Book to Inventory\n";
        cout << "5. View Entire Catalog\n";
        cout << "6. Advance Calendar (Simulate +1 Day)\n";
        cout << "7. Exit Application\n";
        cout << "-----------------------------------------\n";
        cout << "Select an option (1-7): ";

        if (!(cin >> choice)) {
            cout << "❌ Invalid input. Numbers only please.\n";
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: {
                cout << "Enter Title, Author, or ISBN query: ";
                string query;
                getline(cin, query);
                lib.searchBooks(query);
                break;
            }
            case 2: {
                cout << "Enter Book ISBN to check out: ";
                string isbn;
                getline(cin, isbn);
                cout << "Enter Borrower's Name: ";
                string borrower;
                getline(cin, borrower);
                lib.checkoutBook(isbn, borrower);
                break;
            }
            case 3: {
                cout << "Enter Book ISBN to return: ";
                string isbn;
                getline(cin, isbn);
                lib.returnBook(isbn);
                break;
            }
            case 4: {
                string title, author, isbn;
                cout << "Enter Title: ";  getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                cout << "Enter ISBN: ";   getline(cin, isbn);
                lib.addBook(title, author, isbn);
                break;
            }
            case 5:
                lib.displayInventory();
                break;
            case 6:
                lib.incrementDay();
                break;
            case 7:
                cout << "\nExiting Library Manager. Have a nice day!\n";
                return 0;
            default:
                cout << "❌ Choice out of bounds! Please pick from options 1-7.\n";
        }
    }
}