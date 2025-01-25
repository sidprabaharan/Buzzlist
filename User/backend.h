#ifndef BACKEND_H
#define BACKEND_H

#include <string>

// Checks if the user exists with the given email and password.
// Returns true if the credentials are correct, otherwise false.
bool userExists(const std::string &email, const std::string &password);

// Registers a new user with the given email and password.
// Returns true if registration is successful, otherwise false.
bool registerUser(const std::string &email, const std::string &password);

#endif // BACKEND_H
