#pragma once
#include <vector>
#include <assert.h>
#include <type_traits>

namespace cad::util
{
	template <class T>
	class ConstContainer : protected std::vector<T>
	{
		typedef std::vector<T> vec;

	public:
		ConstContainer() = default;
		ConstContainer(std::initializer_list<T>&& list) :vec(list) {}


#pragma region getters_setters
		constexpr size_t count()const noexcept { return vec::size(); }

		constexpr auto data()noexcept { return vec::data(); }

		constexpr std::enable_if_t<std::is_pointer<T>::value, const T*> data()const noexcept { const T tmp = *vec::data(); return tmp; }

		constexpr std::enable_if_t<!std::is_pointer<T>::value, const T*> data()const noexcept { return vec::data(); }

		constexpr T* begin()noexcept { return vec::data(); }
		constexpr T* end()noexcept { return vec::data() + vec::size(); }
		constexpr const T* const begin()const noexcept { return vec::data(); }
		constexpr const T* const end() const noexcept { return vec::data() + vec::size(); }

		constexpr T& back() noexcept { return vec::back(); }
		constexpr T& front() noexcept { return vec::front(); }
		constexpr const T& back() const noexcept { return vec::back(); }
		constexpr const T& front() const noexcept { return vec::front(); }

		constexpr T& at(size_t i) { return vec::at(i); }
		constexpr const T& at(size_t i)const { return vec::at(i); }

		constexpr T& operator[](size_t i)noexcept { return vec::operator[](i); }
		constexpr const T& operator[](size_t i)const noexcept { return vec::operator[](i); }

#pragma endregion getters_setters
	};


	template <class T>
	class Container : public ConstContainer<T>
	{
		typedef std::vector<T> vec;

	public:
		Container() = default;
		Container(std::initializer_list<T>&& list) :vec(list) {}

		~Container() { this->clear(); }

#pragma region actions
		constexpr void add(const T& val) { vec::emplace_back(val); }
		constexpr void add(T&& val) { vec::emplace_back(std::move(val)); }
		constexpr void insert(size_t i, const T& val) { vec::emplace(vec::begin() + i, val); }
		constexpr void insert(size_t i, T&& val) { vec::emplace(vec::begin() + i, std::move(val)); }

		constexpr void remove(size_t i) { auto iter = vec::begin() + i; vec::erase(iter); }
		constexpr void remove(size_t start, size_t end) { 
			vec::erase(vec::begin() + start, vec::begin() + end);
		}
		constexpr void clear()noexcept { 
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