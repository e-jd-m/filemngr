#include "CDirectory.h"
#include <iomanip>

CDirectory::CDirectory ( std::filesystem::path path ) : CFileEntity(path) {}


void CDirectory::print ( std::ostream &os ) const {
  //parts of code from https://stackoverflow.com/questions/2273330/restore-the-state-of-stdcout-after-manipulating-it
  std::ios oldState(nullptr);
  oldState.copyfmt(os); //save old state of ps
  os << std::left << "|" << std::setw(PRINT_WIDTH) << (CFileEntity::getFormatedName()) + "/" << std::setw(PRINT_WIDTH)
     << "|" << std::setw(PRINT_WIDTH) << "" << std::setw(PRINT_WIDTH) << CFileEntity::lastWriteTime()
     << std::setw(PRINT_WIDTH) << "|";
  os.copyfmt(oldState);
}

CFileEntity *CDirectory::clone () const {
  return new CDirectory(*this);
}

int CDirectory::sortingRank () const {
  return 100;
}

