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
			printf("%s %s %s\n","                " ,type, stringtable + array[i].n_un.n_strx);
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

int	handle_64_text(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct segment_command_64   *seg;
	struct section_64 *section;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	// printf("%s\n", SEG_TEXT);
	for (i = 0; i < ncmds; i++) {
	//  printf("cmd: %u%c",lc->cmd, 10);
	  if (lc->cmd == LC_SEGMENT_64)
	  {

	       seg = (struct segment_command_64*)lc;
				//  printf("%s\n", seg->segname);
	       if (strcmp(seg->segname,SEG_TEXT) == 0)
				 {
					 printf("nb section %d\n", seg->nsects);
					 section = (void *)seg + sizeof(*seg);
					 printf("section name: %s\n", section->sectname);
					 printf("section addr: %016llx\n", section->addr);
					 printf("section value: %s\n", ((void*)ptr + section->offset));
					 printf("section value: %s\n", (char *)seg->vmaddr);

					 section = (void *)section + section->size;
					 printf("section name 2: %s\n", section->sectname);
					 printf("section addr 2: %016llx\n", section->addr);
					 printf("section value 2: %s\n", ((void*)ptr + section->offset));
				 }

	  }

      	lc = (void *)lc + lc->cmdsize;

	}

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
	printf("%d\n", magic_number);
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
