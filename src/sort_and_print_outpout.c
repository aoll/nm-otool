/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_outpout.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:24:35 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:24:36 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	sort_and_print_outpout(
	struct symtab_command *sym, void *ptr, void *ptr_end,
	t_seg_infos *seg_infos)
{
	char				*stringtable;
	struct nlist		*array;

	printf("%s\n", "SORT AND PRINT OUTPUT");
	if ((void *)(array = ptr
		+ swap_uint32_check(sym->symoff, seg_infos->cmd_f->is_indian))
		+ sizeof(struct nlist) > ptr_end)
		return (EXIT_FAILURE);
	if ((void *)(stringtable = ptr
		+ swap_uint32_check(sym->stroff, seg_infos->cmd_f->is_indian))
		+ 1 > ptr_end)
		return (EXIT_FAILURE);
	return (ft_sort(array,
		swap_uint32_check(sym->nsyms, seg_infos->cmd_f->is_indian),
		stringtable, seg_infos));
}
