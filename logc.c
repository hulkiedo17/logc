#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "logc.h"

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

	length = datetime - d_time;

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

void init_logger(const char *path, bool file)
{
	if(path != NULL)
		log_path = path;

	output_file = file;
}

void logger(enum log_level level, const char *filename, const size_t line, const char *fmt, ...)
{
	FILE* fp = stderr;

	if(output_file)
		fp = open_log_file();

	if(fp == stderr)
		fprintf(fp, "%s%-9s : ", colors[level], log_level_str[level]);
	else
		fprintf(fp, "%-9s : ", log_level_str[level]);

	log_time(fp);

	fprintf(fp, "[%s:%4zu] : ", filename, line);

	va_list ap;
	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	va_end(ap);

	if(fp == stderr)
		fprintf(fp, "%s\n", RESET_COLOR);
	else
		fprintf(fp, "\n");

	if(fp != stderr)
		fclose(fp);
}
