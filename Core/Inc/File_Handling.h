/**
  ***************************************************************************************************************
  * File:       File_Handling.h
  * Author:     Adapted for STM32F407G-DISC1 with microSD (SPI)
  * Updated:    6th June 2025
  ***************************************************************************************************************
*/

#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

#include "fatfs.h"
#include "string.h"
#include "stdio.h"

#define FILEMGR_LIST_DEPDTH        24
#define FILEMGR_FILE_NAME_SIZE     40
#define FILEMGR_FULL_PATH_SIZE     256
#define FILEMGR_MAX_LEVEL          4

#define FILETYPE_DIR               0
#define FILETYPE_FILE              1

typedef struct _FILELIST_LineTypeDef {
  uint8_t type;
  uint8_t name[FILEMGR_FILE_NAME_SIZE];
} FILELIST_LineTypeDef;

typedef struct _FILELIST_FileTypeDef {
  FILELIST_LineTypeDef file[FILEMGR_LIST_DEPDTH];
  uint16_t ptr;
} FILELIST_FileTypeDef;

/* Mount the microSD card */
void Mount_SD(void);

/* Unmount the microSD card */
void Unmount_SD(void);

/* Get number of WAV files on SD */
uint16_t AUDIO_GetWavObjectNumber(void);

#endif /* FILE_HANDLING_H_ */
