/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_index_sorted_64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_sort	**array_index_sorted_64(struct nlist_64 *nlist, int nsyms, char *stringtable)
{
	t_sort					**sort;
	int						err;

	if (!(sort = malloc(sizeof(t_sort *) * nsyms)))
		return (NULL);
	if ((err = init_sort_64(sort, nlist, nsyms, stringtable)))
	{
		free(sort);
		return (NULL);
	}
	printf("%s\n", "BEGIN SORT");
	sort_ascii(sort, nsyms);
	printf("%s\n", "END SORT");
	return (sort);
}

