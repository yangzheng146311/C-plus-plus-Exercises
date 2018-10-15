#include "node.h"

queue<node*> node::_queue = std::queue<node*>();

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