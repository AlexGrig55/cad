#pragma once
#include <vector>
#include <assert.h>

namespace cad::auxil
{
	template <class T>
	class Container: private std::vector<T*>
	{
		typedef std::vector<T*> vec;

	public:
		~Container() { clear(); }


#pragma region usings
		using vec::reserve;
		using vec::shrink_to_fit;
		using vec::capacity;
		using vec::data;
		using vec::front;
		using vec::back;
		using vec::pop_back;
		using vec::emplace_back;
		using vec::operator[];
		using vec::at;
#pragma endregion usings


#pragma region actions
		void clear()					noexcept;
		constexpr size_t count()		const noexcept	{ return vec::size(); }

		constexpr T* const* begin()		const noexcept	{ return data(); }
		constexpr T* const* end()		const noexcept	{ return data() + vec::size(); }
		constexpr T** begin()			noexcept		{ return data(); }
		constexpr T** end()				noexcept		{ return data() + vec::size(); }

		constexpr void pop_front()		noexcept		{ vec::erase(vec::begin()); }

		constexpr void erase(uint32_t startI, uint32_t endI)noexcept;
		constexpr void erase(uint32_t index)noexcept;

		constexpr void resize(size_t count)				{ vec::resize(count,nullptr); }
#pragma endregion actions

	};


#pragma region realisation
	template<class T>
	inline void Container<T>::clear()noexcept
	{
		for (auto& i : *this)
			delete i;

		vec::clear();
	}


	template<class T>
	constexpr void Container<T>::erase(uint32_t startI, uint32_t endI) noexcept
	{
		assert(startI< endI);
		assert(endI <= vec::size());
		auto ptr = vec::data();
		for (uint32_t i = startI; i < endI; ++i)
		{
			delete *(ptr + i);
		}

		vec::erase(vec::begin()+ startI, vec::begin() + endI);
	}

	template<class T>
	constexpr void Container<T>::erase(uint32_t index) noexcept
	{
		assert(index <= vec::size());

		delete *(vec::data() + index);

		vec::erase(vec::begin() + index);
	}


#pragma endregion realisation
}