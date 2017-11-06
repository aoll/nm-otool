/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_outpout_64.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	sort_and_print_outpout_64(
	struct symtab_command *sym, void *ptr, void *ptr_end,
	t_seg_infos *seg_infos)
{
	char				*stringtable;
	struct nlist_64		*array;

	if ((void *)(array = ptr + sym->symoff) > ptr_end)
		return (EXIT_FAILURE);
	if ((void *)(stringtable = ptr + sym->stroff) > ptr_end)
		return (EXIT_FAILURE);
	return (ft_sort64(array, sym->nsyms, stringtable, seg_infos));
}
