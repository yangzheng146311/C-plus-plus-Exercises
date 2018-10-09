#pragma once
using namespace std;
#include<iostream>
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

	node(int _value)
	{

		value = _value;
		left = NULL;
		right = NULL;
		
	}

	~node()
	{
		if (left != NULL)
		{
			delete left;
			left = NULL;
		}

		if (right != NULL)
		{
			delete left;
			right = NULL;
		}

     }

    


	bool insert_integer(node *newNode,int branch)
	{
		if (branch == Left)
		{
			left = newNode;
			left->value = newNode->value;
			return true;
		}

		if (branch == Right)
		{
			right = newNode;
			right->value = newNode->value;
			return true;
		}

	
			cout << "wrong input";
			return false;
		


	}

	void print_tree(node )
	{



	}



};