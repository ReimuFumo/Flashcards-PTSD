# Flashcards-PTSD
---
## James Lee (a1964984)
- Implemented core flashcard functions, allowing cycling through inserted flashcards.
- Implemented a way to present flashcards sequentially or in random order.
- Implemented session summary statistics, displaying user study details such as: number of reviewed flashcards, remembered flashcards, forgotten flashcards, and total time spent.
-  Debugged the application frequently throughout the process of creating the application.
## Blake Cross (a1921198)
- Implemented a folders system, enabling flashcards within files to be organised into named folders.
- Implemented a way to review every flashcard in each folder for an all-in-one studying experience.
- Responsible for constructing the majority of the README file, keeping it constantly updated throughout the process of creating the application.
- Responsible for frequent and critical testing of applications, creating multiple test files to test for edge cases. Tested debugged areas to ensure functions worked as intended.

## Motivation
The Flashcards-PTSD project was created to help users efficiently memorize information using flashcards. As our team have collectively benefited a lot from using flashcard applications to study, we wanted to provide a small, customizable study tool that allows organisation of flashcards for others. Not only do we want to help others with this simple tool, but it is good practice for us while we strive to create better tools in the future.

---
## Project Scope
The flashcard application is designed to help users study efficiently using information memorisation techniques. Users can **insert, view, edit, and delete flashcards**, with each one containing information on any topic. Flashcards can be organised into **groups and folders**, giving users freedom to customise their study sessions.  

Users can choose to have the flashcards presented **randomly** or **sequentially**, or even **combine all flashcard groups** into a single study session. Each flashcard can be marked to indicate whether it was answered **correctly, incorrectly, or forgotten**. At the end of a study session, users can view statistics such as:  

- Number of cards reviewed  
- Number of correct and incorrect answers  
- Time spent studying  

---

## Getting Started

To get started, in terminal:
```
git clone git@github.com:ReimuFumo/flashcards-ptsd.git
cd flashcards-ptsd
make
```
Or on a Windows CMD:
```
git clone git@github.com:ReimuFumo/flashcards-ptsd.git
cd flashcards-ptsd
make win
```

---

## Writing Flashcards

### Questions
- Each question is an **open-ended question**.  
- **Format**: Question and answer are separated by a **semicolon (`;`)**.  
- **Case-insensitive**: Answers are not case-sensitive.  

**Example:**  
`What is the capital of Australia?;Canberra`

### Folders
- To organise flashcards into folders, start the folder name with a hyphen (-).
- All flashcards following the folder name belong to that folder until another folder is defined.
  
**Example:**
```
-Math
2+2?;4
5×3?;15
-Science
H2O is commonly known as?;Water
The planet closest to the Sun?;Mercury
```

## Usage
- Launch the program.
- Choose one of the following commands:
- select → Choose a flashcards file to revise
- help → View the help manual
- q → Quit the application
- Once a flashcards file is selected, you can:
- Revise flashcards in random or sequential order
- Mark answers as correct or incorrect
- Track progress and statistics during your study session
- 
---

## Modifications to the Scope
To track correctness:  
- After viewing a flashcard, users are prompted to enter:  
  - `1` → Remembered  
  - `2` → Forgotten  
- Forgotten cards are **added back to the sstart of the review session** to allow repetition.
- This avoids redundancy and improves focus on retention.

---

## Notes
- Each time the application starts, previously loaded flashcards are clearede. This allows users to **select a different file** for each session.
- Only **one flashcard file** can be loaded per session. Multiple folders can be reviewed together using the **all** option.

---
