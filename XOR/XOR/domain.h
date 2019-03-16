#pragma once

#include "common.h"

bool encryptFile(char* filepath, char* keyPath);
bool encryptFile(char* filepath, char* keyPath, char* output);
bool xorMem(char* fileBuf, char* keyBuf, unsigned int fileSize, unsigned int keyLength);
char* incMemRollover(char* start, char* ptr, unsigned int size);
char* fileIntoHeap(char* filepath, unsigned int* size);
int getFileSize(char* filepath);
int getFileSize(FILE* fp);
bool saveFile(char* srcMem, char* destPath, unsigned int size);