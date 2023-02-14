#pragma once
#include <vector>
#include <assert.h>

namespace cad::util
{
	template <class T>
	class ConstContainer : protected std::vector<T>
	{
		typedef std::vector<T> vec;

	public:
		ConstContainer() = default;
		ConstContainer(std::initializer_list<T>&& list) :vec(list) {}


#pragma region usings
		using vec::front;
		using vec::back;
		using vec::operator[];
		using vec::at;
		using vec::begin;
		using vec::end;
		using vec::data;
#pragma endregion usings


#pragma region getters_setters
		constexpr size_t count()const noexcept { return vec::size(); }
#pragma endregion getters_setters
	};


	template <class T>
	class Container : public ConstContainer<T>
	{
		typedef std::vector<T> vec;

	protected:
		virtual constexpr void actionBeforAdd(T& val){}
		virtual constexpr void actionBeforDel(T& val) {}

		constexpr void clear(bool callActionBeforDel) { 
			if (callActionBeforDel)
				this->clear();
			else
				vec::clear();
		}

	public:
		Container() = default;
		Container(std::initializer_list<T>&& list) :vec(list) {}

		~Container() { this->clear(); }

#pragma region actions
		constexpr void add(const T& val) { T tmp = val; actionBeforAdd(tmp); vec::emplace_back(std::move(tmp)); }
		constexpr void add(T&& val) { actionBeforAdd(val); vec::emplace_back(std::move(val)); }
		constexpr void insert(size_t i, const T& val) { T tmp = val; actionBeforAdd(tmp); vec::emplace(vec::begin() + i, std::move(tmp)); }
		constexpr void insert(size_t i, T&& val) { actionBeforAdd(val); vec::emplace(vec::begin() + i, std::move(val)); }

		constexpr void remove(size_t i) { auto iter = vec::begin() + i; actionBeforDel(*iter); vec::erase(iter); }
		constexpr void remove(size_t start, size_t end) { 
			for (auto i = vec::data() + start, c = i + end; i < c; i++)
				actionBeforDel(*i);
			vec::erase(vec::begin() + start, vec::begin() + end);
		}
		constexpr void clear() { 
			for (auto& i : *this)
				actionBeforDel(i);
			vec::clear();
		}

		constexpr void pop_front() { remove(0); }
		constexpr void pop_back() { remove(vec::size() - 1); }

		constexpr void reserve(size_t capacity) { vec::reserve(capacity); }
#pragma endregion actions
	};
//
//
//	template <class T>
//	class ContainerPtr: private std::vector<T*>
//	{
//		typedef std::vector<T*> vec;
//
//	public:
//		~ContainerPtr() { clear(); }
//
//#pragma region usings
//		using vec::reserve;
//		using vec::shrink_to_fit;
//		using vec::capacity;
//		using vec::data;
//		using vec::front;
//		using vec::back;
//		using vec::pop_back;
//		using vec::emplace_back;
//		using vec::operator[];
//		using vec::at;
//#pragma endregion usings
//
//
//#pragma region actions
//		void clear()					noexcept;
//		constexpr size_t count()		const noexcept	{ return vec::size(); }
//
//		constexpr T* const* begin()		const noexcept	{ return data(); }
//		constexpr T* const* end()		const noexcept	{ return data() + vec::size(); }
//		constexpr T** begin()			noexcept		{ return data(); }
//		constexpr T** end()				noexcept		{ return data() + vec::size(); }
//
//		constexpr void pop_front()		noexcept		{ vec::erase(vec::begin()); }
//
//		constexpr void erase(uint32_t startI, uint32_t endI)noexcept;
//		constexpr void erase(uint32_t index)noexcept;
//
//		constexpr void resize(size_t count)				{ vec::resize(count,nullptr); }
//#pragma endregion actions
//
//	};
//
//
//#pragma region realisation
//	template<class T>
//	inline void ContainerPtr<T>::clear()noexcept
//	{
//		for (auto& i : *this)
//			delete i;
//
//		vec::clear();
//	}
//
//
//	template<class T>
//	constexpr void ContainerPtr<T>::erase(uint32_t startI, uint32_t endI) noexcept
//	{
//		assert(startI< endI);
//		assert(endI <= vec::size());
//		auto ptr = vec::data();
//		for (uint32_t i = startI; i < endI; ++i)
//		{
//			delete *(ptr + i);
//		}
//
//		vec::erase(vec::begin()+ startI, vec::begin() + endI);
//	}
//
//	template<class T>
//	constexpr void ContainerPtr<T>::erase(uint32_t index) noexcept
//	{
//		assert(index <= vec::size());
//
//		delete *(vec::data() + index);
//
//		vec::erase(vec::begin() + index);
//	}
//
//
//#pragma endregion realisation
}