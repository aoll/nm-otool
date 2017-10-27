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

int print_text_text_section(void *ptr, long double addr, int size)
{
	size_t len;
	int a;
	int j = 0;
	void *tmp;

	tmp = ptr;
	write(1, CONTENT_TEXT_TEXT, strlen(CONTENT_TEXT_TEXT));
	while (j < size)
	{
		if (j % 16 == 0)
		{
			write(1, "0000000", 7);
			ft_print_adress(addr);
			write(1, "\t", 1);
		}
		if (*(unsigned char *)ptr < 0x10)
		{
			write(1, "0", 1);
		}
		ft_print_adress(*(unsigned char *)ptr);
		write(1, " ", 1);
		j++;
		if (j % 16 == 0)
		{
			write(1, "\n", 1);
		}
		addr++;
		ptr++;
 	}
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
		if (!strcmp(section->sectname, section_name))
		{
			return (section);
		}
		section = (void *)section + sizeof(*section);
		loop++;
	}
	return (NULL);
}

struct segment_command_64 *ft_find_segment_64(
	char *ptr, struct load_command *lc, int ncmds, char *segment_name)
{
	struct segment_command_64	*seg;
	int							i;
	int							nb_seg;

	i = 0;
	nb_seg = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			if (strcmp(seg->segname, segment_name) == 0 || ncmds == 1)
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
	if (!(seg = ft_find_segment_64(ptr, lc, header->ncmds, segment_name)))
		return (NULL);
	if (!(section = ft_find_section_64(ptr, seg, section_name)))
		return (NULL);
	return (section);
}

int	handle_64_text(char *ptr, char *av)
{
	struct mach_header_64		*header;
	struct section_64			*section;

	header = (struct mach_header_64 *)ptr;
	printf("cmds : %d\n", header->ncmds);
	if (!(section = ft_find_segment_section_64(
		ptr, header, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	write(1, av, strlen(av));
	write(1, ":\n", 2);
	print_text_text_section(
		(void*)ptr + section->offset, section->addr, section->size);
	return (EXIT_SUCCESS);
}



int	ft_nm(char *ptr)
{
	int magic_number;

	magic_number = *(int *)ptr;
	printf("magic_number: %d\n", magic_number);
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
		// write(1, "\n---\n", 6);
		// handle_64_text(ptr);
	}
	return (EXIT_SUCCESS);
}

int	ft_otool(char *ptr, char *av)
{
	int magic_number;

	magic_number = *(int *)ptr;
	// printf("magic_number: %x\n", magic_number);
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64_text(ptr, av);
	}

	// ptr += 200;

	printf("%s\n", (void *)ptr + 180);

	struct mach_header_64 *ht;

	ht = (void *)ptr + 200;

	printf("ptr : %d\n", ht->ncmds);
	return (0);
	struct ar_hdr	*ar;

	ar = (void *)ptr + SARMAG;

	write(1,ar->ar_name, 16 );
	write(1,"\n", 1);
	write(1,ar->ar_size, 10 );
	write(1,"\n", 1);

	// printf("fh : %s\n", ar->ar_name );
	// printf("fh : %s\n", ar->ar_size );

	struct	ranlib *ran;

	ran = (void*)ptr + sizeof(*ar) + SARMAG + 1812;


	//
	// h = ((void *)ptr +sizeof(struct	ranlib) + 100644);
	// printf("h : %d\n", h->ncmds);
	// ran = (struct	ranlib *) ((void *)ptr + sizeof(struct ar_hdr *));
	printf("%u\n", ran[0].ran_off);
	printf("%u\n", ran[1].ran_off);

	// printf("%u\n", ran[0].ran_un.ran_strx);
	// printf("%s\n", (void *)ptr + ran->ran_un.ran_strx);

	// printf("%s\n", (void *)ptr + ran->ran_off);
	// h = (struct mach_header_64 *)(void *)ptr + ran->ran_off;
	// printf("%s\n", ran->ran_un.ran_name);
	// struct mach_header_64		*header;
	// header = (struct mach_header_64 *)ptr;
	// printf("cmds : %d\n", h->ncmds);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av) {
	int			fd;
	char		*ptr;
	struct stat	buf;

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
	ft_otool(ptr, av[1]);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
