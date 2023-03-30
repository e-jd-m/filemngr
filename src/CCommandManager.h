
#pragma once

#include <string>
#include <map>
#include <vector>
#include <ostream>

#include "COperation.h"
#include "CFileManager.h"

///Struct to represent single command
struct TCommand {
  std::string name;
  std::vector <std::string> opts;
  std::vector <std::string> args;
};

namespace fs = std::filesystem;

///Class to handle command inputs and transform them to operation objects
class CCommandManager {
public:
  /***
   *
   * @param manager manager, that the UI is working with
   */
  CCommandManager ( CFileManager &manager );

  /***
   * Parse out user command
   * @param cmd command from user
   * @param[out] printHelp was the help command called
   * @param[out] exit was exit command called
   * @return Object of the operation to execute
   */
  std::shared_ptr <COperation> execute ( std::string cmd, bool &printHelp, bool &exit );

  /***
   *
   * @return text with user manual
   */
  std::string printHelp ();

private:
  ///@var reference to current file manager
  CFileManager &manager;

  /***
   * splits command to tokens by space, words in quotes are kept together
   * @param cmd command from user
   * @return command tokens
   */
  std::vector <std::string> splitCommand ( std::string cmd );

  /***
   * creates command struct
   * @param cmd command from user
   * @return struct representing command
   */
  TCommand createCommand ( std::string cmd );

  /***
   * Creates create file operation
   * @param args arguments to touch command
   * @return object representing create file operation
   */
  std::shared_ptr <COperation>
  operationCreateFileFactory ( std::vector <std::string> args );

  /***
   *  Creates create folder operation
   * @param args arguments to mkdir command
   * @return object representing create folder operation
   */
  std::shared_ptr <COperation>
  operationCreateFolderFactory ( std::vector <std::string> args );

  /***
   * creates delete operation
   * @param args args from user
   * @param opts command options
   * @return object representing delete operation
   */
  std::shared_ptr <COperation>
  operationDeleteFactory ( std::vector <std::string> args, std::vector <std::string> opts );

  /***
   * Creates change directory operation
   * @param args args from user
   * @return object representing change dir operation
   */
  std::shared_ptr <COperation> operationChangeDirFactory ( std::vector <std::string> args );

  /***
   * creates copy operation
   * @param args args from user
   * @param opts user options
   * @return object representing copy operation
   */
  std::shared_ptr <COperation> operationCopyFactory ( std::vector <std::string> args, std::vector <std::string> opts );

  /***
   * creates move operation
   * @param args args from user
   * @param opts user options
   * @return object representing move operation
   */
  std::shared_ptr <COperation> operationMoveFactory ( std::vector <std::string> args, std::vector <std::string> opts );

  /***
   * creates link operation
   * @param args args from user
   * @param opts user options
   * @return object representing link operation
   */
  std::shared_ptr <COperation>
  operationCreateLinkFactory ( std::vector <std::string> args, std::vector <std::string> opts );

  /***
   * lists files with given name in current directory
   * @param name name of the file or regex to match
   * @param useRegex should regex matching be used
   * @return list of files with matching name
   */
  std::vector <CFilePtr> getFileList ( std::string name, bool useRegex );

  /***
   * check if there is even number of quotes in a string, escaping isn't supported
   * @param str str to check
   * @return true if check is passed
   */
  bool validQuotes ( std::string str );


};