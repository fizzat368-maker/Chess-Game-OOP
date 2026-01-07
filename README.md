# ♟ Chess Game in C++ (Object-Oriented Programming)

A fully functional **console-based Chess game** developed in **C++** using strong **Object-Oriented Programming (OOP)** principles.  
This project follows official chess rules and demonstrates modular design, inheritance, and game logic handling.

---

## 📌 Project Overview

This Chess game simulates a real-world chess match between two players (White vs Black) on a standard **8×8 board**.  
All major chess rules and game-ending conditions are implemented, along with file handling for saving and loading games.

---

## ✨ Key Features

### ♜ Core Gameplay
- Standard **8×8 Chess Board**
- Correct initial placement of all pieces
- Turn-based gameplay (White and Black alternate turns)
- Illegal moves are prevented

### ♞ Chess Rules Implemented
- Valid movement rules for:
  - Pawn
  - Rook
  - Knight
  - Bishop
  - Queen
  - King
- **Check detection**
- **Checkmate detection**
- **Castling** (King-side & Queen-side)
- **En Passant**
- **Pawn Promotion**
  - Queen
  - Rook
  - Bishop
  - Knight

### ♝ Draw Conditions
- Stalemate
- Insufficient material
- (Optional) Threefold repetition
- (Optional) Fifty-move rule

### ♚ Additional Features
- Highlighting valid moves for the selected piece
- File-based **Save & Load** functionality
- Proper game-ending messages (Win / Draw)

---

## 🧠 Object-Oriented Design

The project is structured using OOP concepts:

- **Inheritance**: All chess pieces derive from a base `Piece` class
- **Polymorphism**: Each piece overrides movement logic
- **Encapsulation**: Board state, game rules, and player turns are handled through dedicated classes
- **Modular Design**: Each major component is separated into `.cpp` and `.h` files

---

## 📂 Project Structure

├── Bishop.cpp / Bishop.h
├── Board.cpp / Board.h
├── ConsoleUtils.cpp / ConsoleUtils.h
├── Game.cpp / Game.h
├── King.cpp / King.h
├── Knight.cpp / Knight.h
├── Menu.cpp / Menu.h
├── Pawn.cpp / Pawn.h
├── Piece.cpp / Piece.h
├── Position.cpp / Position.h
├── Queen.cpp / Queen.h
├── Rook.cpp / Rook.h
├── SaveLoad.cpp / SaveLoad.h
├── Settings.cpp / Settings.h
├── Main.cpp
└── README.md


---

## ▶ How to Run the Project

1. Open the project in any C++ compiler (Visual Studio / Code::Blocks / g++)
2. Compile **all `.cpp` files**
3. Run `Main.cpp`
4. Play the game using console input

---

## 🛠 Technologies Used

- **C++**
- **Object-Oriented Programming (OOP)**
- **File Handling**
- **Console-based UI**

---

## 🎯 Learning Outcomes

Through this project, I gained hands-on experience in:

- Designing large-scale C++ projects
- Applying OOP principles effectively
- Implementing complex game logic
- Handling edge cases like checkmate and draw conditions
- Using file I/O for persistent game state

---

## 👤 Author

**Fizza Tahir**  
C++ Developer | OOP Enthusiast | Beginner Game Developer
