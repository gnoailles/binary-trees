#include <vld.h>
#include "BinaryTrees/BST.h"
#include "Utils/generation.h"
#include "Utils/Timer.h"
#include <iostream>
#include "BinaryTrees/AVL.h"
#include "BinaryTrees/RBT.h"

int main()
{
	BinaryTrees::RBT<std::string> tree;
	tree.Add(30, "7");
	tree.Add(20, "4");
	tree.Add(40, "5");
	tree.Add(50, "2");
//	tree.Add(8, "8");
//	tree.Add(9, "9");

	tree.Remove(20);

	tree.Display();
	std::cout << "\nNode Count: " << tree.Count() << "\n";
	std::cout << "Tree Height: " << tree.GetHeight() << "\n\n";

	tree.ReverseDisplay();

	system("pause");
	return 0;
}
