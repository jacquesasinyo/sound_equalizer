/**
  ***************************************************************************************************************
  * File:       File_Handling.c
  * Author:     Adapted for STM32F407G-DISC1 with microSD (SPI)
  * Updated:    6th June 2025
  ***************************************************************************************************************
*/

#include "File_Handling.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"  // Ensure fatfs is initialized via CubeMX

extern FILELIST_FileTypeDef FileList;

extern char USERPath[4];     /* SD logical drive path */
extern FATFS USERFatFS;      /* File system object for SD */
extern FIL USERFile;         /* File object for SD */

FILINFO fno;
FRESULT fresult;           // Result code
UINT br, bw;               // File read/write counters

uint16_t NumObs = 0;

FRESULT AUDIO_StorageParse(void)
{
  FRESULT res = FR_OK;
  DIR dir;
  char *fn;

  res = f_opendir(&dir, USERPath);  // open SD card root directory
  FileList.ptr = 0;

  if (res == FR_OK)
  {
    while (1)
    {
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0)
        break;
      if (fno.fname[0] == '.')
        continue;

      fn = fno.fname;

      if (FileList.ptr < FILEMGR_LIST_DEPDTH)
      {
        if ((fno.fattrib & AM_DIR) == 0)
        {
          if ((strstr(fn, ".wav") || strstr(fn, ".WAV")))
          {
            strncpy((char *)FileList.file[FileList.ptr].name, fn, FILEMGR_FILE_NAME_SIZE);
            FileList.file[FileList.ptr].type = FILETYPE_FILE;
            FileList.ptr++;
          }
        }
      }
    }
  }

  NumObs = FileList.ptr;
  f_closedir(&dir);
  return res;
}

uint16_t AUDIO_GetWavObjectNumber(void)
{
  if (AUDIO_StorageParse() == FR_OK)
    return NumObs;
  return 0;
}

void Mount_SD(void)
{
  fresult = f_mount(&USERFatFS, USERPath, 1);
  if (fresult != FR_OK) {
	while(1);
  }
}

void Unmount_SD(void)
{
  fresult = f_mount(NULL, USERPath, 1);
}
