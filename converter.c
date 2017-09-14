#include <stdio.h>
#include <stdlib.h>

storedPPM* ppm_read(char* inFile)
{
	return 0;
}

int ppm_write(storedPPM* inData, char* ppmFormat, char* outFile)
{
	return 0;
}

// the stored PPM stores its format, width, height and max color and the header node for its pixels
typedef struct 
{
	int ppmFormat;
	int width;
	int height;
	int maxColor;
	node* header_pixel;
} storedPPM;