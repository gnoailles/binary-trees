#pragma once
#include "BinaryTree.h"
#include <stddef.h>
#include <utility>
#include <string>
#include <algorithm>

namespace BinaryTrees
{
	template <typename T>
	struct HeightNode
	{
		int key;
		int height;

		T value;
		HeightNode<T>* left;
		HeightNode<T>* right;

		HeightNode(const int key, const int height = 1) :
			key(key),
			height(height),
			left(nullptr),
			right(nullptr)
		{}
		HeightNode(const int key, const T&& value, const int height = 1) :
			key(key),
			height(height),
			value(value),
			left(nullptr),
			right(nullptr)
		{}

		int Balance() { return (((left) ? left->height : 0) - ((right) ? right->height : 0)); }
	};

	template<typename T>
	class AVL : public BinaryTree<HeightNode<T>, T>
	{

	public:
		AVL() {}

		HeightNode<T>* Add(const int key, const std::string&& value) override
		{
			//TODO implement iterative insertion
			if (!this->m_root)
			{
				this->m_root = new HeightNode<T>(key, std::move(value));
				return this->m_root;
			}
			return AddR(this->m_root, key, std::move(value));
		}
		HeightNode<T>* AddR(const int key, const std::string&& value)
		{
			if (!this->m_root)
			{
				this->m_root = new HeightNode<T>(key, std::move(value));
				return this->m_root;
			}
			return AddR(this->m_root, key, std::move(value));
		}

		HeightNode<T>* AddR(HeightNode<T>* p_subRoot, const int key, const std::string&& value)
		{
			if (!p_subRoot)
				return new HeightNode<T>(key, std::move(value));

			if (key < p_subRoot->key)
				p_subRoot->left = AddR(p_subRoot->left, key, std::move(value));
			else if (key > p_subRoot->key)
				p_subRoot->right = AddR(p_subRoot->right, key, std::move(value));
			else
				return p_subRoot;

			p_subRoot->height = 1 + std::max(Height(p_subRoot->left), Height(p_subRoot->right));

			const int balance = p_subRoot->Balance();
			HeightNode<T>* rotateResult = nullptr;

			if (balance > 1 && key < p_subRoot->left->key)
				rotateResult = RightRotate(p_subRoot);

			else if (balance < -1 && key > p_subRoot->right->key)
				rotateResult = LeftRotate(p_subRoot);

			else if (balance > 1 && key > p_subRoot->left->key)
			{
				p_subRoot->left = LeftRotate(p_subRoot->left);
				rotateResult = RightRotate(p_subRoot);
			}

			else if (balance < -1 && key < p_subRoot->right->key)
			{
				p_subRoot->right = RightRotate(p_subRoot->right);
				rotateResult = LeftRotate(p_subRoot);
			}
			else
				return p_subRoot;

			if (p_subRoot == this->m_root) this->m_root = rotateResult;
			return rotateResult;
		}

		bool Remove(int key) override
		{
			//TODO implement iterative deletion
			return RemoveR(this->m_root, key);
		}
		bool RemoveR(int key)
		{
			return RemoveR(this->m_root, key);
		}
		HeightNode<T>* RemoveR(HeightNode<T>* p_subRoot, int key)
		{
			if (!p_subRoot) 
				return p_subRoot;

			if (key < p_subRoot->key)
				p_subRoot->left = RemoveR(p_subRoot->left, key);

			else if (key > p_subRoot->key)
				p_subRoot->right = RemoveR(p_subRoot->right, key);

			else
			{
				if (!p_subRoot->left || !p_subRoot->right)
				{
					HeightNode<T>* child = (p_subRoot->left) ? p_subRoot->left : p_subRoot->right;

					if (!child)
					{
						child = p_subRoot;
						p_subRoot = nullptr;
					}
					else
						*p_subRoot = *child;
						
					delete child;
				}
				else
				{
					HeightNode<T>* child = this->FindMin(p_subRoot->right);

					p_subRoot->key = child->key;

					p_subRoot->right = RemoveR(p_subRoot->right, child->key);
				}
			}


			//Update height & Rotate
			if (!p_subRoot) 
				return p_subRoot;

			p_subRoot->height = 1 + std::max(Height(p_subRoot->left), Height(p_subRoot->right));

			const int balance = p_subRoot->Balance();
			HeightNode<T>* rotateResult = nullptr;


			if (balance > 1 && p_subRoot->left->Balance() >= 0)
				rotateResult = RightRotate(p_subRoot);

			else if (balance < -1 && p_subRoot->right->Balance() <= 0)
				rotateResult = LeftRotate(p_subRoot);

			else if (balance > 1 && p_subRoot->left->Balance() < 0)
			{
				p_subRoot->left = LeftRotate(p_subRoot->left);
				rotateResult = RightRotate(p_subRoot);
			}
			else if (balance < -1 && p_subRoot->right->Balance() > 0)
			{
				p_subRoot->right = RightRotate(p_subRoot->right);
				rotateResult = LeftRotate(p_subRoot);
			}
			else
				return p_subRoot;

			if (p_subRoot == this->m_root) this->m_root = rotateResult;
			return rotateResult;

		}


		HeightNode<T>* LeftRotate(HeightNode<T>* x)
		{
			HeightNode<T>* y = x->right;
			HeightNode<T>* T2 = y->left;

			y->left = x;
			x->right = T2;

			x->height = 1 + std::max(Height(x->left), Height(x->right));
			y->height = 1 + std::max(Height(y->left), Height(y->right));

			return y;
		}

		HeightNode<T>* RightRotate(HeightNode<T>* y)
		{
			HeightNode<T>* x = y->left;
			HeightNode<T>* T2 = x->right;

			x->right = y;
			y->left = T2;

			y->height = std::max(Height(y->left), Height(y->right)) + 1;
			x->height = std::max(Height(x->left), Height(x->right)) + 1;

			return x;
		}

		int GetHeight() const override
		{
			return this->m_root->height;
		}

	private:
		static int Height(HeightNode<T>* p_node)
		{ return (p_node) ? p_node->height : 0; }
	};



}
