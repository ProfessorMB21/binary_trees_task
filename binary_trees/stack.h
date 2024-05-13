#include <stdlib.h>
#include <iostream>
#include "tree.h"
using namespace std;

struct stack_t
{
	string student_name;
	double student_gpa = 0.0;
	stack_t* next = nullptr;
};
typedef stack_t Student_stack;

void push(stack_t*& stack, string _name, double _gpa);
void push(stack_t*& stack, Stud _buf);
bool pop(stack_t*& stack);
void clear(stack_t*& stack);
