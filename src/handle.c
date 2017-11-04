/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"


static int	loop_handle(char *ptr, char *ptr_end,
	struct mach_header *header, struct load_command *lc)
{
 	int						i;
	t_seg_infos				*seg_infos;
	struct symtab_command	*sym;

	if (!(seg_infos = ft_infos_segment(ptr, ptr_end, header, lc)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			sort_and_print_outpout(
				sym, ptr, seg_infos);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	free(seg_infos);
	return (EXIT_SUCCESS);
}

int			handle(char *ptr, char *ptr_end, char *av)
{
	struct mach_header	*header;
	struct load_command		*lc;

	if ((void *)(header = (struct mach_header *)ptr) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
		return (EXIT_FAILURE);
	lc = (void *)ptr + sizeof(*header);
	if (loop_handle(ptr, ptr_end, header, lc))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
