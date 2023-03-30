#pragma once

#include <string>
#include <ostream>
#include <filesystem>
#include <iomanip>

///Class to represent filesystem entity (eg. file, folder, link...)
class CFileEntity {
public:
  /***
   *
   * @param path path to the item
   */
  CFileEntity ( std::filesystem::path path );

  virtual ~CFileEntity () = default;

  /***
   *
   * @return path
   */
  std::filesystem::path getPath ();

  /**
     * Virtual copy
     * @return Pointer to allocated copy of the object
    */
  virtual CFileEntity *clone () const = 0;

  /**
   *
   * @return name of the item
   */
  std::string getName () const;

  /***
   * gives each derived class a rank, so that we can sort them by type
   * @return rank
   */
  virtual int sortingRank () const = 0;

  /**
     * Outputs item to output stream
     * @param os The output stream
     * @param item The item which should be written out to the stream
     * @return The output stream os
     */
  friend std::ostream &operator<< ( std::ostream &os, const CFileEntity &ent );

  /**
   *
   * @return string representing time of last change
   */
  std::string lastWriteTime () const;

  /**
   *
   * @return width of each column in print
   */
  static int getPrintWidth ();


protected:
  /**
 * Outputs dynamically bound item to output stream
 * @note This function should be overridden by each descendant to provide its own output representation
 * @param os The output stream
 */
  virtual void print ( std::ostream &os ) const = 0;

  /**
   * farmats item name, so it's not wider, than PRINT_WIDTH
   * if name is too long, it will end with ...
   * if name contains any spaces, it will be enclosed in quotes
   * @return name in format
   */
  std::string getFormatedName () const;

  /**
   * @var path to item in FS
   */
  const std::filesystem::path path;

  /**
   * @var widht of column in print
   */
  static const int PRINT_WIDTH = 40;


};