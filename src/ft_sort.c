/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:29 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 00:09:20 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int		loop_check_index(
	struct nlist **list, int nsyms, char *stringtable, t_seg_infos *seg_infos)
{
	int					i;

	i = -1;
	while (++i < nsyms)
	{
		if (list[i])
		{
			if ((long)swap_uint32_check((long)list[i]->n_un.n_strx,
			seg_infos->cmd_f->is_indian) < 0 ||
			(void *)(stringtable + swap_uint32_check((long)list[i]->n_un.n_strx,
			seg_infos->cmd_f->is_indian))
				>= (void *)seg_infos->ptr_end)
			{
				ft_putstr_fd(ERROR_STRING_INDEX, STDERR);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static	int	sort_set_index(
	struct nlist **list,
	int nsyms,
	char *stringtable,
	t_seg_infos *seg_infos)
{
	int	index;

	if (seg_infos->cmd_f->r)
		index = loop_sort_reverse(
			list, nsyms, stringtable, seg_infos);
	else
		index = loop_sort(
			list, nsyms, stringtable, seg_infos);
	return (index);
}

static int	sort_init_loop(
	struct nlist **list,
	int nsyms,
	char *stringtable,
	t_seg_infos *seg_infos)
{
	int	err;
	int	j;
	int	index;

	err = loop_check_index(list, nsyms, stringtable, seg_infos);
	j = -1;
	while (++j < nsyms)
	{
		index = j;
		if (!err)
		{
			if (!seg_infos->cmd_f->p)
				index = sort_set_index(list, nsyms, stringtable, seg_infos);
			if ((void *)(stringtable + swap_uint32_check(
				(long)list[index]->n_un.n_strx, seg_infos->cmd_f->is_indian))
			>= seg_infos->ptr_end)
				list[index]->n_un.n_strx = -1;
			print_outpout(
				list[index], stringtable, seg_infos, seg_infos->cmd_f);
		}
		free(list[index]);
		list[index] = NULL;
	}
	return (err);
}

int			ft_sort(
	struct nlist *array, int nsyms,
	char *stringtable, t_seg_infos *seg_infos)
{
	struct nlist		**list;
	int					j;
	int					err;

	if (!(list = ft_copy_nlist(array, nsyms)))
		return (EXIT_FAILURE);
	err = sort_init_loop(
		list, nsyms, stringtable, seg_infos);
	free(list);
	return (err);
}
