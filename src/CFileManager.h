#pragma once

#include "CFileEntity.h"
#include "CFilePtr.h"
#include "COperation.h"
#include <vector>
#include <memory>
#include <string>
#include <regex>

namespace fs = std::filesystem;

/**
 * \mainpage
* **File manager**
Program na správu souborů/adresářů
Implementujte následující funkcionalitu:

 1. vytváření a mazání souborů/adresářů/linků
 2. kopírování a přesun souborů/adresářů/linku
 3. možnost provádět operace nad množinou soborů definovaných regulárním výrazem(copy, move, delete)
 4. navigace mezi jednotlivými adresáři
 5. uživatelské rozhraní: zobrazení adresářů nad kterými se pracuje a vizuální rozlišení souborů/adresářů/linků

Použití polymorfismu:
 - Typy souborů, základní třída CFileEntity, ze které dědí CFile, CDirectory, CSymLink. Pouzito pro polymorfni vypis.
 -  Operace nad soubory. Třída COperation, virtualní metoda COperation::run(), která udelá určenou operaci.

uživatelské rozhraní:
    Aplikace půjde ovládat pomocí textových příkazů.
    Program bude na obrazovku vypisovat aktuální soubory, adresáře...
    Seznam příkazů:

		   -cd -zmena adresare
           -touch -vytvoreni souboru
           -mkdir -vyrvoreni adresare
           -rm -odstraneni souboru
           -ln -vytvoreni linku


 */


///Class to handle file manager operations (eg. hold current path, execute operations)
class CFileManager {
public:
  CFileManager ();

  /***
   * change current directory
   * @param[in] path path to go to
   */
  void changeDirectory ( fs::path &path );

  /**
   * gets current path
   * @return current path
   */
  fs::path getCurrentPath ();

  /**
   * executes operation and returns error msgs for user
   * @param op pointer to operation
   * @return error msg string
   */
  std::string executeOperation ( std::shared_ptr <COperation> op );

  /***
   * gives a list of currently shown files
   * @return vector of file pointers
   */
  const std::vector <CFilePtr> listCurrentFiles ();

  /***
   * gives a list of currently shown files, based on regex expr
   * @param exp regex to mach for
   * @return vector of file pointers
   */
  const std::vector <CFilePtr> listCurrentFiles ( std::regex exp );


private:
  /***
   * sorts files based on sorting rank and name
   */
  void sortFiles ();

  /***
   * refresh currently shown files
   *
   */
  void refreshFiles ();

  /**
   * normalizes path
   * @param p path to normalize
   * @return normalized path
   */
  fs::path normalizePath ( fs::path p );


  ///@var path to currently shown directory
  fs::path currentPath;
  ///@var list of current files
  std::vector <CFilePtr> files;

};