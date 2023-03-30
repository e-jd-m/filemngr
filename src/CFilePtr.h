
#pragma once


#include "CFileEntity.h"
#include <memory>

///Custom pointer type, extends unique pointer and allows copying
class CFilePtr : public std::unique_ptr<CFileEntity> {
public:
  using std::unique_ptr<CFileEntity>::unique_ptr;

  CFilePtr ( const CFilePtr &other ) : std::unique_ptr<CFileEntity>(other->clone()) {}

  CFilePtr &operator= ( CFilePtr other ) {
    swap(other);
    return *this;
  }
};