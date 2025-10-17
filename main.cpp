#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

class Flashcards
{
    // Stored for functions like showing questions and answers
    std::vector<std::pair<std::string, std::string>> flashcard;
    std::string currQuestion;
    std::string currAnswer;

    public:
    void welcome();
    void help();
    void selectFile();

    private:
    void insertFlashcards(const std::string& filename);
    void beginRevision();
};

// The welcome page of the Flashcards Application
void Flashcards::welcome()
{
    std::string action;

    flashcard.clear(); // Prevents duplication of flashcards when inserting from file

    std::cout << "***************************\n";
    std::cout << "Welcome to PTSD Flashcards!" << "\n";
    std::cout << "Make sure your flashcards file is inside the current directory." << "\n";
    std::cout << "Enter 'select' to choose which file you want to revise or 'q' to exit the app." << "\n\n";
    std::cout << "If you do not know how to create one, please refer to the help manual. Enter 'help' to access the manual." << "\n\n";
    
    std::cout << "Enter command: ";
    std::cin >> action;
    while (true)
    {
        if (action == "q" || action == "help" || action == "select") break;
        std::cout << "Invalid input! Try again.\n";
        std::cout << "Enter command: ";
        std::cin >> action;
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
    std::cin >> action;
    std::cout << "\n";

    while (true)
    {
        if (action == "back") break;

        std::cout << "Invalid input! Try again.\n";
        std::cout << "Enter command: ";
        std::cin >> action;
    }
}

// Ask for file name
void Flashcards::selectFile()
{
    std::string filename;

    while (true)
    {
        std::cout << "Enter the file name or 'back' to return: ";
        std::cin >> filename;

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
    std::string action;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        
        if (std::getline(ss, currQuestion, ';') && std::getline(ss, currAnswer))
        {
            if (!currQuestion.empty() && !currAnswer.empty()) flashcard.push_back({currQuestion, currAnswer});
        }
    }

    std::cout << "Enter 'y' to revise the flashcards or 'back' to return." << "\n\n";
    std::cout << "Enter command: ";
    std::cin >> action;

    while (true)
    {
        if (action == "y" || action == "back") break;
        std::cout << "Invalid input! Try again.\n";
        std::cout << "Enter command: ";
        std::cin >> action;
    }
    std::cout << "\n";

    if (action == "y") beginRevision();
}

void Flashcards::beginRevision()
{
    return; // NOT YET IMPLEMENTED
}

// Main
int main()
{
    Flashcards app;

    while (true) app.welcome(); // Calls welcome() and uses while loop to prevent adding additional frames to call stack


    return 0;
}