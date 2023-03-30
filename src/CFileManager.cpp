#include "CFileManager.h"
#include <iostream>
#include <algorithm>
#include "CFileSystemAPI.h"


CFileManager::CFileManager () : currentPath(fs::current_path()), files(CFileSystemAPI::listFiles(currentPath)) {
  sortFiles();
}

void CFileManager::changeDirectory ( fs::path &path ) {
  fs::path tmpPath = normalizePath(currentPath / path);
  files = CFileSystemAPI::listFiles(tmpPath);
  //currentPath /= path;
  currentPath = tmpPath;
}

const std::vector <CFilePtr> CFileManager::listCurrentFiles () {
  refreshFiles();
  return files;
}

const std::vector <CFilePtr> CFileManager::listCurrentFiles ( std::regex exp ) {
  refreshFiles();
  std::vector <CFilePtr> resItems;
  for ( const auto &f: files ) {
    std::string name = f->getName();
    if ( std::regex_match(name, exp)) {
      resItems.push_back(f);
    }
  }
  return resItems;
}


void CFileManager::sortFiles () {
  //sort files, so that folders are at the top
  sort(files.begin(), files.end(), [] ( const CFilePtr a, const CFilePtr b ) {
    if ( a->sortingRank() == b->sortingRank()) {
      return a->getName() < b->getName();
    }
    return a->sortingRank() < b->sortingRank();
  });
}

fs::path CFileManager::getCurrentPath () {
  return currentPath;
}

void CFileManager::refreshFiles () {
  try {
    files = CFileSystemAPI::listFiles(currentPath);
    sortFiles();
  }
  catch ( fs::filesystem_error &ex ) {
    //std::cout << ex.what() << std::endl;
    return;
  }
}

std::string CFileManager::executeOperation ( std::shared_ptr <COperation> op ) {
  if ( op == nullptr ) {
    return "";
  }
  try {
    op->run();
    return "";
  } catch ( fs::filesystem_error &ex ) {
    return ex.code().message();
  }
  return "";
}

fs::path CFileManager::normalizePath ( fs::path p ) {
  return fs::path(p.lexically_normal());
}
