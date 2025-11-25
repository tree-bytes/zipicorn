#pragma once
#include <stdio.h>
#include <stdbool.h>

/// setLocationValues reads a file path from stdin.
/// 
/// Input
/// `value`: A string which clarifies the input type for the user (input or output file)
/// `output`: Our declared path variable, which should be passed in by reference.
/// `out_size`: The size of the output string
/// 
/// Outputs
/// Nothing
void setLocationValues(char* value, char* output, size_t out_size);


/// getPartitionMode decides whether we are using partition mode (creating partitions), or not, depending on user input from standard in,
/// and changse the value passed in-place.
/// 
/// Inputs:
/// `do_partition`: an existing boolean variable passed in as a reference
/// 
/// Outputs:
/// None
void getPartitionMode(bool* do_partition);


/// returnChunkSizes reads a `size_t` from stdin, and returns that value.
/// 
/// Inputs
/// None
/// 
/// Outputs
/// A variable of type `size_t`, which indicates the size that each chunk should be.
size_t returnChunkSizes();