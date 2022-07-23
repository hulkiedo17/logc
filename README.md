# What is this?

This is a small and simple c logger library for C/C++.

You can see comments that describes the functions in library in logc.h file. Also you can see the options for build.sh script, just pass them -h option.

# How to compile

To compile library, you need to run build.sh, like this:

```sh
$ ./build.sh
```

# Usage

To using library in your projects, you need to include logc.h header file, and link your code like this:

```sh
$ gcc [files...] -llogc [options...]
```

Also, before starting usage macros, initialize the logger, by calling init_logger(). Then you can use macros. Below you can see small example:

```c
#include <stdio.h>
#include "logc.h"

int main(void)
{
	// NULL and true means that logger will be used default path to log file
	init_logger(NULL, true);

	log_debug("test log #1");

	log_warning("test log #2");
}
```

