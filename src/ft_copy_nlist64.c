/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_nlist64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:19:56 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 15:39:03 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void			ft_set_nlist64(
	struct nlist_64 *l, struct nlist_64 *array, int i)
{
	l->n_type = array[i].n_type;
	l->n_sect = array[i].n_sect;
	l->n_value = array[i].n_value;
	l->n_un.n_strx = array[i].n_un.n_strx;
}

struct nlist_64		**ft_copy_nlist64(
	struct nlist_64 *array, int nsyms, t_seg_infos *seg_infos)
{
	struct nlist_64	**list;
	struct nlist_64	*l;
	int				i;

	if (!(list = malloc(sizeof(struct nlist_64 *) * nsyms)))
		return (NULL);
	i = 0;
	while (i < nsyms)
	{
		if (!(l = malloc(sizeof(struct nlist_64)))
		|| (void *)((void *)array + (i * sizeof(*l))) + sizeof(*l)
		> seg_infos->ptr_end)
		{
			while (--i >= 0)
				free(list[i]);
			free(list);
			return (NULL);
		}
		ft_set_nlist64(l, array, i);
		list[i] = l;
		i++;
	}
	return (list);
}
