#pragma once

#include "COperation.h"
#include "CFileManager.h"

namespace fs = std::filesystem;

///Class to represent operation of  changing current directory
class CChangePath : public COperation {
public:
  /**
   *
   * @param items should always be size 0
   * @param newPath path to move to
   * @param manager reference to current manager
   */
  CChangePath ( std::vector <CFilePtr> items, fs::path newPath, CFileManager &manager );

  void run () override;

private:
  ///@var path to move to
  fs::path newPath;
  ///@var reference to current manager
  CFileManager &manager;
};