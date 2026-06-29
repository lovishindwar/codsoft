#include <iostream>
#include <random> // Required for modern random number generation

int main() {
    // 1. Initialize the random number engine with a hardware seed
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // 2. Define the range for the random number (1 to 100 inclusive)
    std::uniform_int_distribution<> distr(1, 100);
    
    int secretNumber = distr(gen);
    int userGuess = 0;
    int attempts = 0;

    std::cout << "=================================\n";
    std::cout << "Welcome to the Number Guessing Game!\n";
    std::cout << "I have chosen a number between 1 and 100.\n";
    std::cout << "Can you guess what it is?\n";
    std::cout << "=================================\n\n";

    // 3. Game loop
    while (userGuess != secretNumber) {
        std::cout << "Enter your guess: ";
        std::cin >> userGuess;
        attempts++;

        // Provide feedback
        if (userGuess > secretNumber) {
            std::cout << "Too high! Try again.\n\n";
        } else if (userGuess < secretNumber) {
            std::cout << "Too low! Try again.\n\n";
        } else {
            std::cout << "\n Correct! You've guessed the number in " << attempts << " attempts!\n";
        }
    }

    return 0;
}
