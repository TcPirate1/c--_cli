#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <locale>
#include <string>
#include <unistd.h>
#include <vector>

void validChar(char enteredChar) {
  // std::cin::get() obtains first char entered into input.
  // Check against this char.
  std::string validInput;
  validInput = "yn";
  while (true) {
    for (int i = 0; i <= validInput.length(); i++) {
      validInput[i] == enteredChar ? std::cout << "Same"
                                   : std::cout << "Different";
    }
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

void dirChecker(std::string &fPath) {
  if (!std::filesystem::exists(fPath) &&
      !std::filesystem::is_directory(fPath)) {
    std::cout << "Looks like this directory doesn't exist, do you want to "
                 "create it? [Y]es, [N]o\n";
    char input = std::cin.get();
    std::tolower(input, std::locale());
    if (input == 'y') {
      std::filesystem::create_directory(fPath);
      std::cout << "\nCreating directory...";
    }
  }
  std::cout << "\nDirectory exists\n";
}

bool fileChecker(std::string &file) {
  char input;
  if (access(file.c_str(), F_OK) != -1) {
    std::cout << "\nFile exists\nDo you want to overwrite " << file
              << "? [Y]es [N]o\n";
    input = std::cin.get();
    std::tolower(input, std::locale());
  }
  if (input == 'y') {
    return 1;
  }
  return 0;
}

void vectorListing(std::vector<std::string> &collections) {
  if (collections.empty()) {
    std::cout << "\nThere's nothing inside :(";
  } else {
    std::cout << "\nCollections:\n";
    for (std::string i: collections) {
      std::cout << i << "\n";
    }
  }
}

// Add output listing all the vectors. Find ~/Documents/FF/ and add all files
// inside that end with .csv

int main(int argc, char *argv[]) {
  std::cout << "FF cli tracker\n";

  const char *home = getenv("HOME");
  if (home == NULL) {
    std::cerr << "This is null";
  }
  std::string homedir = home;
  std::string defaultDir = homedir + "/Documents/FF/";

  std::vector<std::string> collections;

  for (const auto &entry : std::filesystem::directory_iterator(defaultDir)) {
    if (entry.path().extension() == ".csv") {
      std::cout << entry.path();
      collections.push_back(entry.path());
    }
  }

  vectorListing(collections);

  int option;

  while ((option = getopt_long(argc, argv, "hvcaud", long_options, nullptr)) !=
         -1) {
    switch (option) {

    case 'h':
      helpStdOut();
      return 1;

    case 'v':
      std::cout << "Version: 0.0.1\n";
      return 1;

    case 'c': {
      std::string collectionName;
      std::cout << "What would you like to name your collection?\n";
      std::getline(std::cin, collectionName);
      std::cout << "Making " << collectionName << ".csv";
      defaultDir = homedir + "/Documents/FF/";
      dirChecker(defaultDir);
      std::string finalPath = defaultDir + collectionName + ".csv";
      if (fileChecker(finalPath)) {
        std::ofstream outfile(finalPath);
        std::cout << finalPath << "overwritten";
      }
      if (!fileChecker(finalPath)) {
        std::ofstream outfile(finalPath);
        std::cout << "finished making " << collectionName;
      }
      collections.push_back(collectionName + ".csv");
      vectorListing(collections);
    }
      return 1;

    case 'a':
      std::cout << "Enter the data you'd like to add to collection:\n";
      break;
    case 'u':
      std::cout << "Which card do you want to update?\n";
      break;
    case 'd':
      std::cout
          << "Are you sure you want to delete this collection? [Y]es, [N]o\n";
      // char input = std::cin.get();
      // validChar(input);
      break;
    default:
      helpStdOut();
      break;
    }
  };
  return 1;
}
