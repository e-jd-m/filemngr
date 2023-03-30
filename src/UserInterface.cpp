#include "UserInterface.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <regex>
#include "COperation.h"

UserInterface::UserInterface () : fileManager(), cmdManager(fileManager), errorMsg(""), printHelp(false) {}


void clearScreen () {
  std::cout << "\033[2J";
  std::cout << "\033[0;0f";
  //system("clear");
}

void UserInterface::render () {
  const auto currentFiles = fileManager.listCurrentFiles();
  clearScreen();
  std::cout << "+" << std::string(CFileEntity::getPrintWidth() * 4, '-') << "+" << std::endl;
  std::cout << "|" << fileManager.getCurrentPath().string() << std::endl;

  std::cout << "+" << std::string(CFileEntity::getPrintWidth() * 4, '-') << "+" << std::endl;
  bool first = true;
  for ( const auto &f: currentFiles ) {
    if ( !first ) {
      std::cout << "+" << std::string(CFileEntity::getPrintWidth(), '-') << "+"
                << std::string(CFileEntity::getPrintWidth() * 3 - 1, '-') << "+" << std::endl;
    }
    std::cout << *f << std::endl;
    first = false;
  }
  std::cout << "+" << std::string(CFileEntity::getPrintWidth() * 4, '-') << "+" << std::endl;

}

void UserInterface::start () {
  std::string command;
  bool exit = false;
  while ( std::cin.good() && !exit ) {
    render();
    if ( errorMsg != "" ) {
      std::cout << "ERROR: " + errorMsg << std::endl;
    }
    if ( printHelp ) {
      std::cout << cmdManager.printHelp() << std::endl;
      printHelp = false;
    }
    std::cout << "$>";
    getline(std::cin, command);
    try {
      std::shared_ptr <COperation> op = cmdManager.execute(command, printHelp, exit);
      errorMsg = fileManager.executeOperation(op);
    } catch ( std::invalid_argument &ex ) {
      errorMsg = ex.what();
    }

    //delete op;
  }
  std::cout << std::endl;
}
