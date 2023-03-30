#pragma once

#include "CFileEntity.h"
#include <string>

///Represents file in file system
class CFile : public CFileEntity {
public:
  /**
   *
   * @param path path to the item
   * @param size size in bytes
   */
  CFile ( std::filesystem::path path, int size );

  /**
     * copy
     * @return Pointer to allocated copy of the object
    */
  CFileEntity *clone () const;

  int sortingRank () const override;


protected:
  /**
 * Outputs dynamically bound item to output stream
 * @param os The output stream
 */
  void print ( std::ostream &os ) const override;


private:
  ///@var size in bytes
  int size;
};