#pragma once

#include "COperation.h"

///Represents move action
class CMove : public COperation {
public:
  /***
 *
 * @param items files to move
 * @param dstPath path to destination
 * @param currentPath current path in file system
 */
  CMove ( std::vector <CFilePtr> items, const std::filesystem::path &dstPath, std::filesystem::path currentPath );

  void run () override;

private:
  ///@var  path to destination
  std::filesystem::path dstPath;
  ///@var current path in file system
  std::filesystem::path currentPath;
};