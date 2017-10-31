#ifndef FT_OTOOL_H
#define FT_OTOOL_H

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach-o/ranlib.h>
#include <ar.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#define CONTENT_TEXT_TEXT "Contents of (__TEXT,__text) section\n"
#define PADDING_STR "0000000000000000"
#endif
