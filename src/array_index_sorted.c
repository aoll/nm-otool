/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_index_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_sort	**array_index_sorted(struct nlist *nlist, int nsyms, char *stringtable)
{
	t_sort					**sort;
	int						err;

	if (!(sort = malloc(sizeof(t_sort *) * nsyms)))
		return (NULL);
	if ((err = init_sort(sort, nlist, nsyms, stringtable)))
	{
		free(sort);
		return (NULL);
	}
	sort_ascii(sort, nsyms);
	return (sort);
}

