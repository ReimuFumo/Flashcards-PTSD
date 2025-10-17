#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include <random>
#include <map>

class Flashcards
{
    // // // Stored for functions like showing questions and answers
    // std::vector<std::pair<std::string, std::string>> flashcard;
    // std::string currQuestion;
    // std::string currAnswer;


    // Map each folder to its flashcards
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> folders;
    std::string currQuestion;
    std::string currAnswer;


    public:
    void welcome();
    void help();
    void selectFile();

    private:
    void insertFlashcards(const std::string& filename);
    void beginRevision();
    void beginFolderRevision(const std::string& folderName);
};

// The welcome page of the Flashcards Application
void Flashcards::welcome()
{
    std::string action;

    folders.clear(); // Prevents duplication of flashcards when inserting from file

    std::cout << "***************************\n";
    std::cout << "Welcome to PTSD Flashcards!" << "\n";
    std::cout << "Make sure your flashcards file is inside the current directory." << "\n";
    std::cout << "Enter 'select' to choose which file you want to revise or 'q' to exit the app." << "\n\n";
    std::cout << "If you do not know how to create one, please refer to the help manual. Enter 'help' to access the manual." << "\n\n";
    
    std::cout << "Enter command: ";
    std::getline(std::cin, action);
    while (true)
    {
        if (action == "q" || action == "help" || action == "select") break;
        std::cout << "Invalid input! Try again.\n";
        std::cout << "Enter command: ";
        std::getline(std::cin, action);
    }
    std::cout << "\n";

    if (action == "q") { std::cout << "Goodbye!" << "\n"; exit(EXIT_SUCCESS); }
    else if (action == "help") help();
    else if (action == "select") selectFile();
}

// Help manual for creating flashcards questions/answers
void Flashcards::help()
{
    std::string action;

    std::cout << "** Help Manual **" << "\n";
    std::cout << "In order to insert your own questions and answers, you must first create a text file." << "\n";
    std::cout << "In the file, type in a question followed by ';' and then your answer. Example: What is the first letter of the alphabet?;a" << "\n";
    std::cout << "Each line holds a single question and answer." << "\n\n";
    std::cout << "Enter 'back' to return." << "\n\n";

    std::cout << "Enter command: ";
    std::getline(std::cin, action);
    std::cout << "\n";

    while (true)
    {
        if (action == "back") break;

        std::cout << "Invalid input! Try again.\n";
        std::cout << "Enter command: ";
        std::getline(std::cin, action);
    }
}

// Ask for file name
void Flashcards::selectFile()
{
    std::string filename;

    while (true)
    {
        std::cout << "Enter the file name or 'back' to return: ";
        std::getline(std::cin, filename);
        std::cout << "\n";

        if (filename == "back") return; 
        else
        {
            std::ifstream file(filename);
            if (!file) std::cout << "File \"" << filename << "\" was not found. Please enter a valid file name.\n";
            else
            {
                std::cout << "File loaded successfully!\n\n";
                insertFlashcards(filename);
                break;
            }
        }
    }
}

void Flashcards::insertFlashcards(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::string currentFolder = "General"; // default folder
    std::string action;

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

    std::cout << "Enter 'y' to revise inserted flashcards or 'back' to return." << "\n\n";
    std::cout << "Enter command: ";
    std::getline(std::cin, action);

    while (true)
    {
        if (action == "y" || action == "back") break;
        std::cout << "Invalid input! Try again.\n";
        std::cout << "Enter command: ";
        std::getline(std::cin, action);
    }
    std::cout << "\n";

    if (action == "y") beginRevision();
}

//Menu for flashcards
void Flashcards::beginRevision()
{
    std::string action;

    std::cout << "Folders found: \n";
    for (auto &folder: folders)
        std::cout << " - " << folder.first << " (" << folder.second.size() << "cards) \n";
    
    std::cout << "\nOptions:\n";
    std::cout << "  all   - Revise all folders combined\n";
    std::cout << "  [name]- Revise a specific folder\n";
    std::cout << "  back  - Return to main menu\n\n";
    std::cout << "Enter command: ";
    std::getline(std::cin, action);
    std::cout << "\n";

    if(action == "back") return;
    else if(action == "all") {
        std::vector<std::pair<std::string,std::string>> allCards;
        for(auto &f : folders)
            allCards.insert(allCards.end(), f.second.begin(), f.second.end());
        std::swap(folders["All"], allCards);
        beginFolderRevision("All");
    }
    else if(folders.find(action) != folders.end()){
        beginFolderRevision(action);
    }
    else {
        std::cout << "Invalid Folder name! \n";
    }

}


// Beginning of revision/practice session
void Flashcards::beginFolderRevision(const std::string& folderName)
{
    auto &cards = folders[folderName];
    if (cards.empty()) {
        std::cout << "No flashcards in this folder.\n";
        return;
    }

    // Randomize flashcard order or not
    std::string randomOrNot;
    std::cout << "Would you like the flashcards to be presented in random order? Enter 'y' for yes or 'n' for no.\n\n";
    std::getline(std::cin, randomOrNot);
    std::cout <<"\n";

    if (randomOrNot == "y") std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device{}())); // Randomizes flashcard vector
    else std::cout << "Randomizing the flashcards...\n\n";

    // Begin practice session
    std::cout << "Starting flashcard practice...\n";
    std::cout << "If you wish to leave the practice session, enter 'back'.\n\n";

    size_t index = 0;
    while (!cards.empty() && index < cards.size())
    {
        const std::pair<std::string, std::string>& card = cards[index];
        const std::string& question = card.first;
        const std::string& answer = card.second;

        std::string userInput;
        
        std::cout << "Q: " << question << "\n"; // Present question
        std::cout << "> (Press enter to see answer)"; // Press enter key to show answer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Uses newline to show the answer (enter makes newline)
        std::cout << "A: " << answer << "\n\n"; // Present answer
        std::cout << "[Enter '1' if remembered or '2' if forgotten, or 'back' to quit]\n";
        std::getline(std::cin, userInput);
        std::cout << "\n";

        // Give user choice to leave current practice session and return to the welcome page
        if (userInput == "back") { std::cout << "Exiting practice session...\n\n"; break; }
        else if (userInput == "1") cards.erase(cards.begin() + index);
        else if (userInput == "2")
        {
            // If user picks '2' for forgotten, sends the flashcard to the back of the vector
            cards.push_back({question, answer});
            cards.erase(cards.begin() + index);
        }
        else std::cout << "Invalid input! Try again.\n";

        // Presented when user gets through all the flashcards
        if (cards.empty()) { std::cout << "\nWoohoo! All cards remembered! Well done!\n\n"; break; }
    }
    index++;
}

// Main
int main()
{
    Flashcards app;

    while (true) app.welcome(); // Calls welcome() and uses while loop to prevent adding additional frames to call stack


    return 0;
}