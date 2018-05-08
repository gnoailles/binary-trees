#pragma once
#include "BinaryTree.h"
#include <algorithm>
#include <string>

namespace BinaryTrees
{
	enum class COLOR : bool 
	{
		RED = false, 
		BLACK = true,
		DOUBLE_BLACK = true,
	};

	template <typename T>
	struct ColorNode
	{
		COLOR color;
		int key;

		T value;
		ColorNode<T>* left;
		ColorNode<T>* right;
		ColorNode<T>* parent;

		ColorNode(const int key, const COLOR color = COLOR::RED) :
			color(color),
			key(key),
			left(nullptr),
			right(nullptr),
			parent(nullptr)
		{
		}

		ColorNode(const int key, const T&& value, const COLOR color = COLOR::RED) :
			color(color),
		    key(key),
		    value(value),
		    left(nullptr),
		    right(nullptr),
		    parent(nullptr)
		{
		}
	};

	template <typename T>
	class RBT : public BinaryTree<ColorNode<T>, T>
	{
	public:
		RBT() = default;

		ColorNode<T>* Add(const int key, const std::string&& value) override
		{
			ColorNode<T>* newNode = new ColorNode<T>(key, std::move(value));

			this->m_root = InsertBST(this->m_root, newNode);

			FixViolation(this->m_root, newNode);

			return newNode;
		}

		ColorNode<T>* InsertBST(ColorNode<T>* p_subRoot, ColorNode<T>* p_newNode)
		{
			if (!p_subRoot)
				return p_newNode;


			if (p_newNode->key < p_subRoot->key)
			{
				p_subRoot->left = InsertBST(p_subRoot->left, p_newNode);
				p_subRoot->left->parent = p_subRoot;
			}

			else if (p_newNode->key > p_subRoot->key)
			{
				p_subRoot->right = InsertBST(p_subRoot->right, p_newNode);
				p_subRoot->right->parent = p_subRoot;
			}

			return p_subRoot;
		}

		void FixViolation(ColorNode<T>* &p_root, ColorNode<T>* &p_node)
		{
			ColorNode<T>* parent = nullptr;
			ColorNode<T>* gr_parent = nullptr;

			while((p_node != p_root) && (p_node->color != COLOR::BLACK) && (p_node->parent->color == COLOR::RED))
			{
				parent = p_node->parent;
				gr_parent = p_node->parent->parent;

				if(parent == gr_parent->left)
				{
					ColorNode<T>* uncle = gr_parent->right;

					if(uncle && uncle->color == COLOR::RED)
					{
						gr_parent->color = COLOR::RED;
						parent->color = COLOR::BLACK;
						uncle->color = COLOR::BLACK;
						p_node = gr_parent;
					}
					else
					{
						
						if(p_node == parent->right)
						{
							LeftRotate(parent);
							p_node = parent;
							parent = p_node->parent;
						}

						RightRotate(gr_parent);
						std::swap(parent->color, gr_parent->color);
						p_node = parent;


					}
				}
				else
				{
					ColorNode<T>* uncle = gr_parent->left;

					if(uncle && uncle->color == COLOR::RED)
					{
						gr_parent->color = COLOR::RED;
						parent->color = COLOR::BLACK;
						uncle->color = COLOR::BLACK;
						p_node = gr_parent;
					}
					else
					{
						if(p_node = parent->left)
						{
							RightRotate(parent);
							p_node = parent;
							parent = p_node->parent;
						}

						LeftRotate(gr_parent);
						std::swap(parent->color, gr_parent->color);
						p_node = parent;
					}
				}
			}

			p_root->color = COLOR::BLACK;
		}


		void LeftRotate(ColorNode<T>*& p_node)
		{
			ColorNode<T>* rightNode = p_node->right;

			p_node->right = rightNode->left;

			if (p_node->right)
				p_node->right->parent = p_node;

			rightNode->parent = p_node->parent;

			if (!p_node->parent)
				this->m_root = rightNode;

			else if (p_node == p_node->parent->left)
				p_node->parent->left = rightNode;

			else
				p_node->parent->right = rightNode;

			rightNode->left = p_node;
			p_node->parent = rightNode;
		}

		void RightRotate(ColorNode<T>*& p_node)
		{
			ColorNode<T>* leftNode = p_node->left;

			p_node->left = leftNode->right;

			if (p_node->left)
				p_node->left->parent = p_node;

			leftNode->parent = p_node->parent;

			if (!p_node->parent)
				this->m_root = leftNode;

			else if (p_node == p_node->parent->left)
				p_node->parent->left = leftNode;

			else
				p_node->parent->right = leftNode;

			leftNode->right = p_node;
			p_node->parent = leftNode;
		}

		bool Remove(int key) override
		{
			ColorNode<T>* node = DeleteBST(this->m_root, key);
			if (!node)
				return false;
			FixDeleteRBTree(node);
			return true;
		}

		ColorNode<T>* DeleteBST(ColorNode<T>*& p_subRoot, int key)
		{
			if (!p_subRoot) 
				return  p_subRoot;

			if (key < p_subRoot->key)
				return DeleteBST(p_subRoot->left, key);

			if (key > p_subRoot->key)
				return DeleteBST(p_subRoot->right, key);

			if (!p_subRoot->left || !p_subRoot->right)
				return p_subRoot;

			ColorNode<T>* temp = BinaryTree<ColorNode<T>, T>::FindMin(p_subRoot->right);
			p_subRoot->key = temp->key;

			return DeleteBST(p_subRoot->right, temp->key);
		}
	
		void FixDeleteRBTree(ColorNode<T>*& p_node) 
		{
			if (!p_node)
				return;

			if(p_node == this->m_root)
			{
				this->m_root = nullptr;
				return;
			}

			if (GetColor(p_node) == COLOR::RED || GetColor(p_node->left) == COLOR::RED || GetColor(p_node->right) == COLOR::RED)
			{
				ColorNode<T>* child = (p_node->left) ? p_node->left : p_node->right;

				if (p_node == p_node->parent->left)
				{
					p_node->parent->left = child;

					if (child)
						child->parent = p_node->parent;

					SetColor(child, COLOR::BLACK);
					delete p_node;
				}
				else
				{
					p_node->parent->right = child;
					if (child)
						child->parent = p_node->parent;

					SetColor(child, COLOR::BLACK);
					delete p_node;
				}
			}
			else
			{
				ColorNode<T>* sibling = nullptr;
				ColorNode<T>* parent = nullptr;
				ColorNode<T>* ptr = p_node;

				SetColor(ptr, COLOR::DOUBLE_BLACK);

				while(ptr != this->m_root && GetColor(ptr) == COLOR::DOUBLE_BLACK)
				{
					parent = ptr->parent;
					if(ptr == parent->left)
					{
						sibling = parent->right;

						if(GetColor(sibling) == COLOR::RED)
						{
							SetColor(sibling, COLOR::BLACK);
							SetColor(parent, COLOR::RED);
							LeftRotate(parent);
						}
						else
						{
							if(GetColor(sibling->left) == COLOR::BLACK && GetColor(sibling->right) == COLOR::BLACK)
							{
								SetColor(sibling, COLOR::RED);

								if (GetColor(parent) == COLOR::RED)
									SetColor(parent, COLOR::BLACK);
								else
									SetColor(parent, COLOR::DOUBLE_BLACK);
								ptr = parent;
							}
							else
							{
								if(GetColor(sibling->right) == COLOR::BLACK)
								{
									SetColor(sibling->left, COLOR::BLACK);
									SetColor(sibling, COLOR::RED);
									RightRotate(sibling);
									sibling = parent->right;
								}

								SetColor(sibling, parent->color);
								SetColor(parent, COLOR::BLACK);
								SetColor(sibling->right, COLOR::BLACK);
								LeftRotate(parent);
								break;
							}
						}
					}
					else
					{
						sibling = parent->left;
						if (GetColor(sibling) == COLOR::RED)
						{
							SetColor(sibling, COLOR::BLACK);
							SetColor(parent, COLOR::RED);
							RightRotate(parent);
						}
						else
						{
							if (GetColor(sibling->left) == COLOR::BLACK && GetColor(sibling->right) == COLOR::BLACK)
							{
								SetColor(sibling, COLOR::RED);

								if (GetColor(parent) == COLOR::RED)
									SetColor(parent, COLOR::BLACK);
								else
									SetColor(parent, COLOR::DOUBLE_BLACK);
								ptr = parent;
							}
							else
							{
								if(GetColor(sibling->left) == COLOR::BLACK)
								{
									SetColor(sibling->right, COLOR::BLACK);
									SetColor(sibling, COLOR::RED);

									LeftRotate(sibling);
									sibling = parent->left;
								}

								SetColor(sibling, parent->color);
								SetColor(parent, COLOR::BLACK);
								SetColor(sibling->left, COLOR::BLACK);
								RightRotate(parent);
								break;
							}
						}
					}
				}

				if (p_node == p_node->parent->left)
					p_node->parent->left = nullptr;
				else
					p_node->parent->right = nullptr;

				delete p_node;
				SetColor(this->m_root, COLOR::BLACK);
			}
		}

		static COLOR GetColor(ColorNode<T>* p_node)
		{
			return (p_node) ? p_node->color : COLOR::BLACK;
		}
		static void SetColor(ColorNode<T>* p_node, const COLOR color)
		{
			if (!p_node)
				return;

			p_node->color = color;
		}
	};
}
