#pragma once

#include "common.h"

bool encryptFile(char* filepath, char* keyPath);
bool encryptFile(char* filepath, char* keyPath, char* output);
bool xorMem(char* fileBuf, char* keyBuf, int fileSize, int keyLength);
char* incMemRollover(char* start, char* ptr, int size);
char* fileIntoHeap(char* filepath, int* size);
int getFileSize(char* filepath);
int getFileSize(FILE* fp);
bool saveFile(char* srcMem, char* destPath, int size);