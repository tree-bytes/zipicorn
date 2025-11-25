#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_WIDTH 1024
#define CHUNK_BUFFER (1*1024*1024) 

void mergeUnicornFiles(char* partition_location, char* zip_location)
{
	struct stat buffer;

	//if stat() returns -1, then our file doesn't exist.
	if (stat(partition_location, &buffer) == -1)
	{
		printf("The directory containing our .UNICORN files does not exist!");
		return;
	}

	if (stat(zip_location, &buffer) == -1)
	{
		printf("The directory to place our zip file does not exist!");
		return;
	}


	//Find the first ".unicorn" file in our directory
	char full_path[FILE_WIDTH];

	//Get the total number of ".UNICORN" files
	size_t unicorn_count = 1;
	sprintf_s(full_path, FILE_WIDTH, "%s\\%d.unicorn", partition_location, unicorn_count);
	FILE* uni_looper = fopen(full_path, "rb");

	if (!uni_looper)
	{
		printf("Failed to open!");
	}

	do
	{
		if (uni_looper)
			fclose(uni_looper);
		sprintf_s(full_path, FILE_WIDTH, "%s\\%d.unicorn", partition_location, unicorn_count++);
	} while (fopen_s(&uni_looper, full_path, "rb") == 0);



	//Allocate memory on the heap for zip_file_name
	char* zip_file_name = malloc(FILE_WIDTH);
	if (!zip_file_name)
	{
		printf("Malloc failed for zip_file_name!");
		return;
	}
	//Create a buffer, allocating memory on the heap for it
	char* uni_file_location = malloc(FILE_WIDTH);
	if (!uni_file_location)
	{
		printf("Malloc failed for uni_file_location");
		free(zip_file_name);
		return;
	}
	//Create a buffer, allocating memory on the heap for it
	char* uni_file_content = malloc(CHUNK_BUFFER);
	if (!uni_file_content)
	{
		printf("Malloc failed for uni_file_content!");
		free(zip_file_name);
		free(uni_file_location);
		return;
	}

	//Define our new zip file and open it
	sprintf_s(zip_file_name, FILE_WIDTH, "%s\\%s", zip_location, "UNICORN.zip");
	FILE* destination_zip = fopen(zip_file_name, "wb");

	if (!destination_zip)
	{
		printf("Failed to open our destination zip file!");
		free(zip_file_name);
		free(uni_file_location);
		free(uni_file_content);
		return;
	}



	size_t bytes_read;

	//Invariance:
	//At the start of each loop, we will have read each previous .unicorn file and written its contents to
	//our desired .zip file.
	for (int i = 1; i < unicorn_count - 1; i++)
	{
		sprintf_s(uni_file_location, FILE_WIDTH, "%s\\%d.unicorn", partition_location, i);
		FILE* uni_file = fopen(uni_file_location, "rb");
		if (!uni_file)
		{
			printf("Exiting loop early; failed to open .UNICORN file...");
			break;
		}

		//Read our .unicorn file in chunks of "CHUNK_BUFFER" in order to prevent 
		//massive .unicorn files from overloading memory.
		while ((bytes_read = fread(uni_file_content, 1, CHUNK_BUFFER, uni_file)) > 0)
		{
			fwrite(uni_file_content, 1, bytes_read, destination_zip);
		}

		//Close our current .unicorn file
		fclose(uni_file);

	}

	fclose(destination_zip);

	free(zip_file_name);
	free(uni_file_location);
	free(uni_file_content);

}