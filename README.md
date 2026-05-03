# Console Word Search Game 🔎

**Developed:** Fall 2024 (Programming Fundamentals Final Project)

A fully interactive, robust console-based puzzle game built entirely in C++. This project demonstrates strong foundational skills in algorithmic logic, data persistence, and fault-tolerant system design.

## ✨ Features

* **Multi-Directional Algorithms:** Employs string-matching algorithms to detect hidden words across a 15x15 2D grid in all directions (horizontal, vertical, and diagonal).
* **Dynamic Difficulty:** Multiple difficulty levels tailored to challenge different players.
* **Persistent High-Scores:** Tracks and stores player high scores locally across multiple sessions.
* **Save & Resume Functionality:** Engineered a robust state-management system utilizing standard C++ File I/O (`fstream`) to serialize and restore game states, player data, and board configurations.
* **Fault-Tolerant Inputs:** Complete input validation and error handling to prevent program crashes from unexpected keystrokes or corrupted local save files.

## 🛠️ Tech Stack

* **Language:** C++
* **Libraries:** Standard Template Library (STL), `<iostream>`, `<fstream>`, `<string>`, `<vector>`
* **Architecture:** 2D Array manipulation, File I/O Serialization

## 🚀 How to Run

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/sohaibijaz940/wordsearchgame.git](https://github.com/sohaibijaz940/wordsearchgame.git)
