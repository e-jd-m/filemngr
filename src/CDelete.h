
#pragma once

#include "COperation.h"

///Represents delete action
class CDelete : public COperation {
public:
  /***
   *
   * @param items items to delete
   * @param recursive use recursive deletion
   */
  CDelete ( std::vector <CFilePtr> items, bool recursive );

  void run () override;

private:
  ///@var use recursive deletion
  bool recursive;
};