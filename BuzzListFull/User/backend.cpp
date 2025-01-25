#include "backend.h"
#include <fstream>
#include <string>
#include <vector>

// Helper function to read all lines from a file
std::vector<std::string> readFile(const std::string &filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Helper function to write a line to a file
void appendToFile(const std::string &filename, const std::string &line) {
    std::ofstream file(filename, std::ios::app);
    file << line << "\n";
}

// Checks if the user exists in the files with the correct password.
bool userExists(const std::string &email, const std::string &password) {
    std::vector<std::string> users = readFile("storedUsers.txt");
    std::vector<std::string> passes = readFile("storedPasses.txt");

    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i] == email && passes[i] == password) {
            return true;
        }
    }
    return false;
}

// Registers a new user by adding them to the files.
// Returns true if registration is successful, otherwise false if user already exists.
bool registerUser(const std::string &email, const std::string &password) {
    std::vector<std::string> users = readFile("storedUsers.txt");

    // Check if the user already exists
    for (const auto &user : users) {
        if (user == email) {
            return false; // User already exists
        }
    }

    // Append new user and password to files
    appendToFile("storedUsers.txt", email);
    appendToFile("storedPasses.txt", password);

    return true;
}
