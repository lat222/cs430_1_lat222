#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    // The is where the colors for a pixel are stored
    unsigned char R, G, B;
}pixel;

// below are global variables that will be accessible throughout the entire program
char* ppmFormat;
int width;
int height;
int maxColor;
pixel* pixMap;

// this function checks if input file exists 
// and returns a 0 if the file exists and a 1 if not
int check_file_path(char* fp)	
{
	FILE *file;
	// if the file can be opened for reading, then it exists
    if ((file = fopen(fp, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// function to read in header (as was described in Chapter 2) from input file
// header information is stored to global variables above
int read_header(FILE* fp)
{
	// variables to store what is read in from input file
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // readHeader marks that none of the header has been stored yet.
    int readHeader = 0;

    // loop to read in all pertinent header information (i.e. ppm format, width, height, and maxColor of the image)
    while (readHeader < 4) {

    	// check that a line has been read in
    	if((read = getline(&line, &len, fp)) != -1)
    	{
    		// check that the line is not a comment
    		if(line[0] != '#')
    		{
    			char* token = strtok(line, " \t");	// split the line on the first whitespace

    			// check to make sure the new token could be split on the whitespace
    			while(token)
    			{
    				// based on what has already been stored, switch to store new header information
    				switch(readHeader)
		    		{
		    			case 0:
		    				ppmFormat = (char*) malloc(sizeof(char)*2); // create the space to store this string
		    				strncpy(ppmFormat,token,2);		// copy the token to the global variable ppmFormat
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
		    					return 1;
		    				}
		    				readHeader++;
		    				break;

		    		}
		    		token = strtok(NULL, " \t"); // continue breaking up the read in line by white space
    			}    			
    		}
    	}
    	// no line has been read in; so the file and the header are wrong
    	else
    	{
    		fprintf(stderr, "Error: Header is incorrect.\n");
    		return 1;	
    	}
    }

    // free up the space used by line
	if (line)
    {
        free(line);
    }

    return 0;	// successful so return 0

}

// read in a ppm with p3 format
int read_p3(FILE* fp)
{
	int r,g,b;		// the ints that will store each pixel's RGB values
	int pixelsSaved = 0;	// stores the number of pixels already in memory

	// loop through the entire image of pixels from the input file as defined by the file's height and width
	while(pixelsSaved < width*height)
	{
		// save the incoming pixel as long as it exists
		if(fscanf(fp,"%d", &r) != EOF && fscanf(fp,"%d", &g) != EOF && fscanf(fp,"%d", &b) != EOF)
		{
			// make sure each color of the pixel is less than or equal to the maxColor
			if(r > maxColor || g > maxColor || b > maxColor)
			{
				fprintf(stderr, "Error: R, G, or B of pixel %d is not within max color range.\n", pixelsSaved);
				return 1;
			}
			// otherwise, store the pixel values within pixMap array of pixel structs
			pixMap[pixelsSaved].R = r;
			pixMap[pixelsSaved].G = g;
			pixMap[pixelsSaved].B = b;
			pixelsSaved++;		// increase the index for pixels stored
		}
		// all of the pixels do not exist; so err out
		else
		{
			fprintf(stderr, "Error: End of file reached before all pixels read.\n");
			return 1;
		}
	}
	return 0;	// success so return 0
}

// read in a ppm with p6 format
int read_p6(FILE* fp)
{
	unsigned char rawPixel[3];	// array to store the each pixel's RGB values

	int pixelsSaved = 0;	// index for how many pixels have been stored

	// loop through the entire image of pixels from the input file as defined by the file's height and width
	while(pixelsSaved < width*height)
	{
		// read in the 3 byte chunk that give the R,G,B values for the pixel
		if(fread(rawPixel, sizeof(unsigned char), 3, fp) == 3)
		{
			// store the pixel values within pixMap array of pixel structs
			pixMap[pixelsSaved].R = rawPixel[0];
			pixMap[pixelsSaved].G = rawPixel[1];
			pixMap[pixelsSaved].B = rawPixel[2];
			pixelsSaved++;		// increase the index for pixels stored
		}
		else
		{
			fprintf(stderr, "Error: Pixel %d did not read in 3 bytes.\n", pixelsSaved);
			return 1;
		}
	}
	return 0;	// success so return 0
}

// write to file in p3 format
void write_p3(FILE* fp)
{
	int pixelsWritten = 0;

	// loop through all the stored pixels and write their values to the output file
	while (pixelsWritten < height*width)
	{
		fprintf(fp, "%d\n%d\n%d\n", pixMap[pixelsWritten].R, pixMap[pixelsWritten].G, pixMap[pixelsWritten].B);
		pixelsWritten++;
	}
}

// write to file in p6 format
void write_p6(FILE* fp)
{
	// writes everyhting stored in pixmap to the output file
	fwrite(pixMap, sizeof(pixel), height*width, fp);
}


int main(int argc, char* argv[]) 
{
	// checks that the correct number of command line arguments were given
	if (argc != 4)		// any number other than 4 arguments means the wrong amount given
	{
		fprintf(stderr, "Error: Incorrect number of arguments. Requires 3 arguments-- NOT %d.\n", argc-1);
		return 1;
	}
	else	// the right amount of command line arguments(4) were given
	{
		// check that the right PPM format is inputted
		if (strcmp(argv[1],"3") == 0 || strcmp(argv[1],"6") == 0)
		{
			// check that the input file exists
			if (check_file_path(argv[2]) == 1)
			{
				// create the file pointer and open the input file for reading
				FILE* fp;
				fp = fopen(argv[2], "r");
				// call read_header to store all header information and check that it returned successfully
				if(read_header(fp) == 0)
				{
					pixMap = (pixel*) malloc(sizeof(pixel)*height*width);	// create the space in memory to store the pixels from the input file

					// read in image pixels based on the format of the input file
					if(strcmp("P3", ppmFormat) == 0)
					{
						if(read_p3(fp) == 1)
						{
							// error message prints in function; so out here just stop running by returning 1
							return 1;
						}
					}
					else if(strcmp("P6", ppmFormat) == 0)
					{
						if(read_p6(fp) == 1)
						{
							// error message prints in function; so out here just stop running by returning 1
							return 1;
						}
					}
					// the input file was not P6 or P3 type; so it cannot be read.
					else
					{
						fprintf(stderr, "Error: PPM Format of input file should be P3 or P6 -- NOT %s\n", ppmFormat);
						return 1;
					}
				}
				// read_header() failed so close the file and stop running here
				else
				{
					fclose(fp);
					return 1;
				}

			    fclose(fp);		// done with the input file so close it
				
			    // WRITING BEGINS
				fp = fopen(argv[3], "w");	// open the file to write to
				// write header into file
				fprintf(fp, "P%s\n%d %d\n%d\n", argv[1], width, height, maxColor);

				// write to file based off of the command line argument
				if(strcmp(argv[1], "3")  == 0)
					write_p3(fp);
				else
					write_p6(fp);


				fclose(fp);		// done with the output file so close it
	
			}
			// input file does not exist
			else
			{
				fprintf(stderr, "Error: File with name %s does not exist.\n", argv[2]);
				return 1;
			}

		}
		// command line argument for conversion is not 3 or 6
		else
		{
			fprintf(stderr, "Error: Can only convert P3 or P6 formats-- NOT P%s.\n", argv[1]);
			return 1;
		}
		
	}
	return 0;		// success so return 0
}

