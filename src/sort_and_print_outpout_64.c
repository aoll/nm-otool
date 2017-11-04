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
	struct symtab_command *sym, void *ptr, t_seg_infos *seg_infos)
{
	char				*stringtable;
	struct nlist_64		*array;

	array = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	return (ft_sort64(array, sym->nsyms, stringtable, seg_infos));
}
