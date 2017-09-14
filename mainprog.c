#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    // The is what is stored in a pixel
    unsigned char R, G, B;
}pixel;


char* ppmFormat;
int width;
int height;
int maxColor;
pixel* pixMap;


int ppm_read(char* inFile)
{
	
}

int ppm_write(char* ppmFormat, char* outFile)
{
	return 0;
}

int check_file_path(char* fp)	
{
	// should check if input file exists
	FILE *file;
    if ((file = fopen(fp, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// function to read in header from an input file as described in Chapter 2
// header information is stored to global variables above
int read_header(FILE* fp)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // read_header makes sure the header is completely read in,
    // and right now, readHeader marks that none of the header has been read in.
    int readHeader = 0;

    while (readHeader < 4) {

    	// check to see if we are just starting to read, then we need to store
    	// information like the ppm format, width, height, and maxColor of the image
    	if((read = getline(&line, &len, fp)) != -1)
    	{
    		// check that the line is not a comment
    		if(line[0] != '#')
    		{
    			char* token = strtok(line, " \t");
    			while(token)
    			{
    				printf("Token: %s\n", token);
    				switch(readHeader)
		    		{
		    			case 0:
		    				ppmFormat = (char*) malloc(sizeof(char)*2);
		    				strcpy(ppmFormat,token);
		    				readHeader++;
		    				break;

		    			case 1:
		    				width = atoi(token);
		    				readHeader++;
		    				break;

		    			case 2:
		    				height = atoi(token);
		    				readHeader++;
		    				break;

		    			case 3:
		    				maxColor = atoi(token);
		    				// check that maxColor is in acceptable range
		    				if (maxColor > 255 || maxColor < 0)
		    				{
		    					fprintf(stderr, "Error: Input file's max color should range from  0-255 -- NOT %d.\n", maxColor);
		    				}
		    				readHeader++;
		    				break;

		    		}
		    		token = strtok(NULL, " \t");
    			}    			
    		}
    	}
    	else
    	{
    		fprintf(stderr, "Error: Header is incorrect.\n");
    		return 1;	
    	}
    }

	if (line)
    {
        free(line);
    }

    return 0;

}

int read_p3(FILE* fp)
{
	return 0;
}

int read_p6(FILE* fp)
{
	return 0;
}

int main(int argc, char* argv[]) 
{
	// checks that the correct number of command line arguments were given
	if (argc != 4)		// any number other than 4 arguments means the wrong amount given
	{
		fprintf(stderr, "Error: Incorrect number of arguments. Requires 3 arguments-- NOT %d.\n", argc-1);
		return 1;
	}
	else				// right amount (4) given
	{
		// check that the right PPM format is inputted
		if (strcmp(argv[1],"3") == 0 || strcmp(argv[1],"6") == 0)
		{
			printf("PPM format is correct!!\n");

			// check that the input file exists
			if (check_file_path(argv[2]) == 1)
			{
				printf("Input file exists!!\n");

				// check the output file does not exist
				if(check_file_path(argv[3]) == 0)
				{
					printf("Output file does not exist!!\n ---Begin reading!!!---\n");
					FILE* fp;
					fp = fopen(argv[2], "r");
					if(read_header(fp) == 0)
					{
						pixMap = (pixel*) malloc(sizeof(pixel)*height*width);
						// read in image pixels
						if(strcmp("P3", ppmFormat) == 0)
						{
							int returnVal = read_p3(fp);
						}
						else if(strcmp("P6", ppmFormat) == 0)
						{
							int returnVal = read_p6(fp);
						}
						else
						{
							fprintf(stderr, "Error: PPM Format of input file should be P3 or P6 -- NOT %s\n", ppmFormat);
							return 1;
						}
					}
					else
					{
						fclose(fp);
						return 1;
					}

				    fclose(fp);
					

					printf("Write returns: %d.\n",ppm_write(argv[1],argv[3]));
				}
				else
				{
					fprintf(stderr, "Error: File with name %s exists and will not be overwritten.\n", argv[3]);
					return 1;
				}
			}
			else
			{
				fprintf(stderr, "Error: File with name %s does not exist.\n", argv[2]);
				return 1;
			}

		}
		else
		{
			fprintf(stderr, "Error: Can only convert P3 or P6 formats-- NOT P%s.\n", argv[1]);
			return 1;
		}
		
	}
	return 0;
}

