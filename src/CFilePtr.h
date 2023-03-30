
#pragma once

///zdroj cviceni: https://gitlab.fit.cvut.cz/matouj10/pa2-2021-lab/blob/master/09/1-rtti-and-polymorphic-ctors/CItemPtr.h

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