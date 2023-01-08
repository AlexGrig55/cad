#pragma once

#include <cstdint>
#include <assert.h>

#ifndef CAD_API
#if !defined(CAD_STATIC)&&(_WIN32 || _WIN64)
#ifdef CAD_EXPORT
#define CAD_API __declspec(dllexport)
#else
// F or clients of the library, supress warnings about DLL interfaces for standard library classes
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#define CAD_API __declspec(dllimport)
#endif
#else
#define CAD_API
#endif
#endif

namespace cad::util
{
	//code range: 0-9, 100, 102, 105, 300-369, 390-399, 410-419, 430-439, 470-481, 999, 1000-1009
	typedef char cad_char;

	//code range: 10-59, 110-149, 210-239, 460-469, 1010-1059
	typedef double cad_float;

	//code range: 60-79, 170-179, 270-289, 370-389, 400-409, 1060-1070
	typedef int16_t cad_int16;

	//code range: 90-99, 420-429, 440-449, 1071
	typedef int32_t cad_int32;

	//code range: 160-169
	typedef int64_t cad_int64;

	//code range: 290-299
	typedef bool cad_bool;

	//code range: 450-459
	typedef long cad_long;
}