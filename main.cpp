#include <iostream>
#include <filesystem>
#include "BackEnd/Api/api.h"
int main() {
    // Use std::filesystem::current_path() to get the current working directory
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Convert the path to a string and print it
    std::cout << "Current working directory: " << currentPath.string() << std::endl;
    Initialize();
    return 0;
}