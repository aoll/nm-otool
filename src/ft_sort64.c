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

char		*is_bad_adresse(char *s, long offset, void *ptr_end)
{
	if (offset < 0 || (void *)(s + offset) >= (void *)ptr_end)
	{
		return (BAD_STRING_INDEX);
	}
	return ((s + offset));
}

// int	f_cmp(char *s, long offset1, long offset2, void *ptr_end)
// {
// 	int r;
//
// 	if((size_t)(offset1 + s) > (size_t)ptr_end)
// 		r = -1;
// 	else if((size_t)(offset2 + s) > (size_t)ptr_end)
// 		r = 1;
// 	else
// 	{
// 		r = strcmp(offset1 + s, offset2 + s);
// 	}
// 	return (r);
// }

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
		if (list[i] && tmp)
		{

			// cmp = f_cmp(stringtable, tmp->n_un.n_strx, list[i]->n_un.n_strx, ptr_end);
			cmp = ft_strcmp(is_bad_adresse(stringtable, tmp->n_un.n_strx, ptr_end),
				is_bad_adresse(stringtable, list[i]->n_un.n_strx, ptr_end));
			if (cmp > 0)
				set_index64(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value > list[i]->n_value)
				set_index64(&tmp, &index, i, list);
			// else if (i && !cmp && tmp->n_value == list[i]->n_value)
			// {
			// 	if (list[i]->n_sect > tmp->n_sect)
			// 	{
			// 		set_index64(&tmp, &index, i, list);
			// 	}
			// 	// else if (list[i]->n_type > tmp->n_type)
			// 	// {
			// 	// 	set_index64(&tmp, &index, i, list);
			// 	// }
			// }

			// 	printf("n_desc: %d\n", list[i]->n_desc);
			// 	printf("n_sect: %d\n", list[i]->n_sect);
			// 	printf("n_type: %d\n", list[i]->n_type);
			// 	printf("n_un.n_strx: %d\n", list[i]->n_un.n_strx);
			//
			//
			// 	printf("n_desc tmp: %d\n", tmp->n_desc);
			// 	printf("n_sect tmp: %d\n", tmp->n_sect);
			// 	printf("n_type: %d\n", tmp->n_type);
			// 	printf("n_un.n_strx tmp: %d\n", tmp->n_un.n_strx);
			// 	exit(0);
			// }
			// else
			// 	continue;
			// if (check)
				// tmp->n_un.n_strx = -1;
			// 	set_index64(&tmp, &index, i, list);
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
			if ((void *)(s + list[i]->n_un.n_strx) >= ptr_end)
			{
				list[i]->n_un.n_strx = -1;
			}
			cmp = ft_strncmp(is_bad_adresse(s, tmp->n_un.n_strx, ptr_end),
				is_bad_adresse(s, list[i]->n_un.n_strx, ptr_end), 0);
			if (cmp < 0)
				set_index64(&tmp, &index, i, list);
			else if (!cmp && tmp->n_value < list[i]->n_value)
				set_index64(&tmp, &index, i, list);
			else if (!cmp)
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
			index = loop_sort64(list, nsyms, stringtable, (void *)seg_infos->ptr_end);

		//
		// if (list[index]->n_value ==  0x0100000000000002)
		// {
		// 	printf("n_value: %llu ,", list[index]->n_value);
		// 	printf("n_desc: %d ,", list[index]->n_desc);
		// 	printf("n_sect: %d ,", list[index]->n_sect);
		// 	printf("n_type: %d ,", list[index]->n_type);
		//
		// 	printf("n_un.n_strx: %d ", list[index]->n_un.n_strx);
		// 	if ((void *)(stringtable + list[index]->n_un.n_strx)
		// 	>= seg_infos->ptr_end)
		// 		list[index]->n_un.n_strx = -1;
		// 	printf("n_strx: %d\n", list[index]->n_un.n_strx);
		// 	print_outpout_64(list[index], stringtable, seg_infos, seg_infos->cmd_f);
		// }


		if ((void *)(stringtable + list[index]->n_un.n_strx)
		>= seg_infos->ptr_end)
			list[index]->n_un.n_strx = -1;

		print_outpout_64(list[index], stringtable, seg_infos, seg_infos->cmd_f);

		free(list[index]);
		list[index] = NULL;
	}
	free(list);
	return (EXIT_SUCCESS);
}
