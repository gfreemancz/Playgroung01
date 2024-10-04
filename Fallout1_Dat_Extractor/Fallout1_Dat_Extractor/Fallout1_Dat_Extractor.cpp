// Fallout1_Dat_Extractor.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

char * LoadBinarzDataFromFile(uint32_t & arg_DataLenght)
{
  std::string loc_RoothPath = "C:/development/Playgroung01/Fallout1_Dat_Extractor/test_data";
  std::string loc_DatFileName = "MASTER.DAT";

  std::ifstream infile((loc_RoothPath + "/" + loc_DatFileName).c_str());

  infile.seekg(0, std::ios::end);
  unsigned int loc_FileLength = infile.tellg();
  infile.seekg(0, std::ios::beg);


  char *loc_Tmp = new char[loc_FileLength];
  

  infile.read(loc_Tmp, loc_FileLength);
  infile.close();

  arg_DataLenght = loc_FileLength;

  return loc_Tmp;
}

uint32_t GetUI32FromIdx(char *arg_Data, uint32_t arg_idx)
{
  uint32_t *loc_DataPtr;

  loc_DataPtr = reinterpret_cast<uint32_t*>(arg_Data + arg_idx);

  return _byteswap_ulong(*loc_DataPtr);
}

uint8_t GetUI8FromIdx(char* arg_Data, uint32_t arg_idx)
{
  uint8_t* loc_DataPtr;

  loc_DataPtr = reinterpret_cast<uint8_t*>(arg_Data + arg_idx);

  return *loc_DataPtr;
}


void ReadDirectoryList(char* arg_Data, std::vector<std::string> &DirectoryList)
{
  uint32_t loc_WorkingIdx = 0x12UL;
  uint16_t loc_Size = GetUI8FromIdx(arg_Data, loc_WorkingIdx);
  uint32_t loc_DirCount = GetUI32FromIdx(arg_Data, 0);

  std::string  loc_DirName = "";

  loc_WorkingIdx++;

  for (uint16_t i = 0; i < loc_DirCount; i++)
  {
    loc_DirName.append((arg_Data + loc_WorkingIdx), loc_Size);
    loc_WorkingIdx += loc_Size;
    loc_Size = GetUI8FromIdx(arg_Data, loc_WorkingIdx);
    loc_WorkingIdx++;
    DirectoryList.push_back(loc_DirName);
    loc_DirName.clear();

  }

  
}


int main()
{
  uint32_t loc_DataFileLength;
  uint32_t loc_Tmp;
  char *loc_DataArray;
  std::vector<std::string> DirectoryList;


  loc_DataArray = LoadBinarzDataFromFile(loc_DataFileLength);

  ReadDirectoryList(loc_DataArray, DirectoryList);

  loc_Tmp = GetUI32FromIdx(loc_DataArray, 4);




  std::cout << (loc_Tmp);








  delete []loc_DataArray;
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
