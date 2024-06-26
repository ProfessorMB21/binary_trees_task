#pragma once
#include <string>
#include <iostream>

// struct for student
struct student_t
{
	std::string m_name;
	double m_gpa;
};
typedef student_t Stud;

struct node
{
	//Stud m_data;
	std::string m_name;
	double m_gpa;
	int count = 1;
	int height = 1;
	node* left = nullptr;
	node* right = nullptr;
};

struct tree
{
	node* root = nullptr;

};

bool add(tree& t, std::string _name, double _gpa);
node* get(tree t, std::string value);
void remove(tree& t, std::string value);
void drop(tree& t);
int get_tree_height(const node* root);
