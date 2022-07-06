#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include "logc.h"

int main(int argc, char **argv)
{
	bool file_flag = false;

	if(argc >= 2 && strcmp(argv[1], "-f") == 0)
		file_flag = true;

	init_logger("test.txt", file_flag);

	log_info("test log info");
	log_error("test log error");
	log_warning("test log warning");
	log_debug("test log debug");
	log_trace("test log trace");
	log_fatal("test log fatal");

	return 0;
}
