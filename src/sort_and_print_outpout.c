/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_outpout.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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

