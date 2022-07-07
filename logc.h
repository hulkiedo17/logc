#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define LOG_PATH "/var/log/logger.log"

#define RESET_COLOR "\x1B[0m"

#define PRINT_FORMAT_LOG(fp, fmt)	\
	va_list ap;	\
	va_start(ap, fmt);	\
	vfprintf(fp, fmt, ap);	\
	va_end(ap)

enum log_level
{
	LL_INFO,
	LL_ERROR,
	LL_WARNING,
	LL_DEBUG,
	LL_TRACE,
	LL_FATAL
};

void init_logger(const char *path, bool output_file);

void logger(enum log_level level, const char *filename, const size_t line, const char *fmt, ...);

#define log_info(...)		logger(LL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)		logger(LL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)	logger(LL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)		logger(LL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_trace(...)		logger(LL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...)		logger(LL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
