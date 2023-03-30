#pragma once

#include "COperation.h"

///Represents operation create hard link
class CCreateHardLink : public COperation {
public:
  /***
   *
   * @param items items to link to, should always be of size 1
   * @param link name of the link
   * @param currentPath current path in file system
   */
  CCreateHardLink ( std::vector <CFilePtr> items, const std::filesystem::path &link,
                    const std::filesystem::path &currentPath );

  void run () override;

private:
  ///@var link name
  std::filesystem::path link;
  ///@var current path in file system
  std::filesystem::path currentPath;
};