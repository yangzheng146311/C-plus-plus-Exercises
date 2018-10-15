#pragma once
using namespace std;
#include<iostream>
#include<queue>
enum MyEnum
{
	Left,Right
};

class  node
{
public:
	int value;
	node *left;
	node *right;
	static queue<node*> _queue;
	node(int _value);
	~node();
	void insert_integer(node *newNode);
	void print_tree();
	void  Depth_First_Search();
	void Breadth_First();
	void  delete_tree();
};

