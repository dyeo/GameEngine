#ifndef _MAESTRO_LOGGING_H_
#define _MAESTRO_LOGGING_H_

#ifdef _WIN32

#define NOMINMAX
#include <Windows.h>

#define _IMPL_LOG_MESSAGE(...) \
	{ \
		SET_COLOR(7); printf("[DEBUG] " __VA_ARGS__ ); std::cout <<"\n";\
	}

#define _IMPL_LOG_WARNING(...) \
	{ \
		SET_COLOR(14); printf("[WARNING] " __VA_ARGS__ ); std::cout <<"\n"; \
	}

#define _IMPL_LOG_ERROR(...) \
	{ \
		SET_COLOR(12); printf("[ERROR] " __VA_ARGS__ ); std::cout <<"\n"; \
	}

#define _IMPL_SET_COLOR(color) \
{ \
HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE); \
SetConsoleTextAttribute(hcon, color);\
}

#elif __APPLE__

#include "TargetConditionals.h"

#ifdef TARGET_OS_MAC

#define _IMPL_LOG_MESSAGE(msg) { printf("\033[1;37m[DEBUG] %s\033[0m\n", msg); }

#define _IMPL_LOG_WARNING(msg) { printf("\033[1;33m[WARNING] %s\033[0m\n", msg); }

#define _IMPL_LOG_ERROR(msg) { printf("\033[1;31m[WARNING] %s\033[0m\n", msg); }

#else
#error "Unknown Apple platform"
#endif

#elif __linux__

#define _IMPL_LOG_MESSAGE(msg) { printf("\033[1;37m[DEBUG] %s\033[0m\n", msg); }

#define _IMPL_LOG_WARNING(msg) { printf("\033[1;33m[WARNING] %s\033[0m\n", msg); }

#define _IMPL_LOG_ERROR(msg) { printf("\033[1;31m[WARNING] %s\033[0m\n", msg); }

#elif __unix__ // all unices not caught above

#define _IMPL_LOG_MESSAGE(msg) { printf("\033[1;37m[DEBUG] %s\033[0m\n", msg); }

#define _IMPL_LOG_WARNING(msg) { printf("\033[1;33m[WARNING] %s\033[0m\n", msg); }

#define _IMPL_LOG_ERROR(msg) { printf("\033[1;31m[WARNING] %s\033[0m\n", msg); }

#elif defined(_POSIX_VERSION)

#else

#error "Unknown compiler"

#endif

#ifdef MAESTRO_DEBUG

#define LOG_MESSAGE(...) _IMPL_LOG_MESSAGE(__VA_ARGS__)

#define LOG_WARNING(...) _IMPL_LOG_WARNING(__VA_ARGS__)

#define LOG_ERROR(...) _IMPL_LOG_ERROR(__VA_ARGS__)

#define SET_COLOR(color) _IMPL_SET_COLOR(color) // format is bg;fg. 7 = black; default 10 = black;green, 11 = black;cyan 12 = black;red 13 = black;magenta 14 = black;yellow 15 = black;white

#else

#define LOG_MESSAGE(...) ((void)0)

#define LOG_WARNING(...) ((void)0)

#define LOG_ERROR(...) ((void)0)

#define SET_Color(color) ((void)0)

#endif

#endif // !_MAESTRO_LOGGING_H_
