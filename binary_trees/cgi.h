#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

namespace cgi_utils
{
	enum request_method {
		get, post
	};

	request_method get_request_method();
	void get_form_data(char*& result);
	void get_param_value(const char* data, const char* param_name, char*& value);
	char* get_current_url();
	char* get_host_ip();

	enum script_type_err
	{
		no_script_run,
		no_data,
		err_all,
		err_name,
		err_invalid_gpa,
		acc_granted
	};

	script_type_err script_err_run(script_type_err e);
	script_type_err script_err_run(script_type_err e, const char* _msg);
}
