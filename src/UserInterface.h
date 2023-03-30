#pragma once

#include "CFileManager.h"
#include "CCommandManager.h"

///Class to handle user interface, eg. display files, process commands
class UserInterface {
public:
  UserInterface ();

  /**
   * starts UI
   */
  void start ();

private:
  /**
   * renders items on screen and handles user commands
   */
  void render ();

  ///@var file manager that we are using
  CFileManager fileManager;
  ///@var command manager to parse commands
  CCommandManager cmdManager;

  ///@var represents error msg to display to user
  std::string errorMsg;
  ///@var should help text be printed
  bool printHelp;
};