#include "utils.h"
#include "cgi.h"
#include "tree.h"
using namespace std;
using namespace cgi_utils;

int main()
{
	setlocale(LC_ALL, "");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("studnet.tmpl");
	if (file)
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			if (!strcmp(line, "<!--FORM-->"))
			{
				// do smth
				cout << "-------In form section-------" << endl;
			}
			if (!strcmp(line, "<!--CONTENT-->"))
			{
				cout << "++++++++++++++In content section+++++++++++++" << endl;
				// do smth
			}
			else
				cout << line << endl;
		}
		file.close();
		delete[] line;
	}
	return 0;
}
