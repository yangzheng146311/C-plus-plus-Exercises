// L 9_ Class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include"node.h"

int main()
{
	node *n1 = new node(3);
	node *n2 = new node(1);
	node *n3 = new node(2);
	node *n4 = new node(4);
	node *n5 = new node(5);
	node *n6 = new node(6);
	
	n1->insert_integer(n2);
	n1->insert_integer(n3);
	n1->insert_integer(n4);
	n1->insert_integer(n5);
	n1->insert_integer(n6);

	n1->print_tree();
	n1->delete_tree();


	
	

    std::cout << "\t Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
