#include "CCreateSymLink.h"
#include "CFileSystemAPI.h"

CCreateSymLink::CCreateSymLink ( std::vector <CFilePtr> items, const std::filesystem::path &link,
                                 const std::filesystem::path &currentPath ) : COperation(items), link(link),
                                                                              currentPath(currentPath) {}

void CCreateSymLink::run () {
  CFileSystemAPI::createSymLink(srcItems[0]->getPath(), currentPath / link);
}

