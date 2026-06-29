#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Structure to bundle task properties together
struct Task {
    string description;
    bool isCompleted;
};

// Function prototypes
void addTask(vector<Task>& todoList);
void viewTasks(const vector<Task>& todoList);
void markTaskCompleted(vector<Task>& todoList);
void removeTask(vector<Task>& todoList);
void displayMenu();

int main() {
    vector<Task> todoList;
    int choice;
    bool running = true;

    cout << "=================================\n";
    cout << "    🚀 Simple To-Do Manager     \n";
    cout << "=================================\n";

    while (running) {
        displayMenu();
        cout << "Enter your choice (1-5): ";
        
        // Input validation for menu selection
        if (!(cin >> choice)) {
            cout << "❌ Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addTask(todoList);
                break;
            case 2:
                viewTasks(todoList);
                break;
            case 3:
                markTaskCompleted(todoList);
                break;
            case 4:
                removeTask(todoList);
                break;
            case 5:
                cout << "\nGoodbye! Have a productive day! 👋\n";
                running = false;
                break;
            default:
                cout << "❌ Invalid choice. Please select an option between 1 and 5.\n";
        }
    }

    return 0;
}

// Displays the interactive dashboard menu
void displayMenu() {
    cout << "\n--- Main Menu ---\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Remove Task\n";
    cout << "5. Exit\n";
    cout << "-----------------\n";
}

// Function to add a task to the list
void addTask(vector<Task>& todoList) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear trailing newlines
    
    cout << "\nEnter the task description: ";
    string taskDesc;
    getline(cin, taskDesc); // Use getline to allow spaces in task descriptions

    if (taskDesc.empty()) {
        cout << "❌ Task description cannot be empty!\n";
        return;
    }

    // Insert task as pending by default
    todoList.push_back({taskDesc, false});
    cout << "📝 Task added successfully!\n";
}

// Function to print all current tasks
void viewTasks(const vector<Task>& todoList) {
    if (todoList.empty()) {
        cout << "\n📭 Your to-do list is empty. Nice job!\n";
        return;
    }

    cout << "\n--- Your To-Do List ---\n";
    for (size_t i = 0; i < todoList.size(); ++i) {
        string status = todoList[i].isCompleted ? "[X] Completed" : "[ ] Pending";
        cout << i + 1 << ". " << status << " : " << todoList[i].description << "\n";
    }
    cout << "-----------------------\n";
}

// Function to mark a specific task index as completed
void markTaskCompleted(vector<Task>& todoList) {
    if (todoList.empty()) {
        cout << "\n❌ No tasks available to complete.\n";
        return;
    }

    viewTasks(todoList);
    cout << "Enter the number of the task to mark as completed: ";
    size_t index;

    if (!(cin >> index) || index < 1 || index > todoList.size()) {
        cout << "❌ Invalid task number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // Convert to 0-based index
    todoList[index - 1].isCompleted = true;
    cout << "✅ Task marked as completed!\n";
}

// Function to remove a task from the vector
void removeTask(vector<Task>& todoList) {
    if (todoList.empty()) {
        cout << "\n❌ No tasks available to remove.\n";
        return;
    }

    viewTasks(todoList);
    cout << "Enter the number of the task to remove: ";
    size_t index;

    if (!(cin >> index) || index < 1 || index > todoList.size()) {
        cout << "❌ Invalid task number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // Erase task from the vector
    todoList.erase(todoList.begin() + (index - 1));
    cout << "🗑️ Task removed successfully!\n";
}