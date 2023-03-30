
#include "CFileEntity.h"

#include <string>

///Represents folder in file system
class CDirectory : public CFileEntity {
public:
  /**
   *
   * @param path path to the directory
   */
  CDirectory ( std::filesystem::path path );

  /**
     * copy
     * @return Pointer to allocated copy of the object
    */
  CFileEntity *clone () const;


  int sortingRank () const override;

protected:
  /**
* Outputs dynamically bound item to output stream
*
* @param os The output stream
*/
  void print ( std::ostream &os ) const override;

};