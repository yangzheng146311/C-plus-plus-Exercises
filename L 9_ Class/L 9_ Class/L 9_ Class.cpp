// L 9_ Class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include"node.h"

int main()
{
	
	node *n1 = new node(50);
	node *n2 = new node(45);
	node *n3 = new node(55);
	node *n4 = new node(42);
	node *n5 = new node(46);
	node *n6 = new node(52);
	node *n7 = new node(56);

	node n8(1);
	node n9(2);
	
	n1->insert_integer(n2);
	n1->insert_integer(n3);
	n1->insert_integer(n4);
	n1->insert_integer(n5);
	n1->insert_integer(n6);
	n1->insert_integer(n7);
	//n1->print_tree();
	
	n1->print_tree();
	//n1->delete_tree();
	delete n1;
    std::cout << "\t Hello World!\n"; 
}

