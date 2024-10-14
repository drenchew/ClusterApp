# ClusterApp

ClusterApp is a C++ application that simulates a car cluster interface, including components like RPM and speedometer gauges. The project is built using the SDL2 library for rendering and provides a modular structure for creating and updating different types of gauges.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Contributing](#contributing)
- [License](#license)

## Features
- **RPM Gauge**: Displays engine RPM and updates the needle based on input values.
- **Speedometer**: Displays vehicle speed with smooth needle animation.
- **Modular Design**: Easily extendable for additional gauges or custom car cluster elements.
- **Thread-Safe Operations**: Uses `std::lock_guard` for safe multithreading.

## Installation

### Prerequisites
- **C++ Compiler**: Make sure you have a C++17 (or later) compatible compiler, such as `g++` or `clang++`.
- **Make**: Used to build the project if a Makefile is provided.
- **SDL2 Library**: The project depends on SDL2 for rendering. Make sure SDL2 is installed.

### Steps
1. **Clone the Repository**
   ```bash
   git clone https://github.com/drenchew/ClusterApp.git
   cd ClusterApp
   g++ -std=c++17 -o ClusterApp src/*.cpp -lSDL2 -pthread
   ./ClusterApp

Usage
Once the application is running, it will simulate a car cluster with the current available gauges (RPM and speedometer). The gauges will update based on simulated input values.

Dependencies
SDL2: Simple DirectMedia Layer library for 2D graphics rendering.
C++ Standard Library: For threading, synchronization, and other utilities.
Make sure you have SDL2 installed on your system. You can install it via package managers like apt, brew, or download it from the official website.

Contributing
Contributions are welcome! If you would like to improve this project, please follow these steps:

Fork the repository.
Create a new branch (git checkout -b feature-branch).
Commit your changes (git commit -am 'Add new feature').
Push to the branch (git push origin feature-branch).
Create a new Pull Request.
License
This project is licensed under the MIT License. See the LICENSE file for more information.
