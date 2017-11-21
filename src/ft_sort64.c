/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:40 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:37:50 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	set_index64(
	struct nlist_64 **tmp, int *index, int i, struct nlist_64 **list)
{
	*tmp = list[i];
	*index = i;
}

static char		*is_bad_adresse(char *s, int offset)
{
	if (offset < 0)
	{
		return (BAD_STRING_INDEX);
	}
	return (s + offset);
}

static int		loop_sort64(
	struct nlist_64 **list, int nsyms, char *stringtable, void *ptr_end)
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
		if (list[i])
		{
			if ((void *)(stringtable + tmp->n_un.n_strx) > ptr_end)
			{
				tmp->n_value = (size_t)(stringtable + tmp->n_un.n_strx);
				printf("tp: %llu\n", tmp->n_value);
				tmp->n_un.n_strx = -1;
			}
			if ((void *)(stringtable + list[i]->n_un.n_strx) > ptr_end)
			{
				list[i]->n_value = (size_t)(stringtable + list[i]->n_un.n_strx);
				printf("li: %llu\n", list[i]->n_value);
				list[i]->n_un.n_strx = -1;
			}
			cmp = ft_strcmp(is_bad_adresse(stringtable, tmp->n_un.n_strx),
				is_bad_adresse(stringtable, list[i]->n_un.n_strx));
			if (cmp > 0)
				set_index64(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value > list[i]->n_value)
				set_index64(&tmp, &index, i, list);
		}
	}
	return (index);
}

static int	loop_sort64_reverse(
	struct nlist_64 **list, int nsyms, char *s, void *ptr_end)
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
			if ((void *)(s + tmp->n_un.n_strx) > ptr_end)
			{
				list[i]->n_un.n_strx = -1;
				return (i);
			}
			if ((void *)(s + list[i]->n_un.n_strx) > ptr_end)
			{
				list[i]->n_un.n_strx = -1;
				return (i);
			}
			cmp = ft_strcmp(s + tmp->n_un.n_strx,
				s + list[i]->n_un.n_strx);
			if (cmp < 0)
				set_index64(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value < list[i]->n_value)
				set_index64(&tmp, &index, i, list);
		}
	}
	return (index);
}

int			ft_sort64(
	struct nlist_64 *array, int nsyms,
	char *stringtable, t_seg_infos *seg_infos)
{
	struct nlist_64		**list;
	int					j;
	int					index;

	if (!(list = ft_copy_nlist64(array, nsyms)))
		return (EXIT_FAILURE);
	j = -1;
	while (++j < nsyms)
	{
		if (seg_infos->cmd_f->p)
			index = j;
		else if (seg_infos->cmd_f->r)
			index = loop_sort64_reverse(
				list, nsyms, stringtable, seg_infos->ptr_end);
		else
			index = loop_sort64(list, nsyms, stringtable, seg_infos->ptr_end);
		print_outpout_64(list[index], stringtable, seg_infos, seg_infos->cmd_f);
		free(list[index]);
		list[index] = NULL;
	}
	free(list);
	return (EXIT_SUCCESS);
}
