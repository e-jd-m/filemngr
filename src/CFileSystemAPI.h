
#pragma once

#include "CFilePtr.h"
#include <stdexcept>
#include <vector>


namespace fs = std::filesystem;

///Set of static functions to interface with the file system
class CFileSystemAPI {
public:
  /**
   * lists files in given directory
   * @param p path to dir
   * @return files in given dir
   */
  static std::vector <CFilePtr> listFiles ( const fs::path &p );

  /**
   * deletes item in FS
   * @param p path to item
   * @param recursive should recursive delete be used
   */
  static void deleteItem ( const fs::path &p, bool recursive );

  /**
   * creates directory
   * @param p path to create
   */
  static void createDir ( const fs::path &p );

  /**
   * creates file
   * @param p path to create
   */
  static void createFile ( const fs::path &p );

  /**
   * copies item
   * @param src from
   * @param dst to
   */
  static void copy ( const fs::path &src, const fs::path &dst );

  /**
   * moves item
   * @param src from
   * @param dst to
   */
  static void move ( const fs::path &src, const fs::path &dst );

  /**
   * creates symbolic link
   * @param target target
   * @param link link name
   */
  static void createSymLink ( const fs::path &target, const fs::path &link );

  /**
   * creates hard link
   * @param target target
   * @param link link name
   */
  static void createHardLink ( const fs::path &target, const fs::path &link );

  /**
   * creates CFilePtr object from given path
   * @param src path to create from
   * @return object representing given path
   */
  static CFilePtr getFileFromPath ( const fs::path &src );

  /**
   * checks if path exists in fs
   * @param p path to check
   * @return true if path exist, false otherwise
   */
  static bool pathExists ( const fs::path p );


};