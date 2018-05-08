#include <Utils/generation.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "Utils/Timer.h"
#include <iostream>

namespace Utils
{
	namespace Generation
	{
		int* GenerateRandomArray(const size_t p_size, const bool random)
		{
			srand((unsigned)time(nullptr));
			int* arr = new int[p_size];
			if(!random)
			{
				memset(arr, 0, p_size * sizeof(int));
			}
			else
			{
				for(unsigned int i = 0; i < p_size; ++i)
				{
					arr[i] = rand() % INT_MAX;
				}
			}
			return arr;
		}


		int* CopyArray(int* p_array, const size_t p_size)
		{
			int* arr = new int[p_size];
			memcpy(arr, p_array, p_size * sizeof(int));
			return arr;
		}
	}
}
