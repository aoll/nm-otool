/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_outpout.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:24:35 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/17 16:48:57 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	sort_and_print_outpout(
	struct symtab_command *sym, void *ptr, void *ptr_end,
	t_seg_infos *seg_infos)
{
	char				*stringtable;
	struct nlist		*array;

	if ((void *)(array = ptr + swap_uint32(sym->symoff)) > ptr_end)
		return (EXIT_FAILURE);
	if ((void *)(stringtable = ptr + swap_uint32(sym->stroff)) > ptr_end)
		return (EXIT_FAILURE);

	return (ft_sort(array, swap_uint32(sym->nsyms), stringtable, seg_infos));
}
