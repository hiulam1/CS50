#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.");
        return 1;
    }

    // Read header
    // TODO #3

    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4

    if (check_format(header) == 1)
    {
        printf("Input is not a WAV file.");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7

    int block_size = get_block_size(header);
    // Write reversed audio to file
    // TODO #8

    // block size is 4 bytes, int16_t is 2 bytes, so every block has 2 int16_t
    int16_t temp[block_size / sizeof(int16_t)];
    fseek(input, sizeof(WAVHEADER), SEEK_SET);

    int num_blocks = header.subchunk2Size / block_size; // total data size / block size to find out how many blocks to reverse
    for (int i = 1; i <= num_blocks; i++)
    {
        fseek(input, block_size * -i, SEEK_END); // loop to end of the input
        fread(temp, block_size, 1, input);       // copy last block
        fseek(output, 0, SEEK_END);
        fwrite(temp, block_size, 1, output); // append last block to output
    }
    // find out how many blocks are there
    // printf("%i\n", header.subchunk2Size);

    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    BYTE wave[4] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (wave[i] != header.format[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (int) header.blockAlign;
}