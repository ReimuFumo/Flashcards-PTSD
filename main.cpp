#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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
};

// The welcome page of the Flashcards Application
void Flashcards::welcome()
{
    std::string action;

    std::cout << "Welcome to PTSD Flashcards!" << "\n";
    std::cout << "Make sure your flashcards file is inside the current directory." << "\n";
    std::cout << "Enter 'select' to choose which file you want to revise.'" << "\n\n";
    std::cout << "If you do not know how to create one, please refer to the help manual. Enter 'help' to access the manual." << "\n\n";
    
    std::cout << "Enter command: ";
    std::cin >> action;
    std::cout << "\n";

    if (action == "q") { std::cout << "Goodbye!" << "\n"; return; }
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

        std::cout << "Invalid input! Try again." << "\n";
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
        std::cout << "Enter the name of the file you want to select: ";
        std::cin >> filename;
        
        std::ifstream file(filename);
        if (!file) std::cout << "File \"" << filename << "\" was not found. Please enter a valid file name.\n";
        else
        {
            std::cout << "File loaded successfully!\n";
            insertFlashcards(filename);
            break;
        }
    }

    insertFlashcards(filename);
}

void Flashcards::insertFlashcards(const std::string& filename)
{
    return; // NOT IMPLEMENTED YET
}

// Main
int main()
{
    Flashcards app;

    while (true) app.welcome(); // Calls welcome() and uses while loop to prevent adding additional frames to call stack

    return 0;
}