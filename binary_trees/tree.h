#pragma once

struct node
{
	int val;
	int count = 1;
	int height = 1;
	node* left = nullptr;
	node* right = nullptr;
};

struct tree
{
	node* root = nullptr;

};

bool add(tree& t, int value);
node* get(tree t, int value);
void remove(tree& t, int value);
void drop(tree& t);
int get_tree_height(const node* root);
