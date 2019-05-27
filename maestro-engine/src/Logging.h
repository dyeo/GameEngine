#ifndef _MAESTRO_LOGGING_H_
#define _MAESTRO_LOGGING_H_

#include <stdio.h>

#ifdef _WIN32

	#define NOMINMAX
	#include <Windows.h>

	#define _IMPL_SET_COLOR(color) { HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hcon, color); }
	
	#define _IMPL_LOG_MESSAGE(msg) { _IMPL_SET_COLOR(7); printf("[LOG] %s\n", msg); }
	#define _IMPL_LOG_MESSAGE_FORMAT(...) { _IMPL_SET_COLOR(7); printf("[LOG] " __VA_ARGS__); printf("\n"); }
	
	#define _IMPL_LOG_WARNING(msg) { _IMPL_SET_COLOR(14); printf("[WRN] %s\n", msg); }
	#define _IMPL_LOG_WARNING_FORMAT(...) { _IMPL_SET_COLOR(14); printf("[WRN] " __VA_ARGS__); printf("\n"); }
	
	#define _IMPL_LOG_ERROR(msg) { _IMPL_SET_COLOR(12); printf("[ERR] %s\n", msg); }
	#define _IMPL_LOG_ERROR_FORMAT(...) { _IMPL_SET_COLOR(12); printf("[ERR] " __VA_ARGS__); printf("\n"); }

#elif __APPLE__

	#include "TargetConditionals.h"
	
	#ifdef TARGET_OS_MAC
	
	#define _IMPL_LOG_MESSAGE(msg) { printf("\033[1;37m[LOG] %s\033[0m\n", msg); }
	#define _IMPL_LOG_MESSAGE_FORMAT(...) { printf("\033[1;37m"); printf("[LOG] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#define _IMPL_LOG_WARNING(msg) { printf("\033[1;33m[WRN] %s\033[0m\n", msg); }
	#define _IMPL_LOG_WARNING_FORMAT(...) { printf("\033[1;33m"); printf("[WRN] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#define _IMPL_LOG_ERROR(msg) { printf("\033[1;31m[ERR] %s\033[0m\n", msg); }
	#define _IMPL_LOG_ERROR_FORMAT(...) { printf("\033[1;31m"); printf("[ERR] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#else
	#error "Unknown Apple platform"
	#endif

#elif __linux__

	#define _IMPL_LOG_MESSAGE(msg) { printf("\033[1;37m[LOG] %s\033[0m\n", msg); }
	#define _IMPL_LOG_MESSAGE_FORMAT(...) { printf("\033[1;37m"); printf("[LOG] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#define _IMPL_LOG_WARNING(msg) { printf("\033[1;33m[WRN] %s\033[0m\n", msg); }
	#define _IMPL_LOG_WARNING_FORMAT(...) { printf("\033[1;33m"); printf("[WRN] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#define _IMPL_LOG_ERROR(msg) { printf("\033[1;31m[ERR] %s\033[0m\n", msg); }
	#define _IMPL_LOG_ERROR_FORMAT(...) { printf("\033[1;31m"); printf("[ERR] " __VA_ARGS__); printf("\033[0m\n"); }

#elif __unix__ // all unices not caught above

	#define _IMPL_LOG_MESSAGE(msg) { printf("\033[1;37m[LOG] %s\033[0m\n", msg); }
	#define _IMPL_LOG_MESSAGE_FORMAT(...) { printf("\033[1;37m"); printf("[LOG] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#define _IMPL_LOG_WARNING(msg) { printf("\033[1;33m[WRN] %s\033[0m\n", msg); }
	#define _IMPL_LOG_WARNING_FORMAT(...) { printf("\033[1;33m"); printf("[WRN] " __VA_ARGS__); printf("\033[0m\n"); }
	
	#define _IMPL_LOG_ERROR(msg) { printf("\033[1;31m[ERR] %s\033[0m\n", msg); }
	#define _IMPL_LOG_ERROR_FORMAT(...) { printf("\033[1;31m"); printf("[ERR] " __VA_ARGS__); printf("\033[0m\n"); }

#elif defined(_POSIX_VERSION)

#else

#error "Unknown compiler"

#endif

#ifdef MAESTRO_DEBUG

	#define LOG_MESSAGE(msg) _IMPL_LOG_MESSAGE(msg)
	#define LOG_MESSAGE_FORMAT(...) _IMPL_LOG_MESSAGE_FORMAT(__VA_ARGS__)
	
	#define LOG_WARNING(msg) _IMPL_LOG_WARNING(msg)
	#define LOG_WARNING_FORMAT(...) _IMPL_LOG_WARNING_FORMAT(__VA_ARGS__)
	
	#define LOG_ERROR(msg) _IMPL_LOG_ERROR(msg)
	#define LOG_ERROR_FORMAT(...) _IMPL_LOG_ERROR_FORMAT(__VA_ARGS__)

#else

	#define LOG_MESSAGE(msg) ((void)0)
	#define LOG_MESSAGE_FORMAT(...) ((void)0)
	
	#define LOG_WARNING(msg) ((void)0)
	#define LOG_WARNING_FORMAT(...) ((void)0)
	
	#define LOG_ERROR(msg) ((void)0)
	#define LOG_ERROR_FORMAT(...) ((void)0)

#endif

#endif // !_MAESTRO_LOGGING_H_
