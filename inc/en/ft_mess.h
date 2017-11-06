#ifndef FT_MESS_H
#define FT_MESS_H


#define CONTENT_TEXT_TEXT 	"Contents of (__TEXT,__text) section\n"
#define ERROR_LOAD_MIN_SIZE	"Mach-O load command with size < 8 bytes\n"
#define ERROR_LOAD_SIZE		"Mach-O segment load command size is too small\n"
#define ERROR_FORMAT_FILE	"The file was not recognized \
as a valid object file\n"
#define NO_ACCESS			"No access to : "
#define ERROR_FLAG			"ft_nm: Unknown command line argument"
#define TYPE_HELP			"Type './ft_nm -help' for more informations\n"
#define HELP				"-help"
#define HELP_MESS			"USAGE: nm [options] <input files>\n\n\
General options:\n\n\
-g     Display only global (external) symbols\n\n\
-u     Display only undefined symbols\n\n\
-U     Don't display undefined symbols\n\n\
-a     Display all symbol table entries, including those  inserted  for\
use by debuggers\n\n\
-j     Just display the symbol names (no value or type)\n\n"

#endif
