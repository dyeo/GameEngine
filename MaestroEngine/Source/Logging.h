#ifndef _MAESTRO_LOGGING_H_
#define _MAESTRO_LOGGING_H_

#ifdef _WIN32


#define _IMPL_LOG_MESSAGE(msg) \
	{ \
		SET_COLOR(7); printf("[DEBUG] %s\n", msg);  \
	}

#define _IMPL_LOG_WARNING(msg) \
	{ \
		SET_COLOR(14); printf("[WARNING] %s\n", msg); \
	}

#define _IMPL_LOG_ERROR(msg) \
	{ \
		SET_COLOR(12); printf("[ERROR] %s\n", msg); \
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

#define LOG_MESSAGE(msg) _IMPL_LOG_MESSAGE(msg)

#define LOG_WARNING(msg) _IMPL_LOG_WARNING(msg)

#define LOG_ERROR(msg) _IMPL_LOG_ERROR(msg)

#define SET_COLOR(color) _IMPL_SET_COLOR(color) // format is bg;fg. 7 = black; default 10 = black;green, 11 = black;cyan 12 = black;red 13 = black;magenta 14 = black;yellow 15 = black;white

#else

#define LOG_MESSAGE(msg) ((void)0)

#define LOG_WARNING(msg) ((void)0)

#define LOG_ERROR(msg) ((void)0)

#define SET_Color(color) ((void)0)

#endif

#endif // !_MAESTRO_LOGGING_H_
