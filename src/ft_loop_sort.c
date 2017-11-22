/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:37:23 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 00:12:43 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	set_index(
	struct nlist **tmp, int *index, int i, struct nlist **list)
{
	*tmp = list[i];
	*index = i;
}

char		*is_bad_adresse(char *s, long offset, t_seg_infos *seg_infos)
{
	uint32_t off;

	off = swap_uint32_check(offset, seg_infos->cmd_f->is_indian);
	if ((void *)(s + off) >= (void *)seg_infos->ptr_end)
	{
		return (BAD_STRING_INDEX);
	}
	return ((s + off));
}

int			loop_sort(
	struct nlist **list, int nsyms, char *stringtable, t_seg_infos *seg_infos)
{
	struct nlist		*tmp;
	int					i;
	int					cmp;
	int					index;

	tmp = NULL;
	index = 0;
	i = -1;
	while (++i < nsyms)
	{
		if (!tmp && list[i])
			set_index(&tmp, &index, i, list);
		if (list[i] && tmp)
		{
			cmp = ft_strcmp(is_bad_adresse(stringtable, tmp->n_un.n_strx,
				seg_infos), is_bad_adresse(stringtable,
				list[i]->n_un.n_strx, seg_infos));
			if (cmp > 0)
				set_index(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value > list[i]->n_value)
				set_index(&tmp, &index, i, list);
		}
	}
	return (index);
}

int			loop_sort_reverse(
	struct nlist **list, int nsyms, char *s, t_seg_infos *seg_infos)
{
	struct nlist		*tmp;
	int					i;
	int					cmp;
	int					index;

	tmp = NULL;
	index = 0;
	i = -1;
	while (++i < nsyms)
	{
		if (!tmp && list[i])
			set_index(&tmp, &index, i, list);
		if (list[i])
		{
			cmp = ft_strcmp(is_bad_adresse(s, tmp->n_un.n_strx,
				seg_infos), is_bad_adresse(s, list[i]->n_un.n_strx,
					seg_infos));
			if (cmp < 0)
				set_index(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value < list[i]->n_value)
				set_index(&tmp, &index, i, list);
		}
	}
	return (index);
}
