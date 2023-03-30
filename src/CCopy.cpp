#include "CCopy.h"
#include "CFileSystemAPI.h"
#include <stdexcept>

CCopy::CCopy ( std::vector <CFilePtr> items, const std::filesystem::path &dstPath, std::filesystem::path currentPath )
  : COperation(items), dstPath(dstPath), currentPath(currentPath) {}

void CCopy::run () {
  for ( const auto &f: srcItems ) {
    CFileSystemAPI::copy(f->getPath(), currentPath / dstPath);
  }
}