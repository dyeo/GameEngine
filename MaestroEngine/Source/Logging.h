#ifndef _MAESTRO_LOGGING_H_
#define _MAESTRO_LOGGING_H_

#ifdef _WIN32

#define FOREGROUND_WHITE 0x7
#define FOREGROUND_YELLOW 0x6

#define _IMPL_LOG_MESSAGE(msg) \
	{ \
		printf("[DEBUG] %s\n", msg); \
	}

#define _IMPL_LOG_WARNING(msg) \
	{ \
		printf("[WARNING] %s\n", msg); \
	}

#define _IMPL_LOG_ERROR(msg) \
	{ \
		printf("[ERROR] %s\n", msg); \
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

#define LOG_WARNING(msg) _IMPL_LOG_MESSAGE(msg)

#define LOG_ERROR(msg) _IMPL_LOG_MESSAGE(msg)

#else

#define LOG_MESSAGE(msg) ((void)0)

#define LOG_WARNING(msg) ((void)0)

#define LOG_ERROR(msg) ((void)0)

#endif

#endif // !_MAESTRO_LOGGING_H_
