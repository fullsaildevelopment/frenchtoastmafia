#pragma once
#include <type_traits>
#include <array>
#include <cassert>
#include <list>
#include "basic_structs.h"

template<typename T, int N>

class Effects
{
	using storage_type = std::aligned_storage_t<sizeof(T), alignof(T)>;

	int free_start = 0;

	union entry_t
	{
		storage_type storage;
		size_t next;
	};

	std::array<entry_t, N> data;

public:
	Effects()
	{
		for (int i = 0; i < data.size(); i++)
		{
			data[i].next = i + 1;         // data[i] = free_start;
		}
	}

	template<typename...Args>	// Variadic template parameters
	T* allocate(Args&&...args)	// Variadic function parameters
	{
		if (free_start == N)
		{
			return nullptr;
		}
		void* space = &data[free_start]; // Pop and element from the free list to allocate space


		free_start = data[free_start].next;


		// If no space, return nullptr

		// This is an example of using placement new and forwarding the parameters
		// to the constructor of T. If no matching constructor exists, it will be a compile-time error
		return new (space) T{ std::forward<Args>(args)... };
	}

	void release(T* ptr)
	{
		// If ptr maps to a valid index in the pool, 
		//	destruct it then push it on to the free list

		// store the address of the first index to the data array
		// cast that 2 something      that something(data type is in the free function
		// take pointer parameter and subtract it by the variable you casted 

		T* firstUp = (T*)&data[0];
		auto differential = ptr - firstUp;

		if (differential >= 0 && differential < N)
		{
			ptr->~T();
			data[differential].next = free_start;
			free_start = differential;
		}
	}

	~Effects()
	{

	}
};

//template<typename T, uint16_t N>
//class sorted_effects
//{
//public:
//	// Todo : Implement the sorted_pool class
//
//		// Do the same thing as last thing pool except u dont have free_start you have to make your own variable
//		// Use PowerPoint for reference
//
//	using storage_type = std::aligned_storage_t<sizeof(T), alignof(T)>;
//
//	uint16_t particles = 0;
//
//	std::array<storage_type, N> sortedParticlePool;
//
//	template<typename...Args>	// Variadic template parameters
//	T* allocate(Args&&...args)	// Variadic function parameters
//	{
//		if (particles == N)
//		{
//			return nullptr;
//		}
//
//		void* poolSpace = &sortedParticlePool[particles++]; // Pop and element from the free list to allocate space
//
//		// If no space, return nullptr
//
//		return new (poolSpace) T{ std::forward<Args>(args)... };
//	}
//
//	void release(T* ptr)
//	{
//		// If ptr maps to a valid index in the pool, 
//		//	destruct it then push it on to the free list
//
//		// store the address of the first index to the data array
//		// cast that 2 something      that something(data type is in the free function
//		// take pointer parameter and subtract it by the variable you casted 
//
//		T* firstUp = (T*)&sortedParticlePool[0];
//		auto differential = ptr - firstUp;
//
//		if (differential >= 0 && differential < N)
//		{
//			ptr->~T();
//			sortedParticlePool[differential] = sortedParticlePool[--particles];
//		}
//
//	}
//
//	int activeParticle()
//	{
//		return particles;
//	}
//	T& operator[](int k)
//	{
//		return (T&)sortedParticlePool[k];
//	}
//
//};

