/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:42:38 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:52:25 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <mach-o/stab.h>
# include <ar.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_mess.h"

# define PADDING_STR		"00000000"
# define PADDING_STR_64		"0000000000000000"
# define PADDING_SPACE_64	"                "
# define PADDING_SPACE		"        "
# define MIN_LOAD_SIZE		8
# define HELP_FLAG			-2
# define IS_OTOOL			1
# define IS_NM				0

# define BAD_STRING_INDEX	"bad index adresse"

typedef struct s_cmd_flag	t_cmd_flag;

struct						s_cmd_flag
{
	int						is_indian;
	int						is_otool;
	int						p;
	int						u;
	int						uu;
	int						g;
	int						j;
	int						r;
};

typedef struct s_seg_infos	t_seg_infos;

struct						s_seg_infos
{
	t_cmd_flag				*cmd_f;
	int						text_nsect;
	int						data_nsect;
	int						bss_nsect;
	void					*ptr;
	void					*ptr_end;
};

typedef struct s_fat_infos	t_fat_infos;

struct						s_fat_infos
{
	struct fat_header		*f_h;
	struct fat_arch			*f_a;
	int						nb_arch;
	int						offset;
	char					*s;
};

typedef struct s_load
{
	int						ncmds;
	int						sizeofcmds;
	int						is_indian;
	void					*ptr;
	void					*ptr_end;

} t_load;

typedef struct s_ptr
{
	char					*ptr;
	char					*ptr_end;
	int						is_indian;
	int						is_64;
} t_ptr;

uint32_t					swap_uint32_check(uint32_t val, int is_indian);
int							set_cmd_flag(
	int ac, char **av, t_cmd_flag *cmd_f, int is_otool);
int							print_outpout_format(
	struct nlist *nlist, char type, char *name, t_cmd_flag *cmd_flag);
int							print_outpout_format_64(
	struct nlist_64 *nlist, char type, char *name, t_cmd_flag *cmd_flag);
int							print_outpout(
	struct nlist *nlist, char *stringtable,
	t_seg_infos *seg_infos, t_cmd_flag *cmd_flag);
int							print_outpout_64(
	struct nlist_64 *nlist, char *stringtable,
	t_seg_infos *seg_infos, t_cmd_flag *cmd_flag);
struct nlist_64				**ft_copy_nlist64(
	struct nlist_64 *array, int nsyms);
struct nlist				**ft_copy_nlist(
	struct nlist *array, int nsyms);
int							ft_sort64(struct nlist_64 *array, int nsyms,
	char *stringtable, t_seg_infos *seg_infos);
int							ft_sort(
	struct nlist *array, int nsyms, char *stringtable, t_seg_infos *seg_infos);
int							sort_and_print_outpout(
	struct symtab_command *sym, void *ptr, void *ptr_end,
	t_seg_infos *seg_infos);
int							sort_and_print_outpout_64(
	struct symtab_command *sym, void *ptr, void *ptr_end,
	t_seg_infos *seg_infos);
void						ft_init_seg_infos(t_seg_infos *seg_infos);
t_seg_infos					*ft_infos_segment_64(char *ptr, char *ptr_end,
	struct mach_header_64 *header, struct load_command *lc);
t_seg_infos					*ft_infos_segment(char *ptr, char *ptr_end,
	struct mach_header *header, struct load_command *lc);
int							handle_64(
	char *ptr, char *ptr_end, t_cmd_flag *cmd_f);
int							handle(char *ptr, char *ptr_end, t_cmd_flag *cmd_f);
void						ft_print_adress(long double adr);
void						ft_get_adress_str(
	long double adr, char **dest, int index);
void						ft_print_padding_adresse(
	long int addr, size_t len_padding, char *padding);
int							print_text_text_section(
	void *ptr, long double addr, int size, t_ptr *ptr_infos);
struct section_64			*ft_find_section_64(
	struct segment_command_64 *segment, char *section_name, t_ptr *ptr_infos);
struct section				*ft_find_section(
	struct segment_command *segment, char *section_name, t_ptr *ptr_infos);
int							ft_check_load(
	struct load_command *lc, char *ptr_end, t_load *load);
struct segment_command_64	*ft_find_segment_64(
	struct load_command *lc, int ncmds, char *segment_name, t_ptr *ptr_infos);
struct segment_command		*ft_find_segment(
	struct load_command *lc, int ncmds, char *segment_name, t_ptr *ptr_infos);
struct section_64			*ft_find_segment_section_64(t_ptr *ptr_infos,
	int is_indian, char *segment_name, char *section_name);
struct section				*ft_find_segment_section(t_ptr *ptr_infos,
	int is_indian, char *segment_name, char *section_name);
int							handle_64_text(
	char *ptr, char *ptr_end, char *av, int is_indian);
int							handle_text(
	char *ptr, char *ptr_end, char *av, int is_indian);
char						*ft_format_archive_name(
	char *n1, char *n2, char *n3, char *n4);
void						ft_print_archive_name(char *s1, char *s2);
int							check_valid_file(char *ptr, char *ptr_end);
int							ft_ar_file(
	char *ptr, char *ptr_end, char *av, t_cmd_flag *cmd_f);
uint32_t					swap_uint32(uint32_t val);
int							ft_fat_file(
	char *ptr, char *ptr_end, char *av, t_cmd_flag *cmd_f);
int							ft_otool(
	char *ptr, char *ptr_end, char *av, t_cmd_flag *cmd_f);

#endif
