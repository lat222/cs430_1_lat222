#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "converter.c"
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
					storedPPM* inData = ppm_write(argv[2]);
					int returned = ppm_read(inData, argv[1],argv[3]);
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