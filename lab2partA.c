#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define WORD_SIZE 20

int main(int argc, char *argv[])
{
    char *fileName = argv[1];

    FILE *fptr;
    fptr = fopen(fileName, "r");

    if (fptr == NULL)
    {
        printf("Error opening file: %s\n", fileName);
        return -1;
    }

    char **word = malloc(WORD_SIZE * sizeof(char*));
    int capacity = INITIAL_CAPACITY;
    int wordCount = 0;
    int lineCount = 0;

     while (fscanf(fptr, "%ms", word) == 1)
    {
        wordCount++;
        if (wordCount == capacity)
        {
            // Double the capacity using realloc
            capacity = capacity * 2;
            word = realloc(word, WORD_SIZE * capacity * sizeof(char));
            if (word == NULL)
            {
                printf("Error reallocating memory\n");
                return -1;
            }
        }
    }

    fclose(fptr); // Close the file

    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("Error reopening file: %s\n", fileName);
        free(word);
        return -1;
    }

    int ch;
    ch = fgetc(fptr);
    if (ch == '\n')
    {
        lineCount++;
    }

    // Reset file pointer to the beginning
    fseek(fptr, 0, SEEK_SET);

    int wordsInCurrentLine = 0;

    while (fscanf(fptr, "%ms", word) == 1)
    {
        wordsInCurrentLine++;
        if (fgetc(fptr) == '\n')
        {
                printf("%d ", wordsInCurrentLine);
                wordsInCurrentLine = 0;
                lineCount++;
        }
     }
     fseek(fptr, -1, SEEK_CUR);

    free(word);
    fclose(fptr);

    printf("\n%d words on %d lines\n", wordCount, lineCount);

    return 0;
}

