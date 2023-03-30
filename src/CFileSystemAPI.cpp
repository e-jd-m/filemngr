
#include "CFileSystemAPI.h"
#include <fstream>
#include <filesystem>
#include <exception>
#include <stdexcept>
#include "CSymLink.h"
#include "CDirectory.h"
#include "CFile.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>


std::vector <CFilePtr> CFileSystemAPI::listFiles ( const fs::path &p ) {
  std::vector <CFilePtr> files;
  for ( const auto &entry: fs::directory_iterator(p)) {
    CFilePtr filePtr = getFileFromPath(entry.path());
    if ( filePtr == nullptr ) {
      continue;
    }
    files.push_back(filePtr);
  }
  return files;
}

void CFileSystemAPI::createDir ( const fs::path &p ) {
  fs::create_directory(p);
}

void CFileSystemAPI::createFile ( const fs::path &p ) {
  std::ofstream ofs(p.string());
  ofs.close();
}

void CFileSystemAPI::deleteItem ( const fs::path &p, bool recursive ) {
  if ( recursive ) {
    fs::remove_all(p);
    return;
  }
  if ( !fs::remove(p)) {
    throw std::invalid_argument("Item not found");
  }
}


void CFileSystemAPI::copy ( const fs::path &src, const fs::path &dst ) {
  fs::copy(src.string(), dst.string());
}

void CFileSystemAPI::move ( const fs::path &src, const fs::path &dst ) {
//  if(pathExists(dst)) {
//    fs::rename(src.string(), src / dst);
//  } else {
//    fs::rename(src.string(), dst.string());
//  }
  fs::rename(src.string(), dst.string());
}

void CFileSystemAPI::createSymLink ( const fs::path &target, const fs::path &link ) {
  fs::create_symlink(target, link);
}

void CFileSystemAPI::createHardLink ( const fs::path &target, const fs::path &link ) {
  fs::create_hard_link(target, link);
}

CFilePtr CFileSystemAPI::getFileFromPath ( const fs::path &src ) {
  auto entry = fs::directory_entry(src);
  if ( entry.is_symlink()) {
    //CFilePtr linksTo = getFileFromPath(fs::read_symlink(src));
    return CFilePtr(new CSymLink(entry.path(), fs::read_symlink(src)));
  } else if ( entry.is_regular_file()) {
    return CFilePtr(new CFile(entry.path(), entry.file_size()));
  } else if ( entry.is_directory()) {
    return CFilePtr(new CDirectory(entry.path()));
  }
  return nullptr;
}


bool CFileSystemAPI::pathExists ( const fs::path p ) {
  struct stat buffer;
  return (stat(p.string().c_str(), &buffer) != 0);
}