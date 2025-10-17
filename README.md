# Flashcards-PTSD

## Scope
The flashcard application is designed to help users study efficiently using information memorisation techniques. Users can **insert, view, edit, and delete flashcards**, with each one containing information on any topic. Flashcards can be organised into **groups and folders**, giving users freedom to customise their study sessions.  

Users can choose to have the flashcards presented **randomly** or **sequentially**, or even **combine all flashcard groups** into a single study session. Each flashcard can be marked to indicate whether it was answered **correctly, incorrectly, or forgotten**. At the end of a study session, users can view statistics such as:  

- Number of cards reviewed  
- Number of correct and incorrect answers  
- Time spent studying  

---

## Modifications to the Scope
To track correctness:  

- After viewing a flashcard, users are prompted to enter:  
  - `1` → Correct  
  - `2` → Incorrect/forgotten  
- If a flashcard is answered incorrectly or forgotten, it is **added back to the start** of the review session so the user can attempt it again.  

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
