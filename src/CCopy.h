#pragma once

#include "COperation.h"

///Represents copy action
class CCopy : public COperation {
public:
  /***
   *
   * @param items files to copy
   * @param dstPath path to destination
   * @param currentPath current path in file system
   */
  CCopy ( std::vector <CFilePtr> items, const std::filesystem::path &dstPath, std::filesystem::path currentPath );

  void run () override;

private:
  ///@var path to copy files to
  std::filesystem::path dstPath;
  ///@var current path in file system
  std::filesystem::path currentPath;
};