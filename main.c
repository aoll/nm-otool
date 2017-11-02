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

int		ft_otool(char *ptr, char *ptr_end, char *av, int is_otool);
void	ft_print_padding_adresse(
	long int addr, size_t len_padding, char *padding);
int		ft_check_load(
	char *ptr, struct load_command *lc, int ncmds, int sizeofcmds);
struct segment_command_64 *ft_find_segment_64(
		char *ptr, struct load_command *lc, int ncmds, char *segment_name);

int	print_outpout_format(struct nlist *nlist, char type, char *name)
{
	if (nlist->n_value || type != 'U')
	{
		ft_print_padding_adresse(nlist->n_value, ft_strlen(PADDING_STR), PADDING_STR);
		// printf("%016llx",nlist->n_value);
	}
	else
	{
		write(1, PADDING_SPACE, ft_strlen(PADDING_SPACE));
	}
	write(1, " ", 1);
	write(1, &type, 1);
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int	print_outpout_format_64(struct nlist_64 *nlist, char type, char *name)
{
	if (nlist->n_value || type != 'U')
	{
		ft_print_padding_adresse(nlist->n_value, ft_strlen(PADDING_STR_64), PADDING_STR_64);
		// printf("%016llx",nlist->n_value);
	}
	else
	{
		write(1, PADDING_SPACE_64, ft_strlen(PADDING_SPACE_64));
	}
	write(1, " ", 1);
	write(1, &type, 1);
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int	print_outpout(struct nlist *nlist, char *stringtable, t_seg_infos *seg_infos)
{
	char type;
	type = '?';
	int c = nlist->n_type & N_STAB;
	if ((nlist->n_type & N_STAB) != 0)
	{
		return (EXIT_SUCCESS);
	}
	switch(nlist->n_type & N_TYPE) {
		case N_UNDF:
			type = 'u';
			if(nlist->n_value != 0)
				type = 'c';
			break;
		case N_ABS:  type = 'a'; break;
		case N_SECT:
			if(nlist->n_sect == seg_infos->text_nsect)
				type = 't';
			else if(nlist->n_sect == seg_infos->data_nsect)
				type = 'd';
			else if(nlist->n_sect == seg_infos->bss_nsect)
				type = 'b';
			else
				type = 's';
			if (nlist->n_sect == seg_infos->bss_nsect)
			{
				type = 'b';
			}
			break;
		case N_PBUD: type = 'u'; break;
		case N_INDR: type = 'i'; break;

		default:
			type = '?';
			break;
	}
	if((nlist->n_type & N_EXT) && type != '?')
		type = ft_toupper(type);
	print_outpout_format(nlist, type, stringtable + nlist->n_un.n_strx);
	return (EXIT_SUCCESS);
}

int	print_outpout_64(struct nlist_64 *nlist, char *stringtable, t_seg_infos *seg_infos)
{
	char type;
	type = '?';
	int c = nlist->n_type & N_STAB;
	if ((nlist->n_type & N_STAB) != 0)
	{
		return (EXIT_SUCCESS);
	}
	switch(nlist->n_type & N_TYPE) {
		case N_UNDF:
			type = 'u';
			if(nlist->n_value != 0)
				type = 'c';
			break;
		case N_ABS:  type = 'a'; break;
		case N_SECT:
			if(nlist->n_sect == seg_infos->text_nsect)
				type = 't';
			else if(nlist->n_sect == seg_infos->data_nsect)
				type = 'd';
			else if(nlist->n_sect == seg_infos->bss_nsect)
				type = 'b';
			else
				type = 's';
			if (nlist->n_sect == seg_infos->bss_nsect)
			{
				type = 'b';
			}
			break;
		case N_PBUD: type = 'u'; break;
		case N_INDR: type = 'i'; break;

		default:
			type = '?';
			break;
	}
	if((nlist->n_type & N_EXT) && type != '?')
		type = ft_toupper(type);
	print_outpout_format_64(nlist, type, stringtable + nlist->n_un.n_strx);
	return (EXIT_SUCCESS);
}

void	sort_ascii(t_sort **tmp, int nsyms)
{
	int		i;

	i = 0;
	while (i + 1 < nsyms)
	{
		if (ft_strcmp(tmp[i]->name, tmp[i + 1]->name) > 0)
		{
			t_sort *s;
			s = tmp[i];
			tmp[i] = tmp[i + 1];
			tmp[i + 1] = s;
			i = 0;
		}
		else
			i++;
	}
	return ;
}

int	 free_sort(t_sort **sort, int index)
{
	while (--index >= 0)
	{
		free(sort[index]->name);
		free(sort[index]);
	}
	return (EXIT_SUCCESS);
}

int	init_sort_64(t_sort **sort, struct nlist_64 *nlist, int nsyms, char *stringtable)
{
	int		i;
	int		index;
	char	*tmp;
	t_sort	*new;

	printf("NSYMS: %d\n", nsyms);
	i = 0;
	while (i < nsyms)
	{
		if (!(new = malloc(sizeof(t_sort))))
		{
			free_sort(sort, i);
			return (EXIT_FAILURE);
		}
		if (!(new->name = ft_strdup(stringtable + nlist[i].n_un.n_strx)))
		{
			free_sort(sort, i);
			return (EXIT_FAILURE);
		}
		new->index = i;
		sort[i] = new;
		i++;
	}
	printf("%s\n", "END STRDUP");
	return (EXIT_SUCCESS);
}

int	init_sort(t_sort **sort, struct nlist *nlist, int nsyms, char *stringtable)
{
	int		i;
	int		index;
	char	*tmp;
	t_sort	*new;

	i = 0;
	while (i < nsyms)
	{
		if (!(new = malloc(sizeof(t_sort))))
		{
			free_sort(sort, i);
			return (EXIT_FAILURE);
		}
		if (!(new->name = ft_strdup(stringtable + nlist[i].n_un.n_strx)))
		{
			free_sort(sort, i);
			return (EXIT_FAILURE);
		}
		new->index = i;
		sort[i] = new;
		i++;
	}
	return (EXIT_SUCCESS);
}

t_sort	**array_index_sorted(struct nlist *nlist, int nsyms, char *stringtable)
{
	t_sort					**sort;
	int						err;

	if (!(sort = malloc(sizeof(t_sort *) * nsyms)))
		return (NULL);
	if ((err = init_sort(sort, nlist, nsyms, stringtable)))
	{
		free(sort);
		return (NULL);
	}
	sort_ascii(sort, nsyms);
	return (sort);
}

t_sort	**array_index_sorted_64(struct nlist_64 *nlist, int nsyms, char *stringtable)
{
	t_sort					**sort;
	int						err;

	if (!(sort = malloc(sizeof(t_sort *) * nsyms)))
		return (NULL);
	if ((err = init_sort_64(sort, nlist, nsyms, stringtable)))
	{
		free(sort);
		return (NULL);
	}
	printf("%s\n", "BEGIN SORT");
	sort_ascii(sort, nsyms);
	printf("%s\n", "END SORT");
	return (sort);
}

struct nlist_64	**ft_copy_nlist64(struct nlist_64 *array, int nsyms)
{
	struct nlist_64	**list;
	struct nlist_64	*l;
	int				i;

	if (!(list = malloc(sizeof(struct nlist_64 *) * nsyms)))
		return (NULL);
	i = 0;
	while (i < nsyms)
	{
		if (!(l = malloc(sizeof(struct nlist_64))))
		{
			while (--i >= 0)
				free(list[i]);
			free(list);
			return (NULL);
		}
		l->n_type = array[i].n_type;
		l->n_sect = array[i].n_sect;
		l->n_value = array[i].n_value;
		l->n_un.n_strx = array[i].n_un.n_strx;
		list[i] = l;
		i++;
	}
	return (list);
}
struct nlist	**ft_copy_nlist(struct nlist *array, int nsyms)
{
	struct nlist	**list;
	struct nlist	*l;
	int				i;

	if (!(list = malloc(sizeof(struct nlist *) * nsyms)))
		return (NULL);
	i = 0;
	while (i < nsyms)
	{
		if (!(l = malloc(sizeof(struct nlist))))
		{
			while (--i >= 0)
				free(list[i]);
			free(list);
			return (NULL);
		}
		l->n_type = array[i].n_type;
		l->n_sect = array[i].n_sect;
		l->n_value = array[i].n_value;
		l->n_un.n_strx = array[i].n_un.n_strx;
		list[i] = l;
		i++;
	}
	return (list);
}

int	ft_sort64(struct nlist_64 *array, int nsyms, char *stringtable, t_seg_infos *seg_infos)
{
	struct nlist_64		**list;
	struct nlist_64		*tmp;
	int					i;
	int					j;
	int					index;
	int					cmp;

	if (!(list = ft_copy_nlist64(array, nsyms)))
		return (EXIT_SUCCESS);
	j = 0;
	i = 0;
	while (j < nsyms)
	{
		tmp = NULL;
		index = 0;
		i = 0;
		while (i < nsyms)
		{
			if (!tmp && list[i])
			{
				tmp = list[i];
				index = i;
			}
			if (list[i])
			{
				cmp = ft_strcmp(stringtable + tmp->n_un.n_strx, stringtable + list[i]->n_un.n_strx);
				if (cmp > 0)
				{
					tmp = list[i];
					index = i;
				}
				else if (!cmp && tmp->n_value > list[i]->n_value)
				{
					tmp = list[i];
					index = i;
				}
			}
			i++;
		}
		print_outpout_64(tmp, stringtable, seg_infos);
		free(list[index]);
		list[index] = NULL;
		j++;
	}
	free(list);
	return (EXIT_SUCCESS);
}

int	ft_sort(struct nlist *array, int nsyms, char *stringtable, t_seg_infos *seg_infos)
{
	struct nlist		**list;
	struct nlist		*tmp;
	int					i;
	int					j;
	int					index;
	int					cmp;

	if (!(list = ft_copy_nlist(array, nsyms)))
		return (EXIT_SUCCESS);
	j = 0;
	i = 0;
	while (j < nsyms)
	{
		tmp = NULL;
		index = 0;
		i = 0;
		while (i < nsyms)
		{
			if (!tmp && list[i])
			{
				tmp = list[i];
				index = i;
			}
			if (list[i])
			{
				cmp = ft_strcmp(stringtable + tmp->n_un.n_strx, stringtable + list[i]->n_un.n_strx);
				if (cmp > 0)
				{
					tmp = list[i];
					index = i;
				}
				else if (!cmp && tmp->n_value > list[i]->n_value)
				{
					tmp = list[i];
					index = i;
				}
			}
			i++;
		}
		print_outpout(tmp, stringtable, seg_infos);
		free(list[index]);
		list[index] = NULL;
		j++;
	}
	free(list);
	return (EXIT_SUCCESS);
}

int	sort_and_print_outpout(int nsyms, int symoff, int stroff, void *ptr, t_seg_infos *seg_infos)
{
	int					i;
	char				*stringtable;
	struct nlist		*array;
	t_sort				**sort;

	array = ptr + symoff;
	stringtable = ptr + stroff;
	ft_sort(array, nsyms, stringtable, seg_infos);
	return (0);//wazza
	if (!(sort = array_index_sorted(array, nsyms, stringtable)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < nsyms)
	{
		print_outpout(&array[sort[i]->index], stringtable, seg_infos);
		free(sort[i]->name);
		free(sort[i]);
		i++;
	}
	free(sort);
	return (EXIT_SUCCESS);
}

int	sort_and_print_outpout_64(int nsyms, int symoff, int stroff, void *ptr, t_seg_infos *seg_infos)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;
	t_sort				**sort;

	array = ptr + symoff;
	stringtable = ptr + stroff;
	ft_sort64(array, nsyms, stringtable, seg_infos);
	return (0);//wazza
	if (!(sort = array_index_sorted_64(array, nsyms, stringtable)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < nsyms)
	{
		print_outpout_64(&array[sort[i]->index], stringtable, seg_infos);
		free(sort[i]->name);
		free(sort[i]);
		i++;
	}
	free(sort);
	return (EXIT_SUCCESS);
}

void ft_init_seg_infos(t_seg_infos *seg_infos)
{
	seg_infos->text_nsect = NO_SECT;
	seg_infos->data_nsect = NO_SECT;
	seg_infos->bss_nsect = NO_SECT;
	return ;
}


t_seg_infos	*ft_infos_segment_64(char *ptr, char *ptr_end, struct mach_header_64 *header, struct load_command *lc)
{
	t_seg_infos					*seg_infos;
	struct segment_command_64	*segment;
	struct section_64			*section;
	int							loop;

	if (!(seg_infos = malloc(sizeof(t_seg_infos))))
		return (NULL);
	lc = (void *)ptr + sizeof(*header);
	if (ft_check_load(ptr, lc, header->ncmds, header->sizeofcmds))
		return (NULL);
	if (!(segment = ft_find_segment_64(ptr, lc, header->ncmds, SEG_DATA)))
	// if (!(segment = ft_find_segment_64(ptr, lc, header->ncmds, SEG_TEXT)))
		return (NULL);
	ft_init_seg_infos(seg_infos);
	int							i;

	i = 0;
	int index = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64*)lc;
			section = (void *)segment + sizeof(*segment);
			loop = 0;
			while (loop < segment->nsects)
			{
				if(ft_strcmp(section->sectname, SECT_TEXT) == 0)
					seg_infos->text_nsect = index + 1;
				else if(ft_strcmp(section->sectname, SECT_DATA) == 0)
					seg_infos->data_nsect = index + 1;
				else if(ft_strcmp(section->sectname, SECT_BSS) == 0)
					seg_infos->bss_nsect = index + 1;
				section = (void *)section + sizeof(*section);
				loop++;
				index++;
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg_infos);
}

t_seg_infos	*ft_infos_segment(char *ptr, char *ptr_end, struct mach_header *header, struct load_command *lc)
{
	t_seg_infos					*seg_infos;
	struct segment_command	*segment;
	struct section			*section;
	int							loop;
	int							i;

	if (!(seg_infos = malloc(sizeof(t_seg_infos))))
		return (NULL);
	lc = (void *)ptr + sizeof(*header);
	if (ft_check_load(ptr, lc, header->ncmds, header->sizeofcmds))
		return (NULL);
	ft_init_seg_infos(seg_infos);
	i = 0;
	int index = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command*)lc;
			section = (void *)segment + sizeof(*segment);
			loop = 0;
			while (loop < segment->nsects)
			{
				if(ft_strcmp(section->sectname, SECT_TEXT) == 0)
					seg_infos->text_nsect = index + 1;
				else if(ft_strcmp(section->sectname, SECT_DATA) == 0)
					seg_infos->data_nsect = index + 1;
				else if(ft_strcmp(section->sectname, SECT_BSS) == 0)
					seg_infos->bss_nsect = index + 1;
				section = (void *)section + sizeof(*section);
				loop++;
				index++;
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg_infos);
}

int	handle_64(char *ptr, char *ptr_end, char *av)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct segment_command_64   *seg;
	t_seg_infos					*seg_infos;

	if ((void *)(header = (struct mach_header_64 *)ptr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
		return (EXIT_FAILURE);
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	if (!(seg_infos = ft_infos_segment_64(ptr, ptr_end, header, lc)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			sort_and_print_outpout_64(sym->nsyms, sym->symoff, sym->stroff, ptr, seg_infos);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	free(seg_infos);
	return (EXIT_SUCCESS);
}

int	handle(char *ptr, char *ptr_end, char *av)
{
	int						ncmds;
	int						i;
	struct mach_header	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct segment_command   *seg;
	t_seg_infos					*seg_infos;

	if ((void *)(header = (struct mach_header *)ptr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
		return (EXIT_FAILURE);
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	if (!(seg_infos = ft_infos_segment(ptr, ptr_end, header, lc)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			sort_and_print_outpout(sym->nsyms, sym->symoff, sym->stroff, ptr, seg_infos);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	free(seg_infos);
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
	// write(1, "\t", 1);
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
		{
			ft_print_padding_adresse(
				addr, len, is64 ? PADDING_STR_64 : PADDING_STR);
			write(1, "\t", 1);
		}
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

int	handle_text(char *ptr, char *ptr_end, char *av)
{
	struct mach_header		*header;
	struct section			*section;

	if ((void *)(header = (struct mach_header *)ptr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
	{
		return (EXIT_FAILURE);
	}
	if (!(section = ft_find_segment_section(
		ptr, header, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	write(1, av, ft_strlen(av));
	write(1, ":\n", 2);
	print_text_text_section(
		(void*)ptr + section->offset, section->addr, section->size, 0);
	return (EXIT_SUCCESS);
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

int	check_valid_file(char *ptr, char *ptr_end)
{
	int magic_number;

	if (ptr >= ptr_end)
		return (EXIT_FAILURE);
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC || magic_number == MH_MAGIC_64)
	{
		return (EXIT_SUCCESS);
	}
	else if (magic_number == FAT_CIGAM)
	{
		return (EXIT_SUCCESS);
	}
	else if (!strncmp(ptr, ARMAG, SARMAG))
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_ar_file(char *ptr, char *ptr_end, char *av, int is_otool)
{
	struct ar_hdr	*ar;
	int				len;
	int				nb;
	char			*archive_name;

	if ((void *)
	(ar = (void *)ptr + SARMAG) + sizeof(struct ar_hdr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if (is_otool)
		ft_print_archive_name("Archive : ", av);
	if ((len = ft_atoi(ar->ar_size)) <= 0)
		return (EXIT_FAILURE);
	while ((char *)(ar = (void *)ar + sizeof(*ar) + len) < ptr_end)
	{
		if ((len = atoi(ar->ar_size)) <= 0)
			return (EXIT_FAILURE);
		nb = atoi(ar->ar_name + ft_strlen(AR_EFMT1));
		if (check_valid_file((void *)ar + nb + sizeof(*ar), ptr_end))
		{
			continue ;
		}
		if (!(archive_name = ft_format_archive_name(
			av, "(", (void *)ar + sizeof(*ar), ")")))
			return (EXIT_FAILURE);
		if (!is_otool)
		{
			write(1, "\n", 1);
			write(1, archive_name, ft_strlen(archive_name));
			write(1, ":\n", 2);
		}
		ft_otool((void *)ar + nb + sizeof(*ar), ptr_end, archive_name, is_otool);
		free(archive_name);
	}
	return (EXIT_SUCCESS);
}

uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}


int	ft_fat_file(char *ptr, char *ptr_end, char *av, int is_otool)
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
				return (ft_otool(ptr + offset, ptr_end, av, is_otool));
			}
		}
		f_a = (void *)f_a + sizeof(*f_a);
		nb_arch--;
	}
	return (EXIT_SUCCESS);
}

int	ft_otool(char *ptr, char *ptr_end, char *av, int is_otool)
{
	int magic_number;

	if (ptr >= ptr_end)
		return (EXIT_FAILURE);
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC)
	{
		if (is_otool)
			return (handle_text(ptr, ptr_end, av));
		else
			return (handle(ptr, ptr_end, av));
	}
	else if (magic_number == MH_MAGIC_64)
	{
		if (is_otool)
			return (handle_64_text(ptr, ptr_end, av));
		else
			return (handle_64(ptr, ptr_end, av));
	}
	else if (magic_number == FAT_CIGAM)
	{
		return (ft_fat_file(ptr, ptr_end, av, is_otool));
	}
	else if (!strncmp(ptr, ARMAG, SARMAG))
	{
		return (ft_ar_file(ptr, ptr_end, av, is_otool));
	}
	ft_putstr_fd(av, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(ERROR_FORMAT_FILE, STDERR);
	return (EXIT_FAILURE);
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
	ret = ft_otool(ptr, (void *)ptr + buf.st_size, av[1], 1);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (ret);
}
