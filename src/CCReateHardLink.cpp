#include "CCreateHardLink.h"
#include "CFileSystemAPI.h"

CCreateHardLink::CCreateHardLink ( std::vector <CFilePtr> items, const std::filesystem::path &link,
                                   const std::filesystem::path &currentPath ) : COperation(items), link(link),
                                                                                currentPath(currentPath) {}

void CCreateHardLink::run () {
  CFileSystemAPI::createHardLink(srcItems[0]->getPath(), currentPath / link);
}

