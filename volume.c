// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    uint8_t header[45];
    fread(header, 1, 44, input);
    fwrite(header, 1, 44, output);

    // Read samples from input file and write updated data to output file
    // ...

    // Read samples from input file and write updated data to output file
    if (fseek(input, 0, SEEK_END) != 0)
    {
        perror("Error seeking to end of file");
        return 1;
    }

    long size = ftell(input);
    fseek(input, HEADER_SIZE, SEEK_SET);

    int16_t *buffer = (int16_t *) malloc(size - HEADER_SIZE);
    if (buffer == NULL)
    {
        perror("Error allocating memory for buffer");
        fclose(input);
        fclose(output);
        return 1;
    }

    fread(buffer, 2, (size - HEADER_SIZE) / 2, input);

    for (int i = 0; i < (size - HEADER_SIZE) / 2; i++)
    {
        int16_t modify = (int16_t) (buffer[i] * factor);
        buffer[i] = modify;
    }

    fwrite(buffer, 2, (size - HEADER_SIZE) / 2, output);

    free(buffer);


    // Close files
    fclose(input);
    fclose(output);
}
