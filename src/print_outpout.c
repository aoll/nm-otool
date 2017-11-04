/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outpout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	case_n_sect(struct nlist *nlist, t_seg_infos *seg_infos, char *type)
{
	if(nlist->n_sect == seg_infos->text_nsect)
		*type = 't';
	else if(nlist->n_sect == seg_infos->data_nsect)
		*type = 'd';
	else if(nlist->n_sect == seg_infos->bss_nsect)
		*type = 'b';
	else
		*type = 's';
	if (nlist->n_sect == seg_infos->bss_nsect)
	{
		*type = 'b';
	}
}

static void	case_n_undef(struct nlist *nlist, char *type)
{
	*type = 'u';
	if(nlist->n_value != 0)
		*type = 'c';
}

int			print_outpout(
	struct nlist *nlist, char *stringtable, t_seg_infos *seg_infos)
{
	char type;

	type = '?';
	int c = nlist->n_type & N_STAB;
	if ((nlist->n_type & N_STAB) != 0)
		return (EXIT_SUCCESS);
	c = nlist->n_type & N_TYPE;
	if (c == N_UNDF)
		case_n_undef(nlist, &type);
	else if (c == N_ABS)
		type = 'a';
	else if (c == N_SECT)
		case_n_sect(nlist, seg_infos, &type);
	else if (c == N_PBUD)
		type = 'u';
	else if (c ==  N_INDR)
		type = 'i';
	if((nlist->n_type & N_EXT) && type != '?')
		type = ft_toupper(type);
	print_outpout_format(nlist, type, stringtable + nlist->n_un.n_strx);
	return (EXIT_SUCCESS);
}
