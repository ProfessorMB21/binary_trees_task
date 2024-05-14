#include "utils.h"
#include "cgi.h"
#include "tree.h"
#include "stack.h"

using namespace std;
using namespace cgi_utils;

//void search_form_data();
void collect_form_data();
void print(Student_stack* _storage);
bool _peek(stack_t*& stack);

template<typename T>
void search_tree(tree root, T _name, Student_stack*& _storage)
{
	search_tree<T>(root.root, _name, _storage);
}

// student search. works for c-strings and string only
template <typename T>
void search_tree(node* root, T _name, Student_stack*& _storage)
{
	if (!root) return;
	if (root->m_data.m_name[0] == _name[0])
	{
		push(_storage, root->m_data.m_name, root->m_data.m_gpa);
		_peek(_storage);
	}
	search_tree(root->left, _name, _storage);
	search_tree(root->right, _name, _storage);
}

bool _peek(stack_t*& stack)
{
	if (stack)
	{
		cout << stack->student_name << " " <<  stack->student_gpa << "<br>\n";
		return true;
	}
	return false;
}


int main()
{
	setlocale(LC_ALL, "");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("studnet.tmpl");
	if (file)
	{
		Student_stack* stud_data = nullptr;
		tree stud_tree;

		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			if (!strcmp(line, "<!--THANOS-->"))
			{
				collect_form_data();
			}
			else
				cout << line << endl;
		}
		clear(stud_data);
		delete[] line;
		file.close();
	}
	return 0;
}

// for student search
/*/
void search_form_data()
{
	cout << "<input type=\"text\" placeholder=\"Search by name\" name='name-search'>";
	cout << "<input type=\"submit\" class=\"submit-btn-form\" value=\"Search\" name='submit' id=\"btn-submit\">";
	
	if (get_request_method() == post) {
		char* data = nullptr;
		script_type_err e;
		Student_stack* _storage = nullptr;
		tree _source_db;

		file_io::read_file_data("student_db.txt", _source_db);
		get_param_value(data, "name-search", by_name);
		if (strlen(by_name) == 0)
		{
			e = err_name;
			script_err_run(e);
		}
		if (strlen(by_name) > 0)
		{
			string kword = by_name;
			search_tree<string>(_source_db, kword, _storage);
			print(_storage);
		}
		clear(_storage);
	}
}
*/

// for student addition to db
void collect_form_data()
{
	cout << "<form method=\"post\" action=\"studnet.cgi\" class=\"login-form cx-data\">";
	cout << "<input type=\"text\" placeholder=\"Full name\" name='name'>";
	cout << "<input type=\"number\" placeholder=\"GPA\" name='gpa' min='0' step='0.1'>";
	cout << "<input type=\"submit\" class=\"submit-btn-form\" value=\"Add student\" name='submit' id=\"btn-submit\">";
	cout << "<input type=\"text\" placeholder=\"Search by name\" name='name-search' style='margin-top: 30px'>";
	cout << "<input type=\"submit\" class=\"submit-btn-form\" value=\"Search\" name='submit' id=\"btn-submit-search\">";
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
		if (strlen(by_name) == 0 && strlen(_kword))
		{
			e = err_name;
			script_err_run(e);
		}
		if (strlen(by_name) > 0 && atof(by_gpa) >= 0.0)
		{
			e = script_type_err::acc_granted;
			script_err_run(e, "Student data entered into database!");
			file_io::write_to_file("trees_.txt", 2, by_name, by_gpa);
		}
		// data entry done, we perform the search
		if (strlen(_kword) > 0)
		{
			string kword = by_name;
			Student_stack* _storage = nullptr;
			tree _source_db;

			file_io::read_file_data("student_db.txt", _source_db);
			search_tree<string>(_source_db, kword, _storage);
			print(_storage);
		}
	}
}

// print search results
void print(Student_stack* _storage)
{
	auto* curr = _storage;

	if (curr)
	{
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
}
