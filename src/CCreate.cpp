
#include "CCreate.h"
#include "CFileSystemAPI.h"

CCreate::CCreate ( std::vector <CFilePtr> &srcItms, bool createDir ) : COperation(srcItms), createDir(createDir) {}

void CCreate::run () {
  for ( const auto &it: srcItems ) {
    if ( createDir ) {
      CFileSystemAPI::createDir(it->getPath());
    } else {
      CFileSystemAPI::createFile(it->getPath());
    }
  }
}
