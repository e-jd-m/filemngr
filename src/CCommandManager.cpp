
#include "CCommandManager.h"
#include "CCreate.h"
#include "CFile.h"
#include "CCreate.h"
#include "CDelete.h"
#include "CDirectory.h"
#include "CChagePath.h"
#include "CCopy.h"
#include "CMove.h"
#include "CCreateSymLink.h"
#include "CCreateHardLink.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>

//class CFileSystemAPI;

CCommandManager::CCommandManager ( CFileManager &manager ) : manager(manager) {}

std::shared_ptr <COperation>
CCommandManager::execute ( std::string cmd, bool &printHelp, bool &exit ) {
  std::vector <std::string> args = splitCommand(cmd);
  TCommand cmdStruct = createCommand(cmd);
  if ( cmdStruct.name == "cd" ) {
    return operationChangeDirFactory(cmdStruct.args);
  } else if ( cmdStruct.name == "touch" ) {
    return operationCreateFileFactory(cmdStruct.args);
  } else if ( cmdStruct.name == "mkdir" ) {
    return operationCreateFolderFactory(cmdStruct.args);
  } else if ( cmdStruct.name == "rm" ) {
    return operationDeleteFactory(cmdStruct.args, cmdStruct.opts);
  } else if ( cmdStruct.name == "copy" ) {
    return operationCopyFactory(cmdStruct.args, cmdStruct.opts);
  } else if ( cmdStruct.name == "move" ) {
    return operationMoveFactory(cmdStruct.args, cmdStruct.opts);
  } else if ( cmdStruct.name == "ln" ) {
    return operationCreateLinkFactory(cmdStruct.args, cmdStruct.opts);
  } else if ( cmdStruct.name == "help" ) {
    printHelp = true;
    return nullptr;
  } else if ( cmdStruct.name == "exit" ) {
    exit = true;
    return nullptr;
  }
  throw std::invalid_argument("Unknown command " + cmdStruct.name);
}

bool CCommandManager::validQuotes ( std::string str ) {
  size_t count = 0;
  for ( size_t i = 0; i < str.size(); ++i ) {
    if ( str[i] == '\"' ) {
      count++;
    }
  }
  return (count % 2 == 0);
}

std::vector <std::string> CCommandManager::splitCommand ( std::string cmd ) {
  if ( !validQuotes(cmd)) {
    throw std::invalid_argument("Quotes mismatch");
  }
  std::vector <std::string> args;
  std::string token = "";
  for ( size_t i = 0; i < cmd.size(); ++i ) {
    char c = cmd[i];
    bool space = std::isspace(static_cast<unsigned char>(c));
    if ( space && token.size() == 0 ) {
      continue;
    }
    if ( space ) {
      args.push_back(token);
      token = "";
    } else if ( c == '\"' ) {
      i++;
      while ( cmd[i] != '\"' ) {
        token += cmd[i];
        i++;
      }
      args.push_back(token);
      token = "";
    } else {
      token += c;
    }
  }
  args.push_back(token);
  return args;
}

TCommand CCommandManager::createCommand ( std::string cmd ) {
  std::vector <std::string> commandWords = splitCommand(cmd);
  TCommand resCmd;
  resCmd.name = commandWords[0];
  commandWords.erase(commandWords.begin());
  auto it = commandWords.begin();
  while ( it != commandWords.end()) {
    if ((*it)[0] == '-' ) {
      it->erase(0, 1);
      resCmd.opts.push_back(*it);
      it = commandWords.erase(it);
    } else {
      it++;
    }
  }
  resCmd.args = (commandWords);
  return resCmd;
}


std::shared_ptr <COperation>
CCommandManager::operationCreateFileFactory ( std::vector <std::string> args ) {
  std::vector <CFilePtr> files;
  for ( const auto &n: args ) {
    CFile tmp(manager.getCurrentPath() / n, 0);
    files.emplace_back(tmp.clone());
  }
  if ( files.size() == 0 ) {
    throw std::invalid_argument("No file provided");
  }
  std::shared_ptr <COperation> op = std::make_shared<CCreate>(files, false);
  return op;
}

std::shared_ptr <COperation>
CCommandManager::operationCreateFolderFactory ( std::vector <std::string> args ) {
  std::vector <CFilePtr> files;
  for ( const auto &n: args ) {
    CDirectory tmp(manager.getCurrentPath() / n);
    files.emplace_back(tmp.clone());
  }
  if ( files.size() == 0 ) {
    throw std::invalid_argument("No folder provided");
  }
  std::shared_ptr <COperation> op = std::make_shared<CCreate>(files, true);
  return op;
}

std::shared_ptr <COperation>
CCommandManager::operationDeleteFactory ( std::vector <std::string> args,
                                          std::vector <std::string> opts ) {
  if ( args.size() == 0 ) {
    throw std::invalid_argument("No arguments provided");
  }
  bool useRegex = std::find(opts.begin(), opts.end(), "r") != opts.end();
  bool recursive = std::find(opts.begin(), opts.end(), "c") != opts.end();
  std::vector <CFilePtr> files = getFileList(args[0], useRegex);
  if ( files.size() == 0 ) {
    throw std::invalid_argument("No file name matching \"" + args[0] + "\" in current directory");
  }
  std::shared_ptr <COperation> op = std::make_shared<CDelete>(files, recursive);
  return op;
}

std::shared_ptr <COperation> CCommandManager::operationChangeDirFactory ( std::vector <std::string> args ) {
  if ( args.size() == 0 ) {
    throw std::invalid_argument("No arguments provided");
  }
  fs::path p(args[0]);
  //manager.changeDirectory(p);
  std::vector <CFilePtr> files;
  std::shared_ptr <COperation> op = std::make_shared<CChangePath>(files, manager.getCurrentPath() / p, manager);
  return op;
}

std::shared_ptr <COperation>
CCommandManager::operationCopyFactory ( std::vector <std::string> args, std::vector <std::string> opts ) {
  if ( args.size() < 2 ) {
    throw std::invalid_argument("Too few arguments provided");
  }
  bool useRegex = std::find(opts.begin(), opts.end(), "r") != opts.end();
  std::vector <CFilePtr> files = getFileList(args[0], useRegex);
  if ( files.size() == 0 ) {
    throw std::invalid_argument("No file name matching \"" + args[0] + "\" in current directory");
  }
  std::shared_ptr <COperation> op = std::make_shared<CCopy>(files, fs::path(args[1]), manager.getCurrentPath());
  return op;
}

std::shared_ptr <COperation>
CCommandManager::operationMoveFactory ( std::vector <std::string> args, std::vector <std::string> opts ) {
  if ( args.size() < 2 ) {
    throw std::invalid_argument("Too few arguments provided");
  }
  bool useRegex = std::find(opts.begin(), opts.end(), "r") != opts.end();
  std::vector <CFilePtr> files = getFileList(args[0], useRegex);
  if ( files.size() == 0 ) {
    throw std::invalid_argument("No file name matching \"" + args[0] + "\" in current directory");
  }
  std::shared_ptr <COperation> op = std::make_shared<CMove>(files, fs::path(args[1]), manager.getCurrentPath());
  return op;
}

std::shared_ptr <COperation>
CCommandManager::operationCreateLinkFactory ( std::vector <std::string> args, std::vector <std::string> opts ) {
  if ( args.size() < 2 ) {
    throw std::invalid_argument("Too few arguments provided");
  }
  std::vector <CFilePtr> files = getFileList(args[0], false);
  if ( files.size() == 0 ) {
    throw std::invalid_argument("No file name matching \"" + args[0] + "\" in current directory");
  }
  std::shared_ptr <COperation> op;
  if ( std::find(opts.begin(), opts.end(), "s") != opts.end()) {
    op = std::make_shared<CCreateSymLink>(files, fs::path(args[1]), manager.getCurrentPath());
  } else {
    op = std::make_shared<CCreateHardLink>(files, fs::path(args[1]), manager.getCurrentPath());
  }
  return op;
}

std::vector <CFilePtr> CCommandManager::getFileList ( std::string name, bool useRegex ) {
  std::vector <CFilePtr> files;
  if ( useRegex ) {
    try {
      files = manager.listCurrentFiles(std::regex(name));
    } catch ( const std::regex_error &e ) {
      throw std::invalid_argument("Invalid regex argument");
    }
  } else {
    for ( const auto &f: manager.listCurrentFiles()) {
      if ( f->getName() == name ) {
        files.push_back(f);
        break;
      }
    }
  }
  return files;
}

std::string CCommandManager::printHelp () {
  return std::string("cd <path> \ntouch <list of files to create> \nmkdir <list of folders to create>") +
         "\nrm [-r use regex, -c recursive] <filenames to delete / regex expression>" +
         "\ncopy [-r use regex] <filenames to copy / regex expression> <path/to/dest/filename in dest>" +
         "\nmove [-r use regex] <filenames to move / regex expression> <path/to/dest/filename in dest>" +
         "\nln [-s symbolic link] <filename> <link name>" +
         "\nexit";
}