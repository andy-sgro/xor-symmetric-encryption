#include "domain.h"

/**
* \brief	Encrypts a file, using another file as the key.
*
* \param	char* filepath:	The file that is to be encrypted.
* \param	char* keyPath:  The key to encrypt the file with.
*
* \return	Returns true if the encryption is successful, false if otherwise.
*/
bool encryptFile(char* filepath, char* keyPath)
{
	return encryptFile(filepath, keyPath, filepath);
}


/**
* \brief	Encrypts a file, using another file as the key.
*
* \param	char* filepath:	The file that is to be encrypted.
* \param	char* keyPath:  The key to encrypt the file with.
* \param	char* outPath:  The destination of the cyphertext.
*
* \return	Returns true if the encryption is successful, false if otherwise.
*/
bool encryptFile(char* filepath, char* keyPath, char* outPath)
{
	bool retcode = false;
	unsigned int fileSize = 0;
	unsigned int keyLength = 0;

	char* fileBuf = fileIntoHeap(filepath, &fileSize);
	char* keyBuf = fileIntoHeap(keyPath, &keyLength);

	// put both file and key into heap
	if (fileBuf && keyBuf)
	{
		retcode = true;
		xorMem(fileBuf, keyBuf, fileSize, keyLength);
		saveFile(fileBuf, outPath, fileSize);
	}

	free(fileBuf);
	free(keyBuf);

	return retcode;
}



/**
* \brief	Saves a chunk of memory to the file system.
*
* \details	This only works if the file is not being used by another process.
*
* \param	char* srcMem:	The memory to save.
* \param	char* destPath:	The destination to save the memory to.
* \param	int size:		The size of the memory chunk to save.
*
* \return	Returns true if all arguments are valid, false if otherwise.
*/
bool saveFile(char* srcMem, char* destPath, unsigned int size)
{
	bool retcode = false;

	if (srcMem && destPath && size)
	{
		FILE* fp = fopen(destPath, "wb");
		if (fp)
		{
			if (fwrite(srcMem, sizeof(char), size, fp) == size)
			{
				retcode = true;
			}
			fclose(fp);
		}
	}

	return retcode;
}



/**
* \brief	Applies the xor operator to the bytes in a chunk of memory.
*
* \details	This is useful for symmetric encryption.
*
* \param	char* fileBuf:	The chunk of memory to be xor'd.
* \param	char* keyBuf:	The key to xor the memory with.
* \param	int fileSize:	The size of the memory chunk to xor.
* \param	int keyLength:	The length of the key that xors the memory.
*
* \return	Returns true if all arguments are valid. Otherwise false is returned.
*/
bool xorMem(char* fileBuf, char* keyBuf, unsigned int fileSize, unsigned int keyLength)
{
	bool retcode = false;

	if (fileBuf && keyBuf && fileSize && keyLength)
	{
		retcode = true;
		char* pFile = fileBuf;
		char* pKey = keyBuf;

		for (unsigned int i = 0; i < fileSize; ++i)
		{
			*pFile++ ^= *pKey;
			pKey = incMemRollover(keyBuf, pKey, keyLength);
		}
	}

	return retcode;
}



/**
* \brief	Increments a pointer.
*
* \details	If the pointer is beyond a certain point, it rolls over.
*
* \param	char* start: Starting point of the pointer.
* \param	char* ptr:	 Pointer to increment.
* \param	int size:	 Limit where the rollover happens.
*
* \return	Returns an incremented pointer.
*/
inline char* incMemRollover(char* start, char* ptr, unsigned int size)
{
	return (ptr < (start + size - 1)) ? (ptr + 1) : start;
}
	


/**
* \brief	Copies a file into the heap.
*
* \details	The file must be free'd after.
*			This function won't work if another process is using
*			the file.
*
* \param	char* filepath:	The file to copy into the heap.
* \param	int* size:		The size of the memory allocation. (OUTPUT)
*
* \return	Returns true if all arguments are valid, otherwise false is returned.
*/
char* fileIntoHeap(char* filepath, unsigned int* size)
{
	bool isValid = false;
	char* fileBuffer = NULL;
	*size = 0;

	FILE *fp = fopen(filepath, "rb");
	if (!fp)
	{
		isValid = false;
	}
	else
	{
		unsigned int fileSize = getFileSize(fp);

		// put filedata into heap
		fileBuffer = (char*)malloc(fileSize);
		if (!fileBuffer)
		{
			isValid = false;
		}
		else
		{
			if (!(fread(fileBuffer, sizeof(char), fileSize, fp) == fileSize))
			{
				free(fileBuffer);
				fileBuffer = NULL;
			}
			else
			{
				*size = fileSize;
			}
		}
		fclose(fp);
	}

	return fileBuffer;
}



/**
* \brief	Returns the size of the file (in bytes).
*
* \param	char* filepath: The file to see the size of.
*
* \return	Returns the size of the file (in bytes).
*/
int getFileSize(char* filepath)
{
	int fileSize = 0;
	
	FILE *fp = fopen(filepath, "rb");
	if (fp)
	{
		fileSize = getFileSize(fp);
		fclose(fp);
	}

	return fileSize;
}



/**
* \brief	Returns the size of the file (in bytes).
*
* \param	FILE* fp: The file to see the size of.
*
* \return	Returns the size of the file (in bytes).
*/
int getFileSize(FILE* fp)
{
	fseek(fp, 0L, SEEK_END);
	int fileSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	return fileSize;
}