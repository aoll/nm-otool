/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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

