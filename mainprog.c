#include <string.h>
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


int main(int argc, char* argv[]) 
{
	// checks that the correct number of command line arguments were given
	if (argc != 4)		// any number other than 4 arguments means the wrong amount given
	{
		fprintf(stderr, "Error: Incorrect number of arguments. Requires 3 arguments-- NOT %d.\n", argc-1);
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
					storedPPM* inData = ppm_read(argv[2]);
					printf("Write returns: %d.\n",ppm_write(inData, argv[1],argv[3]));
					// call the program
					/*if(ppm_convert(argv[1],argv[2],argv[3])==0)
					{
						printf("Success!!\n");
					}
					else
					{
						fprintf(stderr, "Error: Files could not be converted");
					}*/
				}
				else
				{
					fprintf(stderr, "Error: File with name %s exists and will not be overwritten.\n", argv[3]);
				}
			}
			else
			{
				fprintf(stderr, "Error: File with name %s does not exist.\n", argv[2]);
			}

		}
		else
		{
			fprintf(stderr, "Error: Can only convert P3 or P6 formats-- NOT P%s.\n", argv[1]);
		}
		
	}
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