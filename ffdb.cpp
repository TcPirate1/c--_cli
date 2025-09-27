#include <fstream>
#include <getopt.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  int option;
  struct option long_options[] = {
      {"help", no_argument, nullptr, 'h'},
      {"version", no_argument, nullptr, 'v'},
      {"create", no_argument, nullptr, 'c'},
      {"add", no_argument, nullptr, 'a'},
      {"update", no_argument, nullptr, 'u'},
      {"delete", no_argument, nullptr, 'd'},
  };
  std::vector<int> collections;
  std::string collectionName;
  std::ofstream outfile;
  if (argc > 4) {
    std::cout << "Too many options";
  }
  if (argc == 1) {
    std::cout << "List collections:\n";
  } else {
    while ((option = getopt_long(argc, argv, "hvcaud", long_options,
                                 nullptr)) != -1) {
      switch (option) {
      case 'h':
        std::cout << "FF cli database\n"
                  << "Usage: FFdb [options]\n"
                  << "--help OR -h           Show man page\n"
                  << "--version OR -v        CLI version\n"
                  << "--create or -c NAME    Create collection\n"
                  << "--add or -a            Add to collection\n"
                  << "--update or -u         Update collection\n"
                  << "--delete or -d         Delete from collection\n";
        return 0;
      case 'v':
        std::cout << "Version: 0.0.1\n";
        return 0;
      // Start by checking if there are any collections. IF there aren't any,
      // ask to create one. If there are collections, ask which one they'd like
      // to choose.
      case 'c':
        std::cout << "What would you like to name your collection?\n";
        getline(std::cin, collectionName);
        std::cout << "Making " << collectionName << "...";
        // The program should be able to detect the OS and find file path
        // to the Documents file.
        #if (__linux__)
        outfile.open(collectionName + ".txt");
        std::cout << "Finished making " << collectionName;
        outfile.close();
        #endif
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
