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
#include <map>

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
    // Map each folder to its flashcards
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> folders;
    std::string currQuestion;
    std::string currAnswer;

    // Revision session statistics
    Statistics stats;


    public:
    void welcome(); // Welcome/starting page
    void help(); // Displays help manual when users need it
    void selectFile(); // Allows users to select a specific file
    void selectFolder(); // allows users to select a specific folder

    private:
    void insertFlashcards(std::ifstream& file); // Insert flashcards from file into system 
    void beginRevision(const std::string& folderName); // Starts session for reviewing flashcards
};

// ------------------------- WELCOME() -------------------------
// The welcome page of the Flashcards Application
void Flashcards::welcome()
{
    std::string action;

    folders.clear(); // Prevents duplication of flashcards when inserting from file

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
        std::cout << "Invalid input! Try again.\n\n";
        std::cout << ">> ";
        std::getline(std::cin, action);
    }
    std::cout << "\n";

    if (action == "q") { std::cout << "Goodbye! ☺" << "\n"; exit(EXIT_SUCCESS); }
    else if (action == "help") help();
    else if (action == "select") selectFile();
}

// ------------------------- HELP() -------------------------
// Help manual to answer questions the user may have
void Flashcards::help()
{
    std::string action;

    std::cout << "            =============================\n";
    std::cout << "           |         HELP MANUAL         |\n";
    std::cout << "            =============================\n";
    std::cout << "In order to insert your own questions and answers, you must first create a text file." << "\n";
    std::cout << "In the file, type in a question followed by ';' and then your answer. Example: What is the first letter of the alphabet?;a" << "\n";
    std::cout << "Each line holds a single question and answer." << "\n";
    std::cout << "If you want to store these flashcards in folders, add '-' at the top, followed by a name.\n\n"
    std::cout << "Enter 'back' to return." << "\n\n";

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, action); // Uses getline() to avoid whitespace issues

        if (action == "back") return;
        else std::cout << "Invalid input! Try again.\n\n";
    }
}

// ------------------------- SELECTFILE() -------------------------
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

// ------------------------- INSERTFLASHCARDS() -------------------------
// Inserts flashcards from file into application
void Flashcards::insertFlashcards(std::ifstream& file)
{
    std::string line;
    std::string currentFolder = "General"; // default folder
    std::string action;

    // Finds folders and contents in file, push them into vector
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        if(line[0] == '-'){
            currentFolder = line.substr(1);
            currentFolder.erase(0, currentFolder.find_first_not_of(" \t"));
            folders[currentFolder];
        }
        else {
            std::stringstream ss(line);
            if (std::getline(ss, currQuestion, ';') && std::getline(ss, currAnswer))
            {
                if (!currQuestion.empty() && !currAnswer.empty())
                    folders[currentFolder].push_back({currQuestion, currAnswer});
            }
        }
    }

    while (true)
    {
        std::cout << "Enter 'y' to choose the flashcards in this file or 'back' to return." << "\n\n";
        std::cout << ">> ";
        std::getline(std::cin, action);
        std::cout << "\n";

        if (action == "y") selectFolder(); // Proceeds to selectFolder()
        else if (action == "back") return;
        else std::cout << "Invalid input! Try again.\n";
    }
    std::cout << "\n";
}

// ------------------------- SELECTFOLDER() -------------------------
// Asks user to review a specific folder or all
void Flashcards::selectFolder()
{
    std::string action;

    // Lists existing folders in file, including number of flashcards in each
    std::cout << "Folders: \n";
    for (auto &folder: folders) std::cout << " - " << folder.first << " (" << folder.second.size() << " flashcards)\n";
    
    // Display multiple options for user to choose
    std::cout << "\nOptions:\n";
    std::cout << "  'all'         - Review all folders\n"; // Review every flashcard in every folder (combination of all)
    std::cout << "  [folder name] - Review a specific folder\n"; // Review flashcards in a specific folder
    std::cout << "  'back'        - Return\n\n"; // Return
    std::cout << ">> ";
    std::getline(std::cin, action);
    std::cout << "\n";

    while (true)
    {
        if (action == "back") return;
        else if (action == "all")
        {
            // Inserts every single flashcard into a vector for review
            std::vector<std::pair<std::string,std::string>> allCards;

            for (auto &f : folders) allCards.insert(allCards.end(), f.second.begin(), f.second.end());
            std::swap(folders["All"], allCards);

            beginRevision("All");
            return;
        }
        else if (folders.find(action) != folders.end()) break;
        else std::cout << "Invalid input! Try again!\n\n";
        std::cout << ">> ";
        std::getline(std::cin, action);
        std::cout << "\n";
    }
    beginRevision(action);
}

// ------------------------- BEGINREVISION() -------------------------
// Beginning of revision/practice session
void Flashcards::beginRevision(const std::string& folderName)
{
    // Notifies user if chosen folder has no flashcards
    auto &cards = folders[folderName];
    if (cards.empty()) {
        std::cout << "No flashcards in this folder.\n";
        return;
    }

    std::string randomOrNot;

    // Randomizes vector that stores the flashcards
    while (true)
    {
        // Give users choice to randomie or not
        std::cout << "Would you like the flashcards to be presented in random order? Enter 'y' for yes or 'n' for no.\n\n";
        std::cout << ">> ";
        std::getline(std::cin, randomOrNot);
        std::cout << "\n";

        if (randomOrNot == "y")
        {
            std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device{}())); // Randomizer algorithm
            std::cout << "* Flashcards have been randomized! *\n\n";
            break;
        }
        else if (randomOrNot == "n") break;
        else std::cout << "Invalid input! Try again.\n";
    }

    // Begin practice session
    stats.reset(); // Reset currently stored stats
    stats.startTimer(); // Start timing current session

    std::cout << "Starting flashcard practice...\n";
    std::cout << "If you wish to leave the practice session at any time, enter 'back' when answering.\n\n";

    size_t index = 0;
    while (!cards.empty() && index < cards.size())
    {
        const std::pair<std::string, std::string>& card = cards[index];
        const std::string& question = card.first;
        const std::string& answer = card.second;

        std::string userInput;
        
        std::cout << "Q: " << question << "\n"; // Present question
        std::cout << "   (Press Enter to show answer) \n"; // Press enter key to show answer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Uses newline to show the answer (Enter makes newline)
        std::cout << "A: " << answer << "\n\n"; // Present answer
        std::cout << "[Enter '1' if remembered, '2' if forgotten, or 'back' to return]\n";
        std::getline(std::cin, userInput);
        std::cout << "\n";

        // Give user choice to leave current practice session and return to the welcome page
        if (userInput == "back")
        {
            stats.stopTimer(); // If user returns mid-session, stop timer
            std::cout << "Exiting practice session...\n\n";
            break;
        }
        else if (userInput == "1")
        {
            cards.erase(cards.begin() + index);
            stats.totalReviewed++; // Increment number of reviewed and remembered flashcards
            stats.totalRemembered++;
        }
        else if (userInput == "2")
        {
            // If user picks '2' for forgotten, sends the flashcard to the back of the vector
            cards.push_back({question, answer});
            cards.erase(cards.begin() + index);
            stats.totalReviewed++; // Increment number of reviewed and forgotten flashcards
            stats.totalForgotten++;
        }
        else { std::cout << "Invalid input! Try again.\n"; continue; }

        // Congratulates user when all flashcards have been reviewed
        if (cards.empty()) { std::cout << "\nWoohoo! All cards remembered! Well done!\n\n"; break; }
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

// ------------------------- MAIN() -------------------------
int main()
{
    Flashcards app;

    // Run the flashcards application
    while (true) app.welcome(); // Calls welcome() and uses while loop to prevent adding additional frames to call stack

    return 0;
}