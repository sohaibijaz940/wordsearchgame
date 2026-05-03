#include <iostream>
#include <fstream>
#include <windows.h>
#include <cctype> 

using namespace std;

// Function to compare two strings (CASE INSENSITIVE)
bool compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (toupper(str1[i]) != toupper(str2[i])) {
            return false;
        }
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0');
}

// Function to display the game board
void displayBoard(const char board[15][15], const char* playerName, int score, int lives) {
    system("cls"); // Clear the console
    cout << "\t\tWORD SEARCH GAME\n";
    cout << "Player: " << playerName << "\n";
    cout << "SCORE: " << score << "\tLIVES: " << lives << "\n";
    for (int row = 0; row < 15; ++row) {
        cout << "\t| ";
        for (int col = 0; col < 15; ++col) {
            cout << board[row][col] << " | ";
        }
        cout << "\n";
    }
}

// Function to check if the word exists in the dictionary
bool isWordInDictionary(const char* word) {
    ifstream fin("dictionary.txt");
    if (!fin.is_open()) return false;

    char dictWord[50];

    // Check original word
    while (fin >> dictWord) {
        if (compareStrings(word, dictWord)) {
            fin.close();
            return true;
        }
    }

    // Check reversed word
    int length = 0;
    while (word[length] != '\0') length++;

    char reversedWord[50];
    for (int i = 0; i < length; ++i) {
        reversedWord[i] = word[length - 1 - i];
    }
    reversedWord[length] = '\0';

    fin.clear();
    fin.seekg(0, ios::beg);

    while (fin >> dictWord) {
        if (compareStrings(reversedWord, dictWord)) {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

// Function to check for words based on difficulty level (CASE INSENSITIVE)
bool checkWord(const char board[15][15], const char* word, int level) {
    int length = 0;
    while (word[length] != '\0') length++;

    for (int row = 0; row < 15; ++row) {
        for (int col = 0; col < 15; ++col) {

            // Level 1, 2, 3: Horizontal
            if (level >= 1) {
                if (col + length <= 15) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row][col + k]) != toupper(word[k])) {
                            match = false;
                            break;
                        }
                    }
                    if (match) return true;
                }
                if (col - length + 1 >= 0) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row][col - k]) != toupper(word[k])) {
                            match = false;
                            break;
                        }
                    }
                    if (match) return true;
                }
            }

            // Level 2, 3: Vertical
            if (level >= 2) {
                if (row + length <= 15) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row + k][col]) != toupper(word[k])) {
                            match = false;
                            break;
                        }
                    }
                    if (match) return true;
                }
                if (row - length + 1 >= 0) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row - k][col]) != toupper(word[k])) {
                            match = false;
                            break;
                        }
                    }
                    if (match) return true;
                }
            }

            // Level 3: Diagonal
            if (level == 3) {
                if (row + length <= 15 && col + length <= 15) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row + k][col + k]) != toupper(word[k])) { match = false; break; }
                    }
                    if (match) return true;
                }
                if (row + length <= 15 && col - length + 1 >= 0) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row + k][col - k]) != toupper(word[k])) { match = false; break; }
                    }
                    if (match) return true;
                }
                if (row - length + 1 >= 0 && col + length <= 15) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row - k][col + k]) != toupper(word[k])) { match = false; break; }
                    }
                    if (match) return true;
                }
                if (row - length + 1 >= 0 && col - length + 1 >= 0) {
                    bool match = true;
                    for (int k = 0; k < length; ++k) {
                        if (toupper(board[row - k][col - k]) != toupper(word[k])) { match = false; break; }
                    }
                    if (match) return true;
                }
            }
        }
    }
    return false;
}

// Function to update high scores gracefully
void updateHighScore(int score) {
    int highScores[6] = { 0 };
    ifstream fin("Highscore.txt");
    if (fin.is_open()) {
        for (int i = 0; i < 5; ++i) {
            fin >> highScores[i];
        }
        fin.close();
    }

    highScores[5] = score;

    for (int i = 0; i < 6; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            if (highScores[i] < highScores[j]) {
                int temp = highScores[i];
                highScores[i] = highScores[j];
                highScores[j] = temp;
            }
        }
    }

    ofstream fout("Highscore.txt");
    for (int i = 0; i < 5; ++i) {
        fout << highScores[i] << " ";
    }
    fout.close();
}

// Function to count total words in the dictionary
int countTotalWordsInDictionary() {
    ifstream fin("dictionary.txt");
    if (!fin.is_open()) return 15; // default fail-safe

    int count = 0;
    char dictWord[50];
    while (fin >> dictWord) {
        count++;
    }
    fin.close();
    return count;
}

// Main Play Game Logic
void playGame(int level) {
    char board[15][15];
    char playerName[30];

    const char* filename = "BoardEasy.txt";
    if (level == 2) filename = "BoardMedium.txt";
    if (level == 3) filename = "BoardHard.txt";

    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "\nERROR: Could not find " << filename << "!\nMake sure it is in the project folder.\n\n";
        system("pause");
        return;
    }
    for (int row = 0; row < 15; ++row) {
        for (int col = 0; col < 15; ++col) {
            fin >> board[row][col];
        }
    }
    fin.close();

    cout << "Enter your name: ";
    cin >> playerName;

    int score = 0, lives = 3;
    char foundWords[100][50];
    int foundWordsCount = 0;
    char word[50];
    char choice;
    int totalWordsInDictionary = countTotalWordsInDictionary();

    while (lives > 0) {
        displayBoard(board, playerName, score, lives);
        cout << "Enter a word to search (or 'p' to pause): ";
        cin >> word;

        // Check for IN-GAME Pause
        if ((word[0] == 'p' || word[0] == 'P') && word[1] == '\0') {
            while (true) {
                cout << "Game paused. Press 'e' to exit to menu or 'r' to resume: ";
                cin >> choice;
                if (choice == 'e' || choice == 'E') {
                    return; // Exits back to main menu
                }
                else if (choice == 'r' || choice == 'R') {
                    cout << "Resuming game....\n";
                    break; // Breaks pause loop, continues playing
                }
                else {
                    cout << "Invalid input.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
            continue;
        }

        // Gameplay Loop
        if (!isWordInDictionary(word)) {
            cout << "Word not in dictionary.\n";
            lives--;
            system("pause");
        }
        else {
            bool alreadyFound = false;
            for (int i = 0; i < foundWordsCount; i++) {
                if (compareStrings(foundWords[i], word)) {
                    alreadyFound = true;
                    break;
                }
            }

            if (!alreadyFound) {
                if (checkWord(board, word, level)) {
                    score += 10;
                    for (int j = 0; j < 50; j++) {
                        foundWords[foundWordsCount][j] = word[j];
                        if (word[j] == '\0') break;
                    }
                    foundWordsCount++;
                    cout << "Word found! Score increased to: " << score << "\n";

                    if (foundWordsCount == totalWordsInDictionary) {
                        cout << "\n============================================\n";
                        cout << "  CONGRATULATIONS! YOU FOUND ALL THE WORDS!  \n";
                        cout << "============================================\n\n";
                        updateHighScore(score);
                        system("pause");
                        return; // Exits game after winning
                    }
                    system("pause");
                }
                else {
                    lives--;
                    cout << "Word not found on board. Lives left: " << lives << "\n";
                    system("pause");
                }
            }
            else {
                cout << "You've already found that word! Score remains the same.\n";
                system("pause");
            }
        }
    }

    updateHighScore(score);
    cout << "\nGame Over! Your final score: " << score << "\n";
    system("pause");
}

void displayMenu() {
    system("cls");
    cout << "\n\t*** WORD SEARCH MENU ***\n";
    cout << "Press N for New Game\n";
    cout << "Press H for High Scores\n";
    cout << "Press E for Exit\n";
    cout << "---------------------------\n";
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4); // Red Text

    char choice;
    int level = 0;

    do {
        displayMenu();
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 'n':
        case 'N':
            cout << "Select Difficulty (1: Easy, 2: Intermediate, 3: Hard): ";

            // Input validation to prevent infinite loop crash
            if (!(cin >> level) || level < 1 || level > 3) {
                cout << "Invalid difficulty level! Please enter a number (1, 2, or 3).\n";
                cin.clear(); // Clears the crash state of cin
                cin.ignore(1000, '\n'); // Flushes bad characters out
                system("pause");
            }
            else {
                playGame(level);
            }
            break;

        case 'h':
        case 'H': {
            int highScores[5] = { 0 };
            ifstream fin("Highscore.txt");
            cout << "\n--- High Scores ---\n";
            if (!fin.is_open()) {
                cout << "No high scores yet! Play a game to set one.\n";
            }
            else {
                for (int i = 0; i < 5; ++i) {
                    fin >> highScores[i];
                    cout << i + 1 << ". " << highScores[i] << " points\n";
                }
                fin.close();
            }
            system("pause");
            break;
        }

        case 'e':
        case 'E':
            cout << "Exiting the game... Thanks for playing!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            system("pause");
        }
    } while (choice != 'e' && choice != 'E');

    return 0;
}