
#include "main.h"
#include "domain.h"

#include <conio.h>


int main(int argc, char** argv)
{
	bool validFiles = false;

	if (argc == NO_OUT)
	{
		if (encryptFile(FILE_ARG, KEY_ARG))
		{
			validFiles = true;
		}
	}
	else if (argc == HAS_OUT)
	{
		if (encryptFile(FILE_ARG, KEY_ARG, OUT_ARG))
		{
			validFiles = true;
		}
	}

	if (!validFiles)
	{
		printf("Usage: <file to encrypt> <key file> (optional: <output filepath>\n");
	}

	return 0;
}



