#pragma once
#include <string>
#include <iostream>
#include <BinaryTrees/BinaryTree.h>

namespace BinaryTrees
{

	template <typename T>
	class BST : public BinaryTree<Node<T>, T>
	{
	public:
		BST()
		{}

		Node<T>* AddR(const int key, const T&& value)
		{
			if (!this->m_root)
			{
				this->m_root = new Node<T>(key, std::move(value));
				return this->m_root;
			}
			return AddR(this->m_root, key, std::move(value));
		}

		Node<T>* AddR(Node<T>* node, const int key, const T&& value) const
		{
			if (!node)
				node = new Node<T>(key, std::move(value));
			else if (key == node->key)
			{
				std::cerr << "Add node failed : Node " << key << " already exists with value :" << node->value << '\n';
				return nullptr;
			}

			else if (key < node->key)
				node->left = AddR(node->left, key, std::move(value));
			else
				node->right = AddR(node->right, key, std::move(value));

			return node;
		}

		Node<T>* Add(const int key, const std::string&& value) override
		{
			Node<T>** currentNode = &this->m_root;
			while (*currentNode)
			{
				if (key == (*currentNode)->key)
				{
					std::cerr << "Add node failed : Node " << key << " already exists with value :" << (*currentNode)->value << '\n';
					return nullptr;
				}
				if (key < (*currentNode)->key)
					currentNode = &(*currentNode)->left;
				else
					currentNode = &(*currentNode)->right;
			}
			*currentNode = new Node<T>(key, std::move(value));
			return *currentNode;
		}

	



		static void ReplaceChild(Node<T>** p_parent, Node<T>* p_child , Node<T>* p_newChild = nullptr)
		{
			if (*p_parent)
			{
				if ((*p_parent)->left == p_child)
				{
					(*p_parent)->left = p_newChild;
				}
				else if ((*p_parent)->right == p_child)
				{
					(*p_parent)->right = p_newChild;
				}
			}
		}

		bool RemoveSubtree(Node<T>* p_subroot, int key)
		{
			// Alternate between left and right successor to balance tree
			static bool useLeftSuccessor = false;

			Node<T>* currentNode = p_subroot;

			while(currentNode)
			{
				if (key == currentNode->key)
					break;
				if (key < currentNode->key)
					currentNode = currentNode->left;
				else
					currentNode = currentNode->right;
			}

			if (!currentNode)
				return true;

			if (currentNode->left && currentNode->right)
			{
				Node<T>* successor = (useLeftSuccessor) ? this->FindMax(currentNode->left) : this->FindMin(currentNode->right);
				const bool result = this->RemoveSubtree(successor, successor->key);
				currentNode->key = successor->key;
				currentNode->value = successor->value;
				delete successor;
				useLeftSuccessor = !useLeftSuccessor;
				return result;
			}
			Node<T>* parentNode = this->SearchParent(this->m_root, currentNode->key);
			if (currentNode->left)
				this->ReplaceChild(&parentNode, currentNode, currentNode->left);

			else if (currentNode->right)
				this->ReplaceChild(&parentNode, currentNode, currentNode->right);

			else
				this->ReplaceChild(&parentNode, currentNode, nullptr);
			return true;
		}
		bool Remove(int key) override
		{
			return this->RemoveSubtree(this->m_root, key);
		}

	};
}
