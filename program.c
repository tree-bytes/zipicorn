#include "program.h"
#include "partition.h"
#include "merge.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

#define INPUT_WIDTH 1024

void setLocationValues(char* value, char* output, size_t out_size)
{
    printf("Enter %s path: ", value);
    //Check: Did we actually succeed in reading a value from stdin?
    if (fgets(output, out_size, stdin) == NULL) {
        //If not, error out.
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }

    output[strcspn(output, "\n")] = '\0';
}

void getPartitionMode(bool* do_partition)
{
    printf("Type 'y' to partition the file: ");
    char buffer[INPUT_WIDTH];

    if (fgets(buffer, INPUT_WIDTH, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (strcmp(buffer, "y") == 0)
    {
        *do_partition = true;
    }

    return;

}

size_t returnChunkSizes()
{
    printf("Type in your desired chunk size: ");
    size_t input;

    if (scanf_s("%zu", &input) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }

    return input;

}

int main(void)
{
    char input_location[INPUT_WIDTH];
    char output_location[INPUT_WIDTH];
    bool partition = false;

    setLocationValues("input", input_location, sizeof(input_location));
    setLocationValues("output", output_location, sizeof(output_location));
    getPartitionMode(&partition);

    if (partition)
    {
        //if partitioning, we need to decide how large our chunks need to be.
        size_t chunk_sizing = returnChunkSizes();

        partitionZipFile(input_location, output_location, chunk_sizing);

    }
    else
    {
        //Call the merge function
        mergeUnicornFiles(input_location, output_location);
    }


    //Finally, let's give the user a headsup the program is over
    printf("\nExecution completed. Press any button to terminate the program.");
    _getch();
    return 0;
}
