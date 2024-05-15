#include "utils.h"

namespace file_io
{
	void file_io::write_to_file(const char* filename, unsigned int argc, ...)
	{
		va_list pdata;
		char* s = nullptr;

		va_start(pdata, argc);

		std::ofstream outfile(filename, std::ios_base::app);
		if (outfile.is_open())
		{
			for (unsigned int i = 0; i < argc; i++)
			{
				s = va_arg(pdata, char*);
				outfile << s << "\n";
			}
			outfile.close();
		}
		va_end(pdata);
	}

	void file_io::read_file_data(const char* filename, tree& root)
	{
		std::ifstream file(filename);
		if (file)
		{
			std::string _name, _gpa;
			while (!file.eof())
			{
				std::getline(file, _name);
				std::getline(file, _gpa);
				
				double pts = std::stod(_gpa);
				add(root, _name, pts);
			}
			file.close();
		}
	}

	tree read_file_data(const char* filename)
	{
		tree db;
		std::ifstream file(filename);
		if (file)
		{
			std::string _name, _gpa;
			while (!file.eof())
			{
				std::getline(file, _name);
				std::getline(file, _gpa);

				add(db, _name, std::stod(_gpa));
			}
			file.close();
		}
		return db;
	}
}
