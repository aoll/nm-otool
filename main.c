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

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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
		simple = 65 + simple - 10;
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
	while (j < size)
	{
		if (j % 16 == 0)
		{
			ft_print_adress(addr);
			write(1, "    ", 4);
		}
		ft_print_adress(*(unsigned char *)ptr);
		write(1, "  ", 2);
		j++;
		if (j == 21)
		{
			write(1, "\n", 1);
			return (0);
		}
		if (j % 16 == 0)
		{
			write(1, "\n", 1);
		}
		addr++;
		ptr++;
 	}
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

	i = 0;
	while (i < ncmds)
	{
	  if (lc->cmd == LC_SEGMENT_64)
	  {
		  seg = (struct segment_command_64*)lc;
		  if (strcmp(seg->segname, segment_name) == 0)
		  {
			  return (seg);
		  }
	  }
	  lc = (void *)lc + lc->cmdsize;
	  i++;
	}
	return (NULL);
}

struct section_64 *ft_find_segment_section_64(
	char *ptr, struct mach_header_64 *header, char *segment_name, char *section_name)
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

int	handle_64_text(char *ptr)
{
	struct mach_header_64		*header;
	struct section_64			*section;

	header = (struct mach_header_64 *)ptr;
	if (!(section = ft_find_segment_section_64(ptr, header, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	print_text_text_section((void*)ptr + section->offset, section->addr, section->size);
	return (EXIT_SUCCESS);
}



int	nm(char *ptr)
{
	int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
	  //handle_64(ptr);
		handle_64_text(ptr);
	}
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
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
