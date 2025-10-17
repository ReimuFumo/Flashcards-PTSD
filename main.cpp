#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include <random>
#include <chrono>
#include <iomanip>

class Statistics
{
    public:
    int totalReviewed = 0, totalRemembered = 0, totalForgotten = 0;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    void startTimer() { start = std::chrono::steady_clock::now(); }
    void stopTimer() { end = std::chrono::steady_clock::now(); }
    double secondsElapsed() const { return std::chrono::duration<double>(end - start).count(); } // Calculates time elapsed of session
    void reset() { totalReviewed = totalRemembered = totalForgotten = 0; } // Resets session summary
};

class Flashcards
{
    // Stored for functions like showing questions and answers
    std::vector<std::pair<std::string, std::string>> flashcard;
    std::string currQuestion;
    std::string currAnswer;

    // Revision session statistics
    Statistics stats;

    public:
    void welcome(); // Welcome/Starting page
    void help(); // Displays help manual when users need it
    void selectFile(); // Allows users to select a specific file

    private:
    void insertFlashcards(std::ifstream& file); // Insert flashcards from file into system
    void beginRevision(); // Starts session for reviewing flashcards
};

// The welcome page of the Flashcards Application
void Flashcards::welcome()
{
    std::string action;

    flashcard.clear(); // Prevents duplication of flashcards when inserting from file

    std::cout << "            ==============================\n";
    std::cout << "           |  Welcome To PTSD Flashcards  |\n";
    std::cout << "            ==============================\n";
    std::cout << "* Ensure all flashcard files are in the current directory! *\n\n";
    std::cout << "Enter 'select' to choose which file you want to revise or 'q' to exit the app." << "\n\n";
    std::cout << "If you do not know how to create one, please refer to the help manual. Enter 'help' to access the manual." << "\n\n";
    
    std::cout << ">> ";
    std::getline(std::cin, action);
    while (true)
    {
        if (action == "q" || action == "help" || action == "select") break;
        std::cout << "Invalid input! Try again.\n";
        std::cout << ">> ";
        std::getline(std::cin, action);
    }
    std::cout << "\n";

    if (action == "q") { std::cout << "Goodbye! ☺" << "\n"; exit(EXIT_SUCCESS); }
    else if (action == "help") help();
    else if (action == "select") selectFile();
}

// Help manual to answer questions the user may have
void Flashcards::help()
{
    std::string action;

    std::cout << "            =============================\n";
    std::cout << "           |         HELP MANUAL         |\n";
    std::cout << "            =============================\n";
    std::cout << "In order to insert your own questions and answers, you must first create a text file." << "\n";
    std::cout << "In the file, type in a question followed by ';' and then your answer. Example: What is the first letter of the alphabet?;a" << "\n";
    std::cout << "Each line holds a single question and answer." << "\n\n";
    std::cout << "Enter 'back' to return." << "\n\n";

    std::cout << ">> ";
    std::getline(std::cin, action); // Uses getline() to avoid whitespace issues
    std::cout << "\n";

    while (true)
    {
        if (action == "back") break;

        std::cout << "Invalid input! Try again.\n";
        std::cout << ">> ";
        std::getline(std::cin, action);
    }
}

// Ask user for file they want to use
void Flashcards::selectFile()
{
    std::string filename;

    std::cout << "            =============================\n";
    std::cout << "           |        SELECT A FILE        |\n";
    std::cout << "            =============================\n\n";

    while (true)
    {
        std::cout << "Enter file name or 'back' to return.\n\n";
        std::cout << ">> ";
        std::getline(std::cin, filename);
        std::cout << "\n";

        if (filename == "back") return; 
        else
        {
            // If file is not in current directory or does not exist, shows error
            std::ifstream file(filename);
            if (!file) std::cout << "File \"" << filename << "\" was not found. Please enter a valid file name.\n";
            else
            {
                std::cout << "* File loaded successfully! *\n\n";
                insertFlashcards(file);
                break;
            }
        }
    }
}

void Flashcards::insertFlashcards(std::ifstream& file)
{
    std::string line;
    std::string action;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        
        if (std::getline(ss, currQuestion, ';') && std::getline(ss, currAnswer))
        {
            if (!currQuestion.empty() && !currAnswer.empty()) flashcard.push_back({currQuestion, currAnswer});
        }
    }

    std::cout << "Enter 'y' to revise inserted flashcards or 'back' to return." << "\n\n";
    std::cout << ">> ";
    std::getline(std::cin, action);

    while (true)
    {
        if (action == "y" || action == "back") break;
        std::cout << "Invalid input! Try again.\n";
        std::cout << ">> ";
        std::getline(std::cin, action);
    }
    std::cout << "\n";

    if (action == "y") beginRevision();
}

// Beginning of revision/practice session 
void Flashcards::beginRevision()
{
    // Randomize flashcard order or not
    std::string randomOrNot;
    std::cout << "Would you like the flashcards to be presented in random order? Enter 'y' for yes or 'n' for no.\n\n";
    std::cout << ">> ";
    std::getline(std::cin, randomOrNot);
    std::cout << "\n";

    // Randomizes vector that stores the flashcards
    if (randomOrNot == "y")
    {
        std::shuffle(flashcard.begin(), flashcard.end(), std::mt19937(std::random_device{}())); 
        std::cout << "* Flashcards have been randomized! *\n\n";
    }

    // Begin practice session
    stats.reset(); // Reset currently stored stats
    stats.startTimer(); // Start timing current session

    std::cout << "Starting flashcard practice...\n";
    std::cout << "If you wish to leave the practice session at any time, enter 'back' when answering.\n\n";

    size_t index = 0;
    while (!flashcard.empty() && index < flashcard.size())
    {
        std::string question = flashcard[index].first;
        std::string answer = flashcard[index].second;
        std::string userInput;
        
        std::cout << "Q: " << question << "\n"; // Present question
        std::cout << "   (Press Enter to show answer) \n"; // Press enter key to show answer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Uses newline to show the answer (Enter makes newline)
        std::cout << "A: " << answer << "\n\n"; // Present answer
        std::cout << "[Enter '1' if remembered or '2' if forgotten]\n\n";
        std::getline(std::cin, userInput);
        std::cout << "\n";

        // Give user choice to leave current practice session and return to the welcome page
        if (userInput == "back")
        {
            stats.stopTimer();
            std::cout << "Exiting practice session...\n\n";
            break;
        }
        else if (userInput == "1")
        {
            flashcard.erase(flashcard.begin() + index);
            stats.totalReviewed++; // Increment number of reviewed and remembered flashcards
            stats.totalRemembered++;
        }
        else if (userInput == "2")
        {
            // If user picks '2' for forgotten, sends the flashcard to the back of the vector
            flashcard.push_back({question, answer});
            flashcard.erase(flashcard.begin() + index);
            stats.totalReviewed++; // Increment number of reviewed and forgotten flashcards
            stats.totalForgotten++;
        }
        else { std::cout << "Invalid input! Try again.\n"; continue; }

        // Congratulates user when all flashcards have been reviewed
        if (flashcard.empty()) { std::cout << "\nWoohoo! All cards remembered! Well done!\n\n"; break; }
    }

    stats.stopTimer(); // Stop timer

    // Display session summary/statistics
    std::cout << "===========================\n";
    std::cout << "      Session Summary       \n";
    std::cout << "===========================\n";
    std::cout << "Flashcards reviewed: " << stats.totalReviewed << "\n";
    std::cout << "Remembered: " << stats.totalRemembered << "\n";
    std::cout << "Forgotten: " << stats.totalForgotten << "\n";
    std::cout << "Total time spent: " << std::fixed << std::setprecision(1) << stats.secondsElapsed() << "s\n"; // Only shows numbers up to first decimal place
    std::cout << "===========================\n\n";
}

// Main
int main()
{
    Flashcards app;

    // Run the flashcards application
    while (true) app.welcome(); // Calls welcome() and uses while loop to prevent adding additional frames to call stack

    return 0;
}