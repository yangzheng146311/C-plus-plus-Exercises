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
		cout << "Value->" << value << "  node delete" << endl;
		

     }

    


	void insert_integer(node *newNode)
	{
		if (newNode != NULL)
		{
			if (newNode->value < this->value)
			{
				if (this->left == NULL)
				{
					this->left = newNode;
				}
				else
				{
					this->left->insert_integer(newNode);
				}
			}

			else
			{
				if (this->right == NULL)
				{
					this->right = newNode;
				}
				else
				{
					this->right->insert_integer(newNode);
				}
			}

		}

		else
		{
			cout << "The node is NULL" << endl;
		}

		return;
	}

		
		/*if (branch == Left)
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
			return false;*/
	

	

public :void print_tree()
	{
		this->Depth_First_Search();
		cout << endl;

	}

    void  Depth_First_Search()
	{
		if (this != NULL)
		{
			 cout <<this->value<<"\t";
			 this->left->Depth_First_Search();
			 this->right->Depth_First_Search();
			 
			
		}

		else
		{

			return;
		}

	}

	void  delete_tree()
	{
		if (this->left != NULL)
		{
			this->left->delete_tree();
		}
		

		if (this->right != NULL)
		{
			this->right->delete_tree();
		}

		delete this;
		

		
		

	}



};