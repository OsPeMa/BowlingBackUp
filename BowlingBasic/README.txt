Bowling Score Tracker - Unreal C++ Assignment

~Project Overview~

This project is a technical assignment focused on implementing a fully functional bowling scoring system using Unreal Engine 5 and C++. The goal is to demonstrate proficiency in C++ design, UI implementation, and clean code practices.

~Functionality~

Input up to 10 frames of bowling scores with support for strikes, spares, and bonus throws.
Dynamic score calculation following official bowling rules.
Visual representation of each frame with real-time score updates.
Editable player name field with confirmation logic.
Reset functionality to restart a match cleanly.

Mouse-only interaction enabled for UI-focused gameplay.

🎨 User Interface Design

The interface was designed with clarity, usability, and structure in mind:

Frames are aligned from left to right in traditional scoreboard format.

Player name input is cleanly isolated and visually intuitive.

Active frame is visually highlighted to indicate progress.

Reset and Quit buttons are color-coded for immediate understanding (green for safe actions, red for exit).

UI-only interaction mode ensures a smooth mouse-based experience with no character or camera interference.

🛠️ Technical Architecture

C++ Driven UI Logic

All core behavior (updating, resetting, scoring) is controlled from C++.

Blueprint widgets are used for layout, but interaction is controlled in code.

Interface-Based Communication

The project heavily uses interfaces to avoid casting, following solid Unreal practices:

IBowlingScoreUIInterface allows the GameMode to communicate with widgets without knowing their exact class.

Frame widgets implement the interface and react to score updates, enable/disable states, and reset events.

SOLID Principles in Practice

✅ S - Single Responsibility

Each class does one thing:

UWidgetBowlingScore only manages a single frame's display and input.

UWidgetScoreBoard manages UI container logic.

ABowlingGameModeBase manages game rules and state.

✅ O - Open/Closed

Widgets can be extended without modifying the GameMode.

✅ L - Liskov Substitution

Everything that implements the IBowlingScoreUIInterface can be used interchangeably.

✅ I - Interface Segregation

IBowlingScoreUIInterface is clean and specific to UI control.

✅ D - Dependency Inversion

UI logic depends on interfaces, not concrete widgets.

🚀 Features Summary

Clean, consistent C++ architecture.

Interface-driven communication.

Professional UI with input flow control.

Real-time bowling logic with score propagation.

Reset and rename support.

🧠 Final Notes

The project was built to simulate a real-world production environment, with readable code, consistent style, and a focus on testability, modularity, and reusability.