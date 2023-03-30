#pragma once

#include "COperation.h"

///Represents create action
class CCreate : public COperation {
public:
  /***
   *
   * @param srcItms files/folders to create
   * @param createDir create folders?
   */
  CCreate ( std::vector <CFilePtr> &srcItms, bool createDir );

  void run () override;

private:
  ///@var if true, creates folders not files
  bool createDir;
};