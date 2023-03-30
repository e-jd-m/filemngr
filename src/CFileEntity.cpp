

#include "CFileEntity.h"
#include <chrono>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>

CFileEntity::CFileEntity ( std::filesystem::path path ) : path(path) {}

std::ostream &operator<< ( std::ostream &os, const CFileEntity &ent ) {
  ent.print(os);
  return os;
}

std::filesystem::path CFileEntity::getPath () {
  return path;
}

std::string CFileEntity::getName () const {
  return path.filename();
}

std::string CFileEntity::getFormatedName () const {
  std::string name = path.filename();
  std::string resName;
  bool useQuotes = name.find(" ") != std::string::npos;
  if ( name.size() > PRINT_WIDTH - 6 ) {
    for ( size_t i = 0; i < PRINT_WIDTH - 6; ++i ) {
      resName += name[i];
    }
    resName += "...";
    return useQuotes ? ("'" + resName + "'") : resName;
  }
  return useQuotes ? ("'" + name + "'") : name;
}

std::string CFileEntity::lastWriteTime () const {
  struct stat result;
  if ( stat(path.string().c_str(), &result) == 0 ) {
    auto modTime = result.st_mtime;
    char resStr[100];
    if ( std::strftime(resStr, sizeof(resStr), "%H:%M - %d.%m.%Y", std::localtime(&modTime))) {
      return resStr;
    }
  }
  return "";
}


int CFileEntity::getPrintWidth () {
  return PRINT_WIDTH;
}