#pragma once

#ifndef PARTITION
#define PARTITION

/// partitionZipFile writes binary files of size `chunk_size` to the specified directory.
///
/// Input
/// `zip_file`: The directory of the zip_file
/// `destination`: The directory to dump all of the binary files
/// `chunk_size`: How big each binary file should be
/// 
/// Output
/// None
void partitionZipFile(char* zip_file, char* destination, const size_t chunk_size);

#endif