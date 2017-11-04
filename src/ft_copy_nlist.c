/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_nlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	 	ft_set_nlist(struct nlist *l, struct nlist *array, int i)
{
	l->n_type = array[i].n_type;
	l->n_sect = array[i].n_sect;
	l->n_value = array[i].n_value;
	l->n_un.n_strx = array[i].n_un.n_strx;
}

struct nlist	**ft_copy_nlist(struct nlist *array, int nsyms)
{
	struct nlist	**list;
	struct nlist	*l;
	int				i;

	if (!(list = malloc(sizeof(struct nlist *) * nsyms)))
		return (NULL);
	i = 0;
	while (i < nsyms)
	{
		if (!(l = malloc(sizeof(struct nlist))))
		{
			while (--i >= 0)
				free(list[i]);
			free(list);
			return (NULL);
		}
		ft_set_nlist(l, array, i);
		list[i] = l;
		i++;
	}
	return (list);
}
