#pragma once


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
