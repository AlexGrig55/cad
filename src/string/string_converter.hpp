#pragma once
#include <assert.h>
#include <string>


namespace cad
{
	class StringConverter
	{
	public:
		static constexpr size_t toId(const std::string_view& view)noexcept
		{
			size_t res = 0;

			for (uint32_t i =0,end=view.size();i<end;++i)
			{
				res += view[i]*(i+1)*100;
			}

			return res;
		}

		template <class T>
		static constexpr T convertToIntegral(const char* ptr, uint32_t count, uint32_t base = 10) noexcept
		{
			assert(std::is_integral<T>::value);
			T res;
			std::from_chars(ptr, ptr + count, res, base);
			return res;
		}

		template <class T>
		static constexpr T convertToIntegral(const std::string_view& strView, uint32_t base = 10) noexcept
		{
			return convertToIntegral<T>(strView.data(), strView.size(),base);
		}

		template <class T>
		static constexpr T convertToFloatPoint(const char* ptr, uint32_t count, std::chars_format format = std::chars_format::general) noexcept
		{
			assert(std::is_floating_point<T>::value);
			T res;
			std::from_chars(ptr, ptr + count, res, format);
			return res;
		}

		template <class T>
		static constexpr T convertToFloatPoint(const std::string_view& strView, std::chars_format format= std::chars_format::general) noexcept
		{
			return convertToFloatPoint<T>(strView.data(), strView.size(),format);
		}
	};
}