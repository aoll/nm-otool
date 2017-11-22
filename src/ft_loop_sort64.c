/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_sort64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:37:23 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 00:12:23 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	set_index64(
	struct nlist_64 **tmp, int *index, int i, struct nlist_64 **list)
{
	*tmp = list[i];
	*index = i;
}

int			loop_sort64(
	struct nlist_64 **list, int nsyms, char *stringtable,
	t_seg_infos *seg_infos)
{
	struct nlist_64		*tmp;
	int					i;
	int					cmp;
	int					index;

	tmp = NULL;
	index = 0;
	i = -1;
	while (++i < nsyms)
	{
		if (!tmp && list[i])
			set_index64(&tmp, &index, i, list);
		if (list[i] && tmp)
		{
			cmp = ft_strcmp(is_bad_adresse(
				stringtable, tmp->n_un.n_strx, seg_infos),
					is_bad_adresse(stringtable, list[i]->n_un.n_strx, seg_infos));
			if (cmp > 0)
				set_index64(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value > list[i]->n_value)
				set_index64(&tmp, &index, i, list);
		}
	}
	return (index);
}

int			loop_sort64_reverse(
	struct nlist_64 **list, int nsyms, char *s, t_seg_infos *seg_infos)
{
	struct nlist_64		*tmp;
	int					i;
	int					cmp;
	int					index;

	tmp = NULL;
	index = 0;
	i = -1;
	while (++i < nsyms)
	{
		cmp = 1;
		if (!tmp && list[i])
			set_index64(&tmp, &index, i, list);
		if (list[i])
		{
			cmp = ft_strcmp(is_bad_adresse(s, tmp->n_un.n_strx, seg_infos),
				is_bad_adresse(s, list[i]->n_un.n_strx, seg_infos));
			if (cmp < 0)
				set_index64(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value < list[i]->n_value)
				set_index64(&tmp, &index, i, list);
		}
	}
	return (index);
}
