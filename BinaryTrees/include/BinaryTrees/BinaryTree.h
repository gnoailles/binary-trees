#pragma once
namespace BinaryTrees
{
	template <typename T>
	struct Node
	{
		int key;

		T value;
		Node<T>* left;
		Node<T>* right;

		Node(const int key) :
			key(key),
			left(nullptr),
			right(nullptr)
		{}
		Node(const int key, const T&& value) :
			key(key),
			value(value),
			left(nullptr),
			right(nullptr)
		{}
	};

	template <typename NodeT, typename T>
	class BinaryTree
	{
	protected:
		NodeT* m_root;

	public:

		BinaryTree() : m_root(nullptr){};

		virtual ~BinaryTree()
		{
			if (m_root)
				Clear();
		}

		virtual NodeT* Add(const int key, const std::string&& value) = 0;
		virtual bool Remove(int key) = 0;

		virtual void Clear()
		{
			PostOrderTraversalR(m_root, [](NodeT*& p_node)
			{
				delete p_node;
				p_node = nullptr;
			}
			);
		}

		static NodeT* SearchR(NodeT* node, const int key)
		{
			if (!node || node->key == key)
				return node;
			if (key < node->key)
				return SearchR(node->left, key);

			return SearchR(node->right, key);
		}
		virtual NodeT* Search(const int key) const
		{
			NodeT* currentNode = m_root;

			while (currentNode)
			{
				if (key == currentNode->key)
					return currentNode;
				if (key < currentNode->key)
					currentNode = currentNode->left;
				else
					currentNode = currentNode->right;
			}
			return currentNode;
		}
	
		static NodeT* SearchParent(NodeT* p_subRoot, const int key)
		{
			if (!p_subRoot) return nullptr;

			NodeT* currentNode = p_subRoot;

			while (currentNode)
			{
				if (!currentNode->left && !currentNode->right)
					return nullptr;

				if ((currentNode->left && currentNode->left->key == key) || (currentNode->right && currentNode->right->key == key))
					return currentNode;

				if (key < currentNode->key)
					currentNode = currentNode->left;
				else
					currentNode = currentNode->right;
			}
			return currentNode;
		}

		static NodeT* FindMin(NodeT* p_parent)
		{
			NodeT* currentNode = p_parent;
			while (currentNode->left)
				currentNode = currentNode->left;

			return currentNode;

		}
		static NodeT* FindMax(NodeT* p_parent)
		{
			NodeT* currentNode = p_parent;
			while (currentNode->right)
				currentNode = currentNode->right;

			return currentNode;

		}


		void ReverseInOrderTraversal(void (p_callback)(NodeT*))
		{
			// Using Morris Inorder Tree Traversal
			NodeT* parentNode = m_root;
			NodeT* currentNode = m_root;

			while (currentNode)
			{

				if (!currentNode->right)
				{
					p_callback(currentNode);
					currentNode = currentNode->left;
				}
				else
				{
					parentNode = currentNode->right;

					while (parentNode->left && parentNode->left != currentNode)
						parentNode = parentNode->left;

					if (!parentNode->left)
					{
						parentNode->left = currentNode;
						currentNode = currentNode->right;
					}

					else
					{
						parentNode->left = nullptr;
						p_callback(currentNode);
						currentNode = currentNode->left;
					}
				}
			}
		}
		void InOrderTraversal(void (p_callback)(NodeT*))
		{
			// Using Morris Inorder Tree Traversal
			NodeT* parentNode = m_root;
			NodeT* currentNode = m_root;

			while (currentNode)
			{

				if (!currentNode->left)
				{
					p_callback(currentNode);
					currentNode = currentNode->right;
				}
				else
				{
					parentNode = currentNode->left;

					while (parentNode->right && parentNode->right != currentNode)
						parentNode = parentNode->right;

					if (!parentNode->right)
					{
						parentNode->right = currentNode;
						currentNode = currentNode->left;
					}

					else
					{
						parentNode->right = nullptr;
						p_callback(currentNode);
						currentNode = currentNode->right;
					}
				}
			}
		}
		void PostOrderTraversalR(NodeT*& p_node, void (p_callback)(NodeT*&))
		{
			if (!p_node)
				return;

			if (p_node->left) PostOrderTraversalR(p_node->left, p_callback);
			if (p_node->right) PostOrderTraversalR(p_node->right, p_callback);

			p_callback(p_node);
		}

		virtual void Display()
		{
			InOrderTraversal([](NodeT* p_node)
			{
				std::cout << p_node->value << '\n';
			}
			);

		}
		virtual void ReverseDisplay()
		{
			ReverseInOrderTraversal([](NodeT* p_node)
			{
				std::cout << p_node->value << std::endl;
			});
		}

		NodeT* SetValue(int key, const std::string&& value) const
		{
			NodeT* node = Search(key);
			if (node)
			{
				node->value = value;
				return node;
			}
			return nullptr;
		}

		int Count() const
		{
			return CountR(m_root);
		}
		int CountR(NodeT* p_node) const
		{
			if (!p_node) return 0;

			return 1 + CountR(p_node->left) + CountR(p_node->right);
		}

		virtual int GetHeight() const {
			return GetHeightR(m_root);
		}
		int GetHeightR(NodeT* p_node) const {
			if (p_node == nullptr) return -1;

			const int leftH = GetHeightR(p_node->left);
			const int rightH = GetHeightR(p_node->right);


			return (leftH > rightH) ? leftH + 1 : rightH + 1;
		}
	
		T GetValue(int key) const
		{
			NodeT* node = Search(key);
			if (node)
				return node->value;
			return nullptr;
		}
		T operator[](int key) const
		{
			NodeT* node = Search(key);
			if (node)
				return node->value;
			return nullptr;
		}

		NodeT* GetRoot() const
		{
			return m_root;
		}
	};
}
