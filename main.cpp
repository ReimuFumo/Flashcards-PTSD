#include <string>
#include <iostream>
#include <fstream>

class Flashcards
{
    public:
    void welcome();
    void help();
    void insertFile(const std::string& fileName);
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
    else if (action == "select") insertFile();
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

    welcome();
}

// Insert flashcards text file name
void Flashcards::insertFile(const std::string& fileName)
{
    return;
}

// Main
int main()
{
    Flashcards a;

    a.welcome();

    return 0;
}