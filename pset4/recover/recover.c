#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;
int main(int argc, char *argv[])
{
    char *name = malloc(3);
    //check if there is an image name
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //initializer of input and output
    FILE *raw_file;
    FILE *photo;
    raw_file = fopen(argv[1], "r");
    //check if file is not null
    if (raw_file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }
    int images = 0;
    bool isJPG = false;
    //allocation of buffer
    BYTE *buffer = malloc(BLOCK_SIZE);
    //main loop
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //iterates trough each block of 512 bytes
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            //checks if there is a start of a jpg image
            if (buffer[i] == (int)strtol("ff", NULL, 16))
            {
                if (buffer[i + 1] == (int)strtol("d8", NULL, 16))
                {
                    if (buffer[i + 2] == (int)strtol("ff", NULL, 16))
                    {
                        //if there is set the name of output and isJPG = true
                        printf("Image Detected\n");
                        isJPG = true;
                        images++;
                        if (images - 1 <= 9)
                        {
                            sprintf(name, "00%d", images - 1);
                        }
                        else if (images - 1 >= 10 && images - 1 <= 99)
                        {
                            sprintf(name, "0%d", images - 1);
                        }
                        else if (images - 1 >= 100 && images - 1 <= 999)
                        {
                            sprintf(name, "%d", images - 1);
                        }
                        strcat(name, ".jpg");
                        photo = fopen(name, "w");
                    }
                }
            }
            //if this is true it writes bytes in ouput file
            if (isJPG)
            {
                fwrite(&buffer[i], sizeof(BYTE), 1, photo);
            }
        }
    }
    printf("%d", images);
    free(name);
    free(buffer);
    return 0;
}