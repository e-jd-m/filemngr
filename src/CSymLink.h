#pragma once

#include "CFileEntity.h"
#include "CFilePtr.h"

///Represents symbolic link in filesystem
class CSymLink : public CFileEntity {
public:
  /**
   *
   * @param path path to link
   * @param linksTo path to what links points to
   */
  CSymLink ( std::filesystem::path path, std::filesystem::path linksTo );

  CFileEntity *clone () const;

  int sortingRank () const override;


protected:
  /**
 * Outputs dynamically bound item to output stream
 * @param os The output stream
 */
  void print ( std::ostream &os ) const override;


private:
  ///@var path to what links points to
  std::filesystem::path linksTo;
};