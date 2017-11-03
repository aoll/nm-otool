/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	init_sort(t_sort **sort, struct nlist *nlist, int nsyms, char *stringtable)
{
	int		i;
	int		index;
	char	*tmp;
	t_sort	*new;

	i = 0;
	while (i < nsyms)
	{
		if (!(new = malloc(sizeof(t_sort))))
		{
			free_sort(sort, i);
			return (EXIT_FAILURE);
		}
		if (!(new->name = ft_strdup(stringtable + nlist[i].n_un.n_strx)))
		{
			free_sort(sort, i);
			return (EXIT_FAILURE);
		}
		new->index = i;
		sort[i] = new;
		i++;
	}
	return (EXIT_SUCCESS);
}

