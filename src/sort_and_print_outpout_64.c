/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_outpout_64.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:24:26 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/22 19:32:43 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	sort_and_print_outpout_64(
	struct symtab_command *sym, void *ptr, void *ptr_end,
	t_seg_infos *seg_infos)
{
	char				*stringtable;
	struct nlist_64		*array;

	if ((void *)(array = ptr
		+ swap_uint32_check(sym->symoff, seg_infos->cmd_f->is_indian))
		+ sizeof(struct nlist_64) > ptr_end)
		return (EXIT_FAILURE);
	if ((void *)(stringtable = ptr
		+ swap_uint32_check(sym->stroff, seg_infos->cmd_f->is_indian))
		+ 1 > ptr_end)
		return (EXIT_FAILURE);
	seg_infos->ptr = ptr;
	seg_infos->ptr_end = ptr_end;
	return (ft_sort64(array,
		swap_uint32_check(sym->nsyms, seg_infos->cmd_f->is_indian),
		stringtable, seg_infos));
}
