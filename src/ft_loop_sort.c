/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:37:23 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/22 19:08:48 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	set_index(
	struct nlist **tmp, int *index, int i, struct nlist **list)
{
	*tmp = list[i];
	*index = i;
}

static char	*is_bad_adresse(char *s, long offset, void *ptr_end)
{
	if (offset < 0 || (void *)(s + offset) >= (void *)ptr_end)
	{
		return (BAD_STRING_INDEX);
	}
	return ((s + offset));
}

int			loop_sort(
	struct nlist **list, int nsyms, char *stringtable, void *ptr_end)
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
			cmp = ft_strcmp(is_bad_adresse(
				stringtable, tmp->n_un.n_strx, ptr_end),
				is_bad_adresse(stringtable, list[i]->n_un.n_strx, ptr_end));
			if (cmp > 0)
				set_index(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value > list[i]->n_value)
				set_index(&tmp, &index, i, list);
		}
	}
	return (index);
}

int			loop_sort_reverse(
	struct nlist **list, int nsyms, char *s, void *ptr_end)
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
		cmp = 1;
		if (!tmp && list[i])
			set_index(&tmp, &index, i, list);
		if (list[i])
		{
			cmp = ft_strcmp(is_bad_adresse(s, tmp->n_un.n_strx, ptr_end),
				is_bad_adresse(s, list[i]->n_un.n_strx, ptr_end));
			if (cmp < 0)
				set_index(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value < list[i]->n_value)
				set_index(&tmp, &index, i, list);
		}
	}
	return (index);
}
