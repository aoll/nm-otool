/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 10:39:43 by aollivie          #+#    #+#             */
/*   Updated: 2017/10/23 19:16:57 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	ft_otool(char *ptr, char *ptr_end, char *av);

int	print_outpout(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	 struct section_64  *seg;

	array = ptr + symoff;
	stringtable = ptr + stroff;

	for (i = 0; i < nsyms; i++) {

		/* Get name of symbol type */
		const char* type = NULL;
		switch(array[i].n_type & N_TYPE) {
			case N_UNDF: type = "U "; break;
			case N_ABS:  type = "A "; break;
			case N_SECT: type = "T "; break;

			default:
				fprintf(stderr, "Invalid symbol type: 0x%x\n", array[i].n_type & N_TYPE);
				return -1;
		}
		if (array[i].n_value)
			printf("%016llx %s %s\n",array[i].n_value ,type, stringtable + array[i].n_un.n_strx);
		else
		{
			printf("%s %s %s\n", "                " ,type, stringtable + array[i].n_un.n_strx);
		}
		// if (array[i].n_sect)
		// {
		// 	seg = ( struct section_64  *)(stringtable + array[i].n_un.n_strx);
		// 	printf("name section : %s\n", seg->segname);
		// }
	}
	return (EXIT_SUCCESS);
}

int	handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct segment_command_64   *seg;


	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	for (i = 0; i < ncmds; i++) {
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_outpout(sym->nsyms, sym->symoff, sym->stroff, ptr);

			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}

	return (EXIT_SUCCESS);
}

/*
** Print a pointeur adresse with hex'format
*/

static void				ft_print_adress(long double adr)
{
	long int	simple;
	long double	d;

	simple = adr / 16;
	d = adr / 16 - simple;
	if (simple > 0)
	{
		ft_print_adress(simple);
	}
	simple = d * 16;
	if (simple > 9)
	{
		simple = 97 + simple - 10;
	}
	else
	{
		simple += '0';
	}
	write(1, &simple, 1);
	return ;
}

void			ft_get_adress_str(long double adr, char **dest, int index)
{
	long int	simple;
	long double	d;
	char		*s;

	if (index < 0)
		return ;
	simple = adr / 16;
	d = adr / 16 - simple;
	if (simple > 0)
		ft_get_adress_str(simple, dest, index - 1);
	simple = d * 16;
	if (simple > 9)
	{
		simple = 97 + simple - 10;
	}
	else
	{
		simple += '0';
	}
	s = *dest;
	s[index] = (int)simple;
	return ;
}

void	ft_print_padding_adresse(
	long int addr, size_t len_padding, char *padding)
{
	char	*addr_str;

	addr_str = ft_strdup(padding);
	if (addr > 0)
		ft_get_adress_str(addr, &addr_str, len_padding - 1);
	write(1, addr_str, len_padding);
	write(1, "\t", 1);
	free(addr_str);
}


int print_text_text_section(void *ptr, long double addr, int size, int is64)
{
	size_t	len;
	int		a;
	int		j;

	j = 0;
	len = is64 ? ft_strlen(PADDING_STR_64) : ft_strlen(PADDING_STR);
	write(1, CONTENT_TEXT_TEXT, ft_strlen(CONTENT_TEXT_TEXT));
	while (j < size)
	{
		if (j % 16 == 0)
			ft_print_padding_adresse(
				addr, len, is64 ? PADDING_STR_64 : PADDING_STR);
		if (*(unsigned char *)ptr < 0x10)
			write(1, "0", 1);
		ft_print_adress(*(unsigned char *)ptr);
		write(1, " ", 1);
		j++;
		if (j % 16 == 0)
			write(1, "\n", 1);
		addr++;
		ptr++;
 	}
	if (j % 16 != 0)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

struct section_64 *ft_find_section_64(
	char *ptr, struct segment_command_64 *segment, char *section_name)
{
	struct section_64			*section;
	int							loop;

	loop = 0;
	section = (void *)segment + sizeof(*segment);
	while (loop < segment->nsects)
	{
		if (!ft_strcmp(section->sectname, section_name))
		{
			return (section);
		}
		section = (void *)section + sizeof(*section);
		loop++;
	}
	return (NULL);
}

struct section	*ft_find_section(
	char *ptr, struct segment_command *segment, char *section_name)
{
	struct section			*section;
	int							loop;

	loop = 0;
	section = (void *)segment + sizeof(*segment);
	while (loop < segment->nsects)
	{
		if (!ft_strcmp(section->sectname, section_name))
		{
			return (section);
		}
		section = (void *)section + sizeof(*section);
		loop++;
	}
	return (NULL);
}

int	ft_check_load(char *ptr, struct load_command *lc, int ncmds, int sizeofcmds)
{
	int							i;
	int							size;

	i = 0;
	size = 0;
	while (i < ncmds)
	{
		if (lc->cmdsize < MIN_LOAD_SIZE)
		{
			ft_putstr_fd(ERROR_LOAD_MIN_SIZE , STDERR);
			return (EXIT_FAILURE);
		}
		size += lc->cmdsize;
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	if (size != sizeofcmds)
	{
		ft_putstr_fd(ERROR_LOAD_SIZE , STDERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

struct segment_command_64 *ft_find_segment_64(
	char *ptr, struct load_command *lc, int ncmds, char *segment_name)
{
	struct segment_command_64	*seg;
	int							i;
	int							nb_seg;

	i = 0;
	nb_seg = 0;
	seg = NULL;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			if (ft_strcmp(seg->segname, segment_name) == 0 || ncmds == 1)
			{
				return (seg);
			}
			nb_seg++;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg);
}

struct segment_command *ft_find_segment(
	char *ptr, struct load_command *lc, int ncmds, char *segment_name)
{
	struct segment_command	*seg;
	int						i;
	int						nb_seg;

	seg = NULL;
	i = 0;
	nb_seg = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			if (ft_strcmp(seg->segname, segment_name) == 0 || ncmds == 1)
			{
				return (seg);
			}
			nb_seg++;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg);
}

struct section_64 *ft_find_segment_section_64(char *ptr,
	struct mach_header_64 *header, char *segment_name, char *section_name)
{
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*section;

	lc = (void *)ptr + sizeof(*header);
	if (ft_check_load(ptr, lc, header->ncmds, header->sizeofcmds))
		return (NULL);
	if (!(seg = ft_find_segment_64(ptr, lc, header->ncmds, segment_name)))
		return (NULL);
	if (!(section = ft_find_section_64(ptr, seg, section_name)))
		return (NULL);
	return (section);
}

struct section *ft_find_segment_section(char *ptr,
	struct mach_header *header, char *segment_name, char *section_name)
{
	struct load_command			*lc;
	struct segment_command	*seg;
	struct section			*section;

	lc = (void *)ptr + sizeof(*header);
	if (!(seg = ft_find_segment(ptr, lc, header->ncmds, segment_name)))
		return (NULL);
	if (!(section = ft_find_section(ptr, seg, section_name)))
		return (NULL);
	return (section);
}

int	handle_64_text(char *ptr, char *ptr_end, char *av)
{
	struct mach_header_64		*header;
	struct section_64			*section;

	if ((void *)ptr + sizeof(struct mach_header_64) > (void *)ptr_end)
	{
		return (EXIT_FAILURE);
	}
	header = (struct mach_header_64 *)ptr;
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
	{
		return (EXIT_FAILURE);
	}
	if (!(section = ft_find_segment_section_64(
		ptr, header, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	write(1, av, ft_strlen(av));
	write(1, ":\n", 2);
	print_text_text_section(
		(void*)ptr + section->offset, section->addr, section->size, 1);
	return (EXIT_SUCCESS);
}

int	handle_text(char *ptr, char *av)
{
	struct mach_header		*header;
	struct section			*section;

	header = (struct mach_header *)ptr;
	if (!(section = ft_find_segment_section(
		ptr, header, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	write(1, av, ft_strlen(av));
	write(1, ":\n", 2);
	print_text_text_section(
		(void*)ptr + section->offset, section->addr, section->size, 0);
	return (EXIT_SUCCESS);
}



int	ft_nm(char *ptr)
{
	int magic_number;

	magic_number = *(int *)ptr;
	// printf("magic_number: %d\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
		// write(1, "\n---\n", 6);
		// handle_64_text(ptr);
	}
	return (EXIT_SUCCESS);
}

int	ft_ranlib(char *ptr)
{
	struct ranlib* ranlib;
	// void *ranlib;

	ranlib = (void *)ptr + 88;
	printf("ran: %u\n", *(uint32_t *)ranlib);

	ranlib = (void *)ptr + 88 + sizeof(uint32_t);
	printf("off %d\n", ranlib[0].ran_off);
	return (0);
}

char	*ft_format_archive_name(char *n1, char *n2, char *n3, char *n4)
{
	char	*s;
	int		l1;
	int		l2;
	int		l3;

	l1 = ft_strlen(n1);
	l2 = ft_strlen(n2);
	l3 = ft_strlen(n3);
	if (!(s = malloc(sizeof(char) * l1 + l2 + l3 + ft_strlen(n4) + 1)))
	{
		return (NULL);
	}
	s[l1 + l2 + l3 + ft_strlen(n4)] = '\0';
	ft_strcpy(s, n1);
	ft_strcpy(s + l1, n2);
	ft_strcpy(s + l1 + l2, n3);
	ft_strcpy(s + l1 + l2 + l3, n4);
	return (s);

}

void ft_print_archive_name(char *s1, char *s2)
{
	write(1, s1, ft_strlen(s1));
	write(1, s2, ft_strlen(s2));
	write(1, "\n", 1);
}


int	ft_ar_file(char *ptr, char *ptr_end, char *av)
{
	struct ar_hdr	*ar;
	int				len;
	int				nb;
	char			*archive_name;

	if ((void *)
	(ar = (void *)ptr + SARMAG) + sizeof(struct ar_hdr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	ft_print_archive_name("Archive : ", av);
	if ((len = ft_atoi(ar->ar_size)) <= 0)
		return (EXIT_FAILURE);
	while ((char *)(ar = (void *)ar + sizeof(*ar) + len) < ptr_end)
	{
		if ((len = atoi(ar->ar_size)) <= 0)
			return (EXIT_FAILURE);
		nb = atoi(ar->ar_name + ft_strlen(AR_EFMT1));
		if (!(archive_name = ft_format_archive_name(
			av, "(", (void *)ar + sizeof(*ar), ")")))
			return (EXIT_FAILURE);
		ft_otool((void *)ar + nb + sizeof(*ar), ptr_end, archive_name);
		free(archive_name);
	}
	return (EXIT_SUCCESS);
}

uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}


int	ft_fat_file(char *ptr, char *ptr_end, char *av)
{
	struct fat_header	*f_h;
	struct fat_arch		*f_a;
	int					nb_arch;
	int					offset;

	f_h = (struct fat_header *)ptr;
	nb_arch = swap_uint32(f_h->nfat_arch);
	f_a = (void *)f_h + sizeof(*f_h);
	offset = 0;
	while (nb_arch)
	{
		if (swap_uint32(f_a->cputype) == CPU_TYPE_X86_64)
		{
			offset = swap_uint32(f_a->offset);
			if (offset >= 0)
			{
				return (ft_otool(ptr + offset, ptr_end, av));
			}
		}
		f_a = (void *)f_a + sizeof(*f_a);
		nb_arch--;
	}
	return (EXIT_SUCCESS);
}

int	ft_otool(char *ptr, char *ptr_end, char *av)
{
	int magic_number;

	// if (ptr >= ptr_end)
	// 	return (EXIT_FAILURE);
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC)
	{
		return (handle_text(ptr, av));
	}
	else if (magic_number == MH_MAGIC_64)
	{
		return (handle_64_text(ptr, ptr_end, av));
	}
	else if (magic_number == FAT_CIGAM)
	{
		return (ft_fat_file(ptr, ptr_end, av));
	}
	else if (!strncmp(ptr, ARMAG, SARMAG))
	{
		return (ft_ar_file(ptr, ptr_end, av));
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av) {
	int			fd;
	char		*ptr;
	struct stat	buf;
	int			ret;

	if (ac != 2)
	{
		fprintf(stderr, "%s\n", "Please give a arg.");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(
		0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	// ft_nm(ptr);
	ret = ft_otool(ptr, (void *)ptr + buf.st_size, av[1]);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (ret);
}
