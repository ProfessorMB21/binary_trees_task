#pragma once
#include <string>
#include <iostream>
using namespace std;

// struct for student
struct student_t
{
	string m_name;
	double m_gpa;
};
typedef student_t Stud;

struct node
{
	Stud m_data;
	int count = 1;
	int height = 1;
	node* left = nullptr;
	node* right = nullptr;
};

struct tree
{
	node* root = nullptr;

};

bool add(tree& t, Stud student);
node* get(tree t, string value);
void remove(tree& t, string value);
void drop(tree& t);
int get_tree_height(const node* root);
