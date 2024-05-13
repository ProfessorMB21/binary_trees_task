#include "utils.h"
#include "tree.h"

namespace file_io
{
	void file_io::write_to_file(const char* filename, unsigned int argc, ...)
	{
		va_list pdata;
		char* s = nullptr;

		va_start(pdata, argc);

		ofstream outfile(filename, ios_base::app);
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

	void read_file_data(const char* filename, tree& root)
	{
		ifstream file(filename);
		if (file)
		{
			char _name[10000], _gpa[10000];
			while (!file.eof())
			{
				file.getline(_name, 10000);
				file.getline(_gpa, 10000);

				double pts = atof(_gpa);
				string n = _name;
				Stud new_student = { n, pts };
				add(root, new_student);
			}
			file.close();
		}
	}
}
