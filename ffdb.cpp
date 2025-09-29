#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <vector>
#include <filesystem>

void validChar(char enteredChar []) {
  int length = strlen(enteredChar);
  while (true) {
    // if () {
    //   std::cout << enteredChar;
    //   break;
    // }
  }
}

struct option long_options[] = {
      {"help", no_argument, nullptr, 'h'},
      {"version", no_argument, nullptr, 'v'},
      {"create", no_argument, nullptr, 'c'},
      {"add", no_argument, nullptr, 'a'},
      {"update", no_argument, nullptr, 'u'},
      {"delete", no_argument, nullptr, 'd'},
  };

void helpStdOut() {
  std::cout << "Usage: FF tracker [options]\n"
                  << "--help OR -h           Show man page\n"
                  << "--version OR -v        CLI version\n"
                  << "--create or -c NAME    Create collection\n"
                  << "--add or -a            Add to collection\n"
                  << "--update or -u         Update collection\n"
                  << "--delete or -d         Delete from collection\n";
}

void dirChecker(std::string fPath) {
  if (!std::filesystem::exists(fPath) && !std::filesystem::is_directory(fPath)) {
          std::filesystem::create_directory(fPath);
        }
}

int main(int argc, char *argv[]) {
  std::cout << "FF cli tracker\n";

  int option;
  
  std::vector<std::string> collections;
  // Possible can just use std::cin::fail() -> returns bool, to check whether it's a char, therefore don't need
  // to check length, just need to check input contains valid chars.

  if (argc == 1) {
    std::cout << collections.size();
    helpStdOut();
} else {
    while ((option = getopt_long(argc, argv, "hvcaud", long_options, nullptr)) != -1) {
      switch (option) {

      case 'h':
        helpStdOut();
        return 0;

      case 'v':
        std::cout << "Version: 0.0.1\n";
        return 0;
      
      case 'c': {
        // getenv with "HOME" as the parameter will expand to "home/user/"
        const char* home = getenv("HOME");
        std::string homedir = home;
        if (home == NULL) {
          std::cout << "This is null";
        }
        std::string collectionName;
        std::cout << "What would you like to name your collection?\n";
        std::getline(std::cin, collectionName);
        std::cout << "Making " << collectionName << "...";
        std::string fPath = homedir + "/Documents/FF/";
        dirChecker(fPath);
        std::string finalPath = fPath + collectionName + ".txt";
        std::ofstream outfile(finalPath);
        std::cout << "Finished making " << finalPath;
        collections.push_back(collectionName);
        outfile.close();
      }
        return 0;

      case 'a':
        std::cout << "Enter the data you'd like to add to collection:\n";
        break;
      case 'u':
        std::cout << "Which card do you want to update?\n";
        break;
      case 'd':
        std::cout
            << "Are you sure you want to delete this collection? [Y]es, [N]o\n";
        break;
      }
    };
  }
  return 0;
}
