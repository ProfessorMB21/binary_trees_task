#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdarg.h>

namespace file_io
{
	/**
	* @brief Writes data to a file.
	*	If file does not exist a new file is created, otherwise data is appended
	*	to the given file.
	* @param filename - Name of the file where to write the data.
	* @param argc - Number of arguments to be supplied to the function that
	*	will be written to the file.
	* @returns Nothing
	*/
	void write_to_file(const char* filename, unsigned int argc, ...);

	/**
	* @brief Reads data from a file and write it to a tree.
	* @param filename - Nmae of the file from which the data is read.
	* @returns A tree with the data.
	*/
	void read_file_data(const char* filename, tree &root);
}
