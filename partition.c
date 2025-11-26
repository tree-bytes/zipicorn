#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

//Create our buffer for memory, ~1mb
#define CHUNK_BUFFER (1*1024*1024) 
#define FILE_WIDTH 1024

void partitionZipFile(char* zip_file, char* destination, const size_t chunk_size)
{
	struct _stat64 buffer;

	//if stat() returns -1, then our file doesn't exist.
	if (_stat64(zip_file, &buffer) == -1)
	{
		printf("The zip file does not exist!");
		return;
	}
	if (_stat64(destination, &buffer) == -1)
	{
		printf("The destination path does not exist!");
		return;
	}

	//Next, check to see if our file path is actually a zip file
	if (strstr(zip_file, ".zip") == NULL)
	{
		printf("Input file needs to be a zip file!");
		return;
	}
	//Last but not least, let's ensure that chunk_size > 0
	if (chunk_size <= 0)
	{
		printf("Chunk size must be bigger than 0 bytes!");
		return;
	}


	//Open the file
	FILE* zip = fopen(zip_file, "rb");
	if (!zip)
	{
		printf("Couldn't open the file");
		return;
	}
	size_t bytes_read;
	size_t bytes_written = 0;
	unsigned int chunk_idx = 1;

	//Unsigned char for chunk because we will be reading/writing binary
	//We use malloc() to allocate these to the heap. This keeps the stack cleaner.
	unsigned char* chunk = malloc(CHUNK_BUFFER);
	if (!chunk) {
		printf("Malloc failed for chunk!\n");
		return;
	}

	char* output_file = malloc(FILE_WIDTH);
	if (!output_file) {
		printf("Malloc failed for output_file!\n");
		free(chunk);
		return;
	}

	char* destination_file = malloc(FILE_WIDTH);
	if (!destination_file) {
		printf("Malloc failed for destination_file!\n");
		free(chunk);
		free(output_file);
		return;
	}


	sprintf_s(output_file, FILE_WIDTH, "%d.unicorn", chunk_idx);
	sprintf_s(destination_file, FILE_WIDTH, "%s\\%s", destination, output_file);

	FILE* out_file = fopen(destination_file, "wb");
	if (!out_file)
	{
		free(chunk);
		free(output_file);
		free(destination_file);

		printf("Failed to open output file!");
		return;
	}

	while ((bytes_read = fread(chunk, 1, CHUNK_BUFFER, zip)) > 0)
	{
		//If for some reason, we do not have an out_file,
		//stop the loop early.
		if (!out_file)
			break;


		fwrite(chunk, 1, bytes_read, out_file);

		if ((bytes_written += bytes_read) >= chunk_size)
		{
			bytes_written = 0;
			fclose(out_file);
			sprintf_s(output_file, FILE_WIDTH, "%d.unicorn", ++chunk_idx);
			sprintf_s(destination_file, FILE_WIDTH, "%s\\%s", destination, output_file);

			errno_t file_did_open = fopen_s(&out_file, destination_file, "wb");
			if (file_did_open != 0)
			{
				printf("Failed to open file %d", chunk_idx);
				break;
			}
		}
	}
	if (out_file)
	{
		fclose(out_file);
	}


	fclose(zip);
	//Free the heap up
	free(chunk);
	free(output_file);
	free(destination_file);
	return;
}