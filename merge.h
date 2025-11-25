#pragma once

#ifndef MERGE
#define MERGE

/// mergeUnicornFiles writes the contents of each binary file in a specified directory
/// into a new zip file.
/// 
/// Input
/// `partition_location`: The folder where all of the binary files live
/// `zip_location`: The location to dump the new .zip file
void mergeUnicornFiles(char* partition_location, char* zip_location);

#endif