#pragma once

#include "CFilePtr.h"
#include <vector>

///Represents filesystem operation
class COperation {
public:
  /**
   *
   * @param srcItems items to perform action on
   */
  COperation ( std::vector <CFilePtr> &srcItems ) : srcItems(srcItems) {}

  /**
   * virtual run
   * each object should implement own
   */
  virtual void run () = 0;

  virtual ~COperation () = default;

protected:
  ///@var items to perform action on
  std::vector <CFilePtr> srcItems;
};