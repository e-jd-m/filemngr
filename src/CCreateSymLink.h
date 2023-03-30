#pragma once

#include "COperation.h"

///Represents create sym link operation
class CCreateSymLink : public COperation {
public:
  /***
   *
   * @param items items to link to, should always be of size 1
   * @param link name of the link
   * @param currentPath current path in file system
   */
  CCreateSymLink ( std::vector <CFilePtr> items, const std::filesystem::path &link,
                   const std::filesystem::path &currentPath );

  void run () override;

private:
  ///@var name of the link
  std::filesystem::path link;
  ///@var current path in file system
  std::filesystem::path currentPath;
};