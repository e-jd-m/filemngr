#include "CMove.h"
#include "CFileSystemAPI.h"
#include <stdexcept>

CMove::CMove ( std::vector <CFilePtr> items, const std::filesystem::path &dstPath, std::filesystem::path currentPath )
  : COperation(items), dstPath(dstPath), currentPath(currentPath) {}

void CMove::run () {
  for ( const auto &f: srcItems ) {
    CFileSystemAPI::move(f->getPath(), currentPath / dstPath);
  }
}