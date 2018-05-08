#pragma once
#include "BinaryTrees/BST.h"
#include <ctime>

namespace Utils
{
	namespace Generation
	{
		int* GenerateRandomArray(const size_t size = 100, const bool random = true);
		int* CopyArray(int* p_array, const size_t p_size);

		template<typename TreeType, typename DataType>
		TreeType GenerateRandomTree(const size_t p_nodeCount, const DataType&& value, const bool random = true)
		{
			srand((unsigned)time(nullptr));
			TreeType tree;
			for (unsigned int i = 0; i < p_nodeCount; ++i)
			{
				int key = rand() % INT_MAX;
				auto* node = tree.Add(key, std::move(value));
				if (!node)
					--i;
			}

			return tree;
		}
	}
}
