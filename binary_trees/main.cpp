#include "utils.h"
#include "cgi.h"
#include "tree.h"
#include "stack.h"

using namespace std;
using namespace cgi_utils;

void collect_form();
void print(Student_stack* _storage);

template<typename T>
void search_tree(tree root, T _name, Student_stack*& _storage)
{
	search_tree<T>(root.root, _name, _storage);
}

// student search. Meant to work for c-strings and std::string only
template <typename T>
void search_tree(node* root, T _name, Student_stack*& _storage)
{
	if (!root) return;
	if (toupper(root->m_name[0]) == toupper(_name[0]))
	{
		push(_storage, root->m_name, root->m_gpa);
	}
	search_tree(root->left, _name, _storage);
	search_tree(root->right, _name, _storage);
}

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
			if (!strcmp(line, "<!--THANOS-->"))
			{
				collect_form();
			}
			else
				cout << line << endl;
		}
		delete[] line;
		file.close();
	}
	return 0;
}

// for student addition to db
void collect_form()
{
	cout << "<form method=\"post\" action=\"studnet.cgi\" class=\"login-form cx-data\">";
	cout << "<input type=\"text\" placeholder=\"Full name\" name='name'>";
	cout << "<input type=\"number\" placeholder=\"GPA\" name='gpa' min='0' step='0.1'>";
	cout << "<input type=\"submit\" class=\"submit-btn-form\" value=\"Add student\" name='submit' id=\"btn-submit\">";
	cout << "<input type=\"text\" placeholder=\"Search by name\" name='name-search' style='margin-top: 30px'>";
	cout << "<input type=\"submit\" class=\"submit-btn-form\" value=\"Search\" name='submit' id=\"btn-submit\">";
	cout << "</form>";

	if (get_request_method() == post)
	{
		char* data = nullptr;
		script_type_err e;

		get_form_data(data);

		char* by_name = nullptr;
		char* by_gpa = nullptr;
		char* _kword = nullptr;

		get_param_value(data, "name", by_name);
		get_param_value(data, "gpa", by_gpa);
		get_param_value(data, "name-search", _kword);
		if (atof(by_gpa) < 0.0)
		{
			e = err_invalid_gpa;
			script_err_run(e);
		}
		if ((strlen(by_name) > 0 && strlen(by_gpa) > 0) && atof(by_gpa) >= 0.0)
		{
			e = script_type_err::acc_granted;
			script_err_run(e, "Student data entered into database!");
			file_io::write_to_file("trees_.txt", 2, by_name, by_gpa);
		}
		// data entry done, we perform the search
		if (strlen(_kword) > 0)
		{
			string kword = _kword;
			Student_stack* _storage = nullptr;
			tree _source_db = file_io::read_file_data("trees_.txt");

			search_tree<string>(_source_db, kword, _storage);
			print(_storage);
		}
	}
}

// print search results
void print(Student_stack* _storage)
{
	auto* curr = _storage;

	cout << "<table cellspacing='0' style='margin-top: 40px'><thead><tr>" \
		"<th>Full name</th><th>GPA</th></tr></thead>\n";
	cout << "<tbody>";
	while (curr)
	{
		cout << "<tr>";
		cout << "<td class=\"cell\" data-title=\"Full Name\">";
		cout << curr->student_name << "</td>";
		cout << "<td class=\"cell\" data-title=\"Full Name\">";
		cout << curr->student_gpa << "</td></tr>";
		curr = curr->next;
	}
	cout << "</tbody></table>" << endl;
}
