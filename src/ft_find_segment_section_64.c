/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_segment_section_64.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:38 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/23 00:56:19 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int			check_load(struct mach_header_64 *header,
	t_ptr *ptr_infos, struct load_command *lc)
{
	t_load						load;

	load.is_indian = swap_uint32(*(int *)ptr_infos->ptr) == MH_MAGIC_64 ? 1 : 0;
	load.ncmds = swap_uint32_check(header->ncmds, load.is_indian);
	load.sizeofcmds = swap_uint32_check(header->sizeofcmds, load.is_indian);
	load.ptr = ptr_infos->ptr;
	load.ptr_end = ptr_infos->ptr_end;
	if (ft_check_load(lc, ptr_infos->ptr_end, &load))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

struct section_64	*ft_find_segment_section_64(t_ptr *ptr_infos,
	int is_indian, char *segment_name, char *section_name)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*section;

	if ((void *)(header = (struct mach_header_64 *)ptr_infos->ptr)
	+ sizeof(struct mach_header) > (void *)ptr_infos->ptr_end)
		return (NULL);
	if ((void *)(lc = (void *)ptr_infos->ptr + sizeof(*header))
	+ sizeof(struct load_command) > (void *)ptr_infos->ptr_end)
		return (NULL);
	if (check_load(header, ptr_infos, lc))
		return (NULL);
	ptr_infos->is_indian = is_indian;
	if (!(seg = ft_find_segment_64(lc,
		swap_uint32_check(header->ncmds, is_indian), segment_name, ptr_infos)))
		return (NULL);
	if (!(section = ft_find_section_64(seg, section_name, ptr_infos)))
		return (NULL);
	return (section);
}
