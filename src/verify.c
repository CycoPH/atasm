#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "md5.h"

#ifdef MSVC
#define STRCASECMP(a,b) _stricmp((a),(b))
#else
#define STRCASECMP(a,b) strcasecmp((a),(b))
#endif



void print_hash(uint8_t *p)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		printf("%02x", p[i]);
	}
	printf("\n");
}

void read(char *filename, uint8_t* result)
{
	FILE* toRead = fopen(filename, "rb");
	if (toRead == NULL)
	{
		printf("Unable to read:'%s'\n", filename);
		exit(1);
	}
	md5File(toRead, result);
	fclose(toRead);
}

int main(int argc, char *argv[])
{
	uint8_t result[16] = { 0 };

	if (argc == 2)
	{
		read(argv[1], result);
		print_hash(result);
		return 0;
	}
	else if (argc == 3)
	{
		// arg1 = filename
		// arg2 = md5 to compare with
		read(argv[1], result);

		char ascii_md5hash[33];
		for (unsigned int i = 0; i < 16; ++i)
		{
			sprintf(&ascii_md5hash[i*2], "%02x", result[i]);
		}

		if (STRCASECMP(ascii_md5hash, argv[2]) == 0)
		{
			printf("%s - Hash Ok\n", argv[1]);
			return 0;
		}
		printf("%s - Hash Failed\n", argv[1]);
		return 1;
	}
	else
	{
		printf("verify path-to-file md5\n");
		printf("\tRead the contents of the file, calculate the md5 and verify that its the same as the supplied one\n");
		return 1;
	}
}
