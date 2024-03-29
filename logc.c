#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <time.h>
#include "logc.h"

#define LOG_PATH "/var/log/logger.log"

#define RESET_COLOR "\x1B[0m"

#define PRINT_FORMAT_LOG(fp, fmt)	\
	va_list ap;	\
	va_start(ap, fmt);	\
	vfprintf(fp, fmt, ap);	\
	va_end(ap)

static const char *log_path = LOG_PATH;
static bool output_file = false;

const char *colors[] = {
	"\x1B[37m",	// white
	"\x1B[31m",	// red
	"\x1B[33m",	// yellow
	"\x1B[34m",	// blue
	"\x1B[32m",	// green
	"\x1B[35m",	// magenta
};

const char *log_level_str[] = {
	"[INFO]",
	"[ERROR]",
	"[WARNING]",
	"[DEBUG]",
	"[TRACE]",
	"[FATAL]"
};

static FILE* open_log_file(void)
{
	FILE* fp = NULL;

	fp = fopen(log_path, "a");
	if(!fp)
	{
		fprintf(stderr, "%s%s : file not existing or permisson denied%s\n", colors[LL_ERROR], log_level_str[LL_ERROR], RESET_COLOR);
		exit(EXIT_FAILURE);
	}

	return fp;
}

static void log_time(FILE *fp)
{
	assert(fp != NULL);

	time_t t;
	struct tm *ltm = NULL;
	const char *d_time = NULL;
	const char *datetime = NULL;
	char *date = NULL;
	size_t length;
	
	t = time(NULL);
	ltm = localtime(&t);

	d_time = asctime(ltm);
	datetime = strchr(d_time, '\n');

	length = (size_t)(datetime - d_time);

	date = calloc(length + 1, sizeof(char));
	if(!date)
	{
		fprintf(stderr, "%s%s : allocation failed%s\n", colors[LL_ERROR], log_level_str[LL_ERROR], RESET_COLOR);
		exit(EXIT_FAILURE);
	}

	strncpy(date, d_time, length);

	fprintf(fp, "[%s] : ", date);

	free(date);
}

void init_logger(const char *path, bool file_flag)
{
	if(path != NULL)
		log_path = path;
	else
		log_path = LOG_PATH;

	output_file = file_flag;
}

void logger(enum log_level level, const char *filename, const size_t line, const char *fmt, ...)
{
	assert(fmt != NULL);

	FILE* fp = NULL;

	if(output_file)
		fp = open_log_file();
	else
		fp = stderr;

	if(fp == stderr)
		fprintf(fp, "%s%-9s : ", colors[level], log_level_str[level]);
	else
		fprintf(fp, "%-9s : ", log_level_str[level]);

	log_time(fp);

	fprintf(fp, "[%s:%4zu] : ", filename, line);

	PRINT_FORMAT_LOG(fp, fmt);

	if(fp == stderr)
		fprintf(fp, "%s\n", RESET_COLOR);
	else
		fprintf(fp, "\n");

	if(fp != stderr)
		fclose(fp);
}
