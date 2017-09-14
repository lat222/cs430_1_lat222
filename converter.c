#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

// the stored PPM stores its format, width, height and max color and the header node for its pixels
typedef struct 
{
	int ppmFormat;
	int width;
	int height;
	int maxColor;
	node* header_pixel;
} storedPPM;

storedPPM* ppm_read(char* inFile)
{
	storedPPM* storedData = NULL;
	FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(inFile, "r");

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

    fclose(fp);

    if (line)
        free(line);

	return storedData;
}

int ppm_write(storedPPM* inData, char* ppmFormat, char* outFile)
{
	if (inData == NULL)
	{
		return 1;
	}
	return 0;
}