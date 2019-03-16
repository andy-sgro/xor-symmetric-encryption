
#include "main.h"
#include "domain.h"

#include <conio.h>


int main(int argc, char** argv)
{
	bool validFiles = false;

	if ((argc == NO_OUT) | (argc == HAS_OUT))
	{
		if (stricmp(KEY_ARG, FILE_ARG) == 0)
		{
			printf("Error: Cannot use the key to encrypt itself\n");
		}
		else
		{
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
		}
	}

	if (!validFiles)
	{
		printf(USAGE_STATEMENT);
	}

	return 0;
}



