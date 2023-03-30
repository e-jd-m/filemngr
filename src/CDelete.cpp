#include "CDelete.h"
#include "CFileSystemAPI.h"

CDelete::CDelete ( std::vector <CFilePtr> items, bool recursive ) : COperation(items), recursive(recursive) {}

void CDelete::run () {
  for ( const auto &f: srcItems ) {
    CFileSystemAPI::deleteItem(f->getPath(), recursive);
  }
}