#include "stack.h"

// Adds an item on top of the stack
void push(stack_t*& stack, string _name, double _gpa)
{
	stack_t* new_el = new stack_t;
	new_el->student_name = _name;
	new_el->student_gpa = _gpa;
	new_el->next = stack;
	stack = new_el;
}

void push(stack_t*& stack, Stud _buf)
{
	stack_t* new_el = new stack_t;
	new_el->student_name = _buf.m_name.data();
	new_el->student_gpa = _buf.m_gpa;
	new_el->next = stack;
	stack = new_el;
}

// Removes the item on top of the stack
// and returns the value of the removed item
bool pop(stack_t*& stack, Stud& _buf)
{
	if (stack)	// check if stack is not empty
	{
		_buf.m_name = stack->student_name;
		_buf.m_gpa = stack->student_gpa;
		auto* temp = stack;	// remove item on top of stack
		delete temp;
		stack = stack->next;
		return true;
	}
	return false;
}

// Removes the item on top of the stack
bool pop(stack_t*& stack)
{
	if (stack)
	{
		auto* temp = stack;
		stack = stack->next;
		delete temp;
		return true;
	}
	return false;
}

// Returns the value of the item on top of the stack
bool peek(stack_t*& stack, Stud& _buf)
{
	if (stack)
	{
		_buf.m_name = stack->student_name;
		_buf.m_gpa = stack->student_gpa;
		return true;
	}
	return false;
}

// Deallocates memory alloc'd to the stack
// Frees the entire stack
void clear(stack_t*& stack)
{
	while (stack) // check if top of stack is NULL
	{
		auto* temp = stack;
		stack = stack->next;
		delete temp;
	}
}
