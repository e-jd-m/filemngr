#include "CChagePath.h"

CChangePath::CChangePath ( std::vector <CFilePtr> items, fs::path newPath, CFileManager &manager ) : COperation(items),
                                                                                                     newPath(newPath),
                                                                                                     manager(manager) {}

void CChangePath::run () {
  //auto d = fs::directory_iterator(newPath);
  manager.changeDirectory(newPath);
}