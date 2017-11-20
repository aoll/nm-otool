/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:29 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:22:31 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	set_index(
	struct nlist **tmp, int *index, int i, struct nlist **list)
{
	*tmp = list[i];
	*index = i;
}

static int	loop_sort(
	struct nlist **list, int nsyms, char *s, int is_indian)
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
			cmp = ft_strcmp(s + swap_uint32_check(tmp->n_un.n_strx, is_indian),
				s + swap_uint32_check(list[i]->n_un.n_strx, is_indian));
			if (cmp > 0)
				set_index(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value > list[i]->n_value)
				set_index(&tmp, &index, i, list);
		}
	}
	return (index);
}

static int	loop_sort_reverse(
	struct nlist **list, int nsyms, char *s, int is_indian)
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
			cmp = ft_strcmp(s + swap_uint32_check(tmp->n_un.n_strx, is_indian),
				s + swap_uint32_check(list[i]->n_un.n_strx, is_indian));
			if (cmp < 0)
				set_index(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value < list[i]->n_value)
				set_index(&tmp, &index, i, list);
		}
	}
	return (index);
}

int			ft_sort(
	struct nlist *array, int nsyms,
	char *stringtable, t_seg_infos *seg_infos)
{
	struct nlist		**list;
	int					j;
	int					index;


	printf("%s\n", "SORT");
	printf("SEG INFOS\n text_nsect: %d, data_nsect: %d, bss_nsect: %d\n",seg_infos->text_nsect, seg_infos->data_nsect, seg_infos->bss_nsect);
	if (!(list = ft_copy_nlist(array, nsyms)))
		return (EXIT_FAILURE);
	j = -1;
	while (++j < nsyms)
	{
		if (seg_infos->cmd_f->p)
			index = j;
		else if (seg_infos->cmd_f->r)
			index = loop_sort_reverse(
				list, nsyms, stringtable, seg_infos->cmd_f->is_indian);
		else
			index = loop_sort(
				list, nsyms, stringtable, seg_infos->cmd_f->is_indian);
		print_outpout(list[index], stringtable, seg_infos, seg_infos->cmd_f);
		free(list[index]);
		list[index] = NULL;
	}
	free(list);
	return (EXIT_SUCCESS);
}
