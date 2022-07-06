#include <iostream>
#include <cstring>

#include "logc.h"

int main(int argc, char **argv)
{
	bool file_flag = false;

	if(argc >= 2 && strcmp(argv[1], "-f") == 0)
		file_flag = true;

	init_logger("test2.txt", file_flag);

	log_info("test1");
	log_error("test2");
	log_warning("test3");
	log_debug("test4");
	log_trace("test5");
	log_fatal("test6");

	return 0;
}
