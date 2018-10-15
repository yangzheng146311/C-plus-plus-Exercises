#include "pch.h"
#include "node.h"

queue<node*> node::_queue = std::queue<node*>();

node::node(int _value)
{

	value = _value;
	left = NULL;
	right = NULL;

}

node::~node()
{
	cout << "Value->" << value << "  node delete" << endl;
	delete_tree();

}
void node::insert_integer(node *newNode)
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
void node::print_tree()
{
	bool run = true;
	int input = 0;
	while (run)
	{
		cout << "press'1' for Depth First;" << endl;
		cout << "press '2' for Breadth First;" << endl;
		cout<<"press '3' to exit." << endl;
		cin >> input;
		switch (input)
		{
		case 1:this->Depth_First_Search(); break;
		case 2:this->Breadth_First(); break;
		case 3:run = false; break;
		default:
			break;
		}
		cout << endl;
	}

}
void  node::Depth_First_Search()
{
	if (this != NULL)
	{
		cout << this->value << "\t";
		this->left->Depth_First_Search();
		this->right->Depth_First_Search();

	}

	else
	{

		return;
	}

}
void node::Breadth_First()
{
	_queue.push(this);

	while (_queue.size() > 0)
	{
		if (_queue.front()->left != NULL) _queue.push(_queue.front()->left);

		if (_queue.front()->right != NULL) _queue.push(_queue.front()->right);
		cout << _queue.front()->value << "\t";
		_queue.pop();
	}
	cout << endl;

}
void  node::delete_tree()
{
	if (this->left != NULL)
	{
		this->left->delete_tree();
		delete this->left;
		this->left = NULL;
	}


	if (this->right != NULL)
	{
		this->right->delete_tree();
		delete this->right;
		this->right = NULL;
	}

	// this;	

}