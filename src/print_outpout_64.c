/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outpout_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	print_outpout_64(struct nlist_64 *nlist, char *stringtable, t_seg_infos *seg_infos)
{
	char type;
	type = '?';
	int c = nlist->n_type & N_STAB;
	if ((nlist->n_type & N_STAB) != 0)
	{
		return (EXIT_SUCCESS);
	}
	c = nlist->n_type & N_TYPE;
	if (c == N_UNDF)
	{
		type = 'u';
		if(nlist->n_value != 0)
			type = 'c';
	}
	else if (c == N_ABS)
	{
		type = 'a';
	}
	else if (c == N_SECT)
	{
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
	}
	else if (c == N_PBUD)
	{
		type = 'u';
	}
	else if (c ==  N_INDR)
	{
		type = 'i';
	}
	if((nlist->n_type & N_EXT) && type != '?')
		type = ft_toupper(type);
	print_outpout_format_64(nlist, type, stringtable + nlist->n_un.n_strx);
	return (EXIT_SUCCESS);
}
