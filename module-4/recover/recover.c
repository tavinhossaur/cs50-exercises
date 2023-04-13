#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check the usage
    if(argc != 2)
    {
        printf("Command: ./recover file.raw\n");
        return 1;
    }

    // Open the file for reading
    FILE *inptr = fopen(argv[1], "r");

    // Check the file
    if(inptr == NULL)
    {
        printf("The file '%s' could not be opened.\n", argv[1]);
        return 2;
    }

    // Set outfile pointer to NULL
    FILE* outptr = NULL;

    // 512 bytes array to get "chunks" of the image
    BYTE buffer[512];

    // Track the amount of image files
    int jpeg = 0;

    // Filename created and initialized all values to 0
    char filename[8] = {0};

    // While there is data to read in the .raw
    while(fread(buffer, sizeof(BYTE)*512, 1, inptr) == 1)
    {
        // Check for a JPEG
        if(buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // Close the current output file if it was already written
            if(outptr != NULL) fclose(outptr);

            // Add up to the filename
            sprintf(filename, "%03d.jpg", jpeg++);

            // Open a new output file for writing
            outptr = fopen(filename, "w");
        }

       // Keep writing until finding a new file
       if(outptr != NULL) fwrite(buffer, sizeof(BYTE)*512, 1, outptr);
    }

    // Close the lastest output file and the input file
    if (outptr != NULL) fclose(outptr);
    fclose(inptr);

    return 0;
}