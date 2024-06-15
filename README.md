Solitaire Card Graphics Description:
This repository contains C++ code for a console-based solitaire card game with graphical representations using Unicode symbols and colored text.

Contents
1. ConsoleFunctions.h
Header file providing utility functions to interact with the console:
  Setting console title
  Setting cursor position
  Reading characters from console
  Handling mouse events (left and right clicks)
  Handling key press and release events
  Setting console text color and background color
  Clearing console screen
  Getting console window size and setting buffer size

2. ConsoleFunctions.cpp
   Implementation file for ConsoleFunctions.h, defining all the methods declared in the header. This file enables direct interaction with the Windows console API for various console manipulations required for the game.

3. oop proj.cpp
Main program file demonstrating the use of classes and objects for a card game simulation:
  PlayingCard class representing individual playing cards with rank, suit, and color.
  PileofCards class managing a collection of PlayingCard objects, supporting operations like adding, removing, checking emptiness, and fullness 
  of the pile.
  Deck class representing a deck of 52 PlayingCard objects, with operations like initialization, checking emptiness, removing cards, and printing 
  card details to the console.
  main() function demonstrating the usage of these classes to simulate adding cards to a pile, removing them, and displaying card graphics on the 
  console.

HOW TO USE:

1. Setup Environment
  Ensure you have a C++ compiler and a Windows environment to compile and run the code using Visual Studio or any other IDE supporting C++     
  development on Windows.
2. Compilation
  Compile all source files (ConsoleFunctions.cpp, oop proj.cpp) together with the header file ConsoleFunctions.h to build the executable.
3. Execution
  Run the compiled executable to see the console-based solitaire card game simulation.
  Follow the instructions and prompts displayed on the console to interact with the game.
4. Gameplay
  The game simulates basic card operations such as adding cards to a pile, removing cards from the pile, and displaying graphical 
  representations of cards using Unicode symbols.

Notes:
Ensure proper handling of console window size and buffer size to display the graphical card representations correctly.
The provided code demonstrates foundational concepts of object-oriented programming in C++ and interaction with the Windows console API for graphical display.


 

