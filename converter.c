#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    // The is what is stored in a pixel
    unsigned char R, G, B;
}pixel;

// the stored PPM stores its format, width, height and max color and the header node for its pixels
typedef struct 
{
	char* ppmFormat;
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

    // read_header makes sure the header is completely read in,
    // and right now, none of the header has been read in.
    int read_header = 0;

    while ((read = getline(&line, &len, fp)) != -1) {

    	// check to see if we are just starting to read, then we need to store
    	// information like the ppm format, width, height, and maxColor of the image
    	if(read_header < 4)
    	{
    		// check that the line is not a comment
    		if(line[0] != '#')
    		{
    			char* token = strtok(line, " \t");
    			while(token)
    			{
    				printf("Token: %s\n", token);
    				switch(read_header)
		    		{
		    			case 0:
		    				storedData->ppmFormat = (char*) malloc(sizeof(char)*2);
		    				strcpy(storedData->ppmFormat,token);
		    				read_header++;
		    				break;

		    			case 1:
		    				storedData->width = atoi(token);
		    				read_header++;
		    				break;

		    			case 2:
		    				storedData->height = atoi(token);
		    				read_header++;
		    				break;

		    			case 3:
		    				storedData->maxColor = atoi(token);
		    				read_header++;
		    				break;

		    		}
		    		token = strtok(NULL, " \t");
    			}
	    			
    		}

    	}

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