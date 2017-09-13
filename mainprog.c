#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
			// check that the input file exists
			if (check_file_path(argv[2]) == 1)
			{

				// check the output file
					// call the program
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
	// should check if metadata and log file exists
	FILE *file;
    if ((file = fopen(fp, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}