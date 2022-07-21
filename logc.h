#ifndef LOGC_H
#define LOGC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __cplusplus
#include <stdbool.h>
#endif /* __cplusplus */

enum log_level
{
	LL_INFO,
	LL_ERROR,
	LL_WARNING,
	LL_DEBUG,
	LL_TRACE,
	LL_FATAL
};

/* 
   logger - generates log output to stream

   - log_level - specified the output log level
   - filename - specified the source filename
   - line - specified the line in source file
   - fmt, ... - variadic format arguments
 */
void logger(enum log_level level, const char *filename, const size_t line, const char *fmt, ...);

/*
   init_logger - initializes the path to output and file flag

   arguments:
   - path - path to the file where the logs will be output, if it's null, then LOG_PATH will be used.
   - output_file - if it's true, the output will be to a file, otherwise it will be to terminal.
 */
void init_logger(const char *path, bool output_file);

/*
   log_info, log_error, log_warning, log_debug, log_trace, log_fatal - default wrapped directives
   for logger function to use all log_level constants
 */
#define log_info(...)		logger(LL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)		logger(LL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)	logger(LL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)		logger(LL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_trace(...)		logger(LL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...)		logger(LL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LOGC_H */
