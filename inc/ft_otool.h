#ifndef FT_OTOOL_H
#define FT_OTOOL_H

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach-o/ranlib.h>
#include <mach-o/stab.h>
#include <ar.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

#define CONTENT_TEXT_TEXT 	"Contents of (__TEXT,__text) section\n"
#define PADDING_STR			"00000000"
#define PADDING_STR_64		"0000000000000000"
#define PADDING_SPACE_64	"                "
#define PADDING_SPACE		"        "
#define MIN_LOAD_SIZE		8
#define ERROR_LOAD_MIN_SIZE	"Mach-O load command with size < 8 bytes\n"
#define ERROR_LOAD_SIZE		"Mach-O segment load command size is too small\n"
#define ERROR_FORMAT_FILE	"The file was not recognized as a valid object file\n"

typedef struct s_seg_infos	t_seg_infos;

struct s_seg_infos
{
	int		text_nsect;
	int		data_nsect;
	int		bss_nsect;
};

typedef struct s_sort		t_sort;

struct s_sort
{
	char	*name;
	int		index;
};

int							print_outpout_format(struct nlist *nlist, char type, char *name);
int							print_outpout_format_64(struct nlist_64 *nlist, char type, char *name);
int							print_outpout(struct nlist *nlist, char *stringtable, t_seg_infos *seg_infos);
int							print_outpout_64(struct nlist_64 *nlist, char *stringtable, t_seg_infos *seg_infos);
void						sort_ascii(t_sort **tmp, int nsyms);
int							free_sort(t_sort **sort, int index);
// int							init_sort_64(t_sort **sort, struct nlist_64 *nlist, int nsyms, char *stringtable);
// int							init_sort(t_sort **sort, struct nlist *nlist, int nsyms, char *stringtable);
t_sort						**array_index_sorted(struct nlist *nlist, int nsyms, char *stringtable);
t_sort						**array_index_sorted_64(struct nlist_64 *nlist, int nsyms, char *stringtable);
struct nlist_64				**ft_copy_nlist64(struct nlist_64 *array, int nsyms);
struct nlist				**ft_copy_nlist(struct nlist *array, int nsyms);
int							ft_sort64(struct nlist_64 *array, int nsyms, char *stringtable, t_seg_infos *seg_infos);
int							ft_sort(struct nlist *array, int nsyms, char *stringtable, t_seg_infos *seg_infos);
int							sort_and_print_outpout(struct symtab_command *sym, void *ptr, t_seg_infos *seg_infos);
int							sort_and_print_outpout_64(struct symtab_command *sym, void *ptr, t_seg_infos *seg_infos);
void						ft_init_seg_infos(t_seg_infos *seg_infos);
t_seg_infos					*ft_infos_segment_64(char *ptr, char *ptr_end, struct mach_header_64 *header, struct load_command *lc);
t_seg_infos					*ft_infos_segment(char *ptr, char *ptr_end, struct mach_header *header, struct load_command *lc);
int							handle_64(char *ptr, char *ptr_end, char *av);
int							handle(char *ptr, char *ptr_end, char *av);
void						ft_print_adress(long double adr);
void						ft_get_adress_str(long double adr, char **dest, int index);
void						ft_print_padding_adresse(long int addr, size_t len_padding, char *padding);
int							print_text_text_section(void *ptr, long double addr, int size, int is64);
struct section_64			*ft_find_section_64(char *ptr, struct segment_command_64 *segment, char *section_name);
struct section				*ft_find_section(char *ptr, struct segment_command *segment, char *section_name);
int							ft_check_load(char *ptr, struct load_command *lc, int ncmds, int sizeofcmds);
struct segment_command_64	*ft_find_segment_64(char *ptr, struct load_command *lc, int ncmds, char *segment_name);
struct segment_command		*ft_find_segment(char *ptr, struct load_command *lc, int ncmds, char *segment_name);
struct section_64			*ft_find_segment_section_64(char *ptr, struct mach_header_64 *header, char *segment_name, char *section_name);
struct section				*ft_find_segment_section(char *ptr, struct mach_header *header, char *segment_name, char *section_name);
int							handle_64_text(char *ptr, char *ptr_end, char *av);
int							handle_text(char *ptr, char *ptr_end, char *av);
char						*ft_format_archive_name(char *n1, char *n2, char *n3, char *n4);
void						ft_print_archive_name(char *s1, char *s2);
int							check_valid_file(char *ptr, char *ptr_end);
int							ft_ar_file(char *ptr, char *ptr_end, char *av, int is_otool);
uint32_t					swap_uint32(uint32_t val);
int							ft_fat_file(char *ptr, char *ptr_end, char *av, int is_otool);
int							ft_otool(char *ptr, char *ptr_end, char *av, int is_otool);

#endif
