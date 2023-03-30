#include "CSymLink.h"
#include <iomanip>

CSymLink::CSymLink ( std::filesystem::path path, std::filesystem::path linksTo ) : CFileEntity(path),
                                                                                   linksTo(linksTo) {}

CFileEntity *CSymLink::clone () const {
  return new CSymLink(*this);
}


int CSymLink::sortingRank () const {
  return 200;
}

void CSymLink::print ( std::ostream &os ) const {
  //parts of code from https://stackoverflow.com/questions/2273330/restore-the-state-of-stdcout-after-manipulating-it
  std::ios oldState(nullptr);
  oldState.copyfmt(os); //save old state of ps
  os << std::left << "|" << std::setw(PRINT_WIDTH) << (CFileEntity::getFormatedName()) << std::setw(PRINT_WIDTH) << "|"
     << std::setw(PRINT_WIDTH) << "-> " + linksTo.filename().string() << std::setw(PRINT_WIDTH)
     << CFileEntity::lastWriteTime() << std::setw(PRINT_WIDTH) << "|";
  os.copyfmt(oldState);
}
