#include "CFile.h"
#include <iomanip>

CFile::CFile ( std::filesystem::path path, int size ) : CFileEntity(path),
                                                        size(size) {}

void CFile::print ( std::ostream &os ) const {
  //parts of code from https://stackoverflow.com/questions/2273330/restore-the-state-of-stdcout-after-manipulating-it
  std::ios oldState(nullptr);
  oldState.copyfmt(os); //save old state of ps
  os << std::left << "|" << std::setw(PRINT_WIDTH) << (CFileEntity::getFormatedName()) << std::setw(PRINT_WIDTH) << "|"
     << std::setw(PRINT_WIDTH)
     << size << std::setw(PRINT_WIDTH) << CFileEntity::lastWriteTime() << std::setw(PRINT_WIDTH) << "|";
  os.copyfmt(oldState); //reset os
//  os << "+" << std::string(CFileEntity::getPrintWidth() * 4, '-') << "+";
}

CFileEntity *CFile::clone () const {
  return new CFile(*this);
}

int CFile::sortingRank () const {
  return 200;
}
