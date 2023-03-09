// JA1_DataExtractor.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include<iostream>
#include<fstream>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <map>



typedef struct sMainFileHeader
{
  char name[0x10];
  unsigned int FileTableSize;
  unsigned int FileTableElements;
  char reserved[8];
} tMainFileHeader;

typedef struct sSubFileHeader
{
  char name[0x10];
  unsigned int address;
  unsigned int size;
  char reserved[8];
} tSubFileHeader;



typedef struct sTileInfo
{
  unsigned char data[5];
} tTileInfo;



int ExtractPackage(std::string arg_path, std::string arg_FileName)
{
  struct stat results;
  char* loc_SourceFileData;
  tMainFileHeader* loc_MainFileHeader;
  tSubFileHeader* loc_SubFileHeader;

  if (stat((arg_path + arg_FileName).c_str(), &results) == 0)
  {
    std::cout << results.st_size << std::endl;

  }
  else
  {
    std::cout << "neni file" << std::endl;
    return 1;
  }

  loc_SourceFileData = new char[results.st_size];

  std::ifstream  InputFile(arg_path + arg_FileName, std::ios::binary);

  InputFile.read(loc_SourceFileData, results.st_size);
  InputFile.close();

  loc_MainFileHeader = reinterpret_cast<tMainFileHeader*>(loc_SourceFileData);
  loc_SubFileHeader = reinterpret_cast<tSubFileHeader*>(loc_SourceFileData) + 1;


  for (unsigned int i = 0; i < loc_MainFileHeader->FileTableElements; i++)
  {
    std::string loc_FilePathAndName = arg_path + "output\\" + std::string(loc_SubFileHeader[i].name);
    std::ofstream  loc_OutputFile(loc_FilePathAndName, std::ios::binary);
    loc_OutputFile.write(&loc_SourceFileData[loc_SubFileHeader[i].address], loc_SubFileHeader[i].size);
    loc_OutputFile.close();

  }


  delete[] loc_SourceFileData;
  return 0;
}


int ReadSectorMap(std::string arg_path, std::string arg_FileName)
{
  struct stat results;
  char* loc_SourceFileData;
  tTileInfo* loc_TilePtr;
  uint32_t loc_TileCount;
  std::vector<char> loc_List;
  std::vector<char> loc_List2;
  char loc_Znak = '_';

  std::map<char, char> loc_pallete;

  if (stat((arg_path + arg_FileName).c_str(), &results) == 0)
  {
    std::cout << results.st_size << std::endl;

  }
  else
  {
    std::cout << "neni file" << std::endl;
    return 1;
  }

  loc_SourceFileData = new char[results.st_size];
  std::ifstream  InputFile(arg_path + arg_FileName, std::ios::binary);

  InputFile.read(loc_SourceFileData, results.st_size);
  InputFile.close();


  char loc_sector = 59;

  loc_TileCount = results.st_size / 5;

  uint32_t loc_DataOffset = loc_sector * 15681;


  loc_TilePtr = reinterpret_cast<tTileInfo * >(&loc_SourceFileData[loc_DataOffset]);

  std::ofstream  loc_OutputFile(arg_path + "output\\sector.txt");


  //for (uint32_t i = 0; i < loc_TileCount; i++)
  //{
  //  if ((i > 0) && ((i % 55) == 0))
  //  {
  //    loc_OutputFile << std::endl;
  //  }
  //  loc_OutputFile << loc_TilePtr[i].data[3];
  //}

  char loc_idx = 0;
  

  for (uint32_t i = 0; i < loc_TileCount; i++)
  {
    if (std::find(loc_List.begin(), loc_List.end(), loc_TilePtr[i].data[loc_idx]) == loc_List.end())
    {
      loc_List.push_back(loc_TilePtr[i].data[loc_idx]);

      std::pair<char, char> loc_Tmp(loc_TilePtr[i].data[loc_idx], loc_Znak);
      loc_pallete.insert(loc_Tmp);
      loc_Znak++ ;
    }
    if (i == 3136)break;
  }

  for (uint32_t i = 0; i < loc_TileCount; i++)
  {
    if ((i > 0) && ((i % 56) == 0))
    {
      loc_OutputFile << std::endl;
    }
    loc_OutputFile << loc_pallete[loc_TilePtr[i].data[loc_idx]];
    if (i == 3135)break;
    //loc_OutputFile << loc_TilePtr[i].data[3];
  }

    loc_OutputFile.close();
  delete[] loc_SourceFileData;

  return 0;

}


int main()
{
    std::cout << "Hello World!\n";


    // ExtractPackage("C:\\development\\Playgroung01.git\\JA1_DataExtractor\\data_files\\", "MAIN.DAT");
     ReadSectorMap("C:\\development\\Playgroung01.git\\JA1_DataExtractor\\data_files\\", "TERRAIN.DAT");
    
    
    return 0;

}

// Spuštění programu: Ctrl+F5 nebo nabídka Ladit > Spustit bez ladění
// Ladění programu: F5 nebo nabídka Ladit > Spustit ladění

// Tipy pro zahájení práce:
//   1. K přidání nebo správě souborů použijte okno Průzkumník řešení.
//   2. Pro připojení ke správě zdrojového kódu použijte okno Team Explorer.
//   3. K zobrazení výstupu sestavení a dalších zpráv použijte okno Výstup.
//   4. K zobrazení chyb použijte okno Seznam chyb.
//   5. Pokud chcete vytvořit nové soubory kódu, přejděte na Projekt > Přidat novou položku. Pokud chcete přidat do projektu existující soubory kódu, přejděte na Projekt > Přidat existující položku.
//   6. Pokud budete chtít v budoucnu znovu otevřít tento projekt, přejděte na Soubor > Otevřít > Projekt a vyberte příslušný soubor .sln.
