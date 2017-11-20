/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_segment_section.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:59 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:33:15 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct section	*ft_find_segment_section(t_ptr *ptr_infos,
	int is_indian, char *segment_name, char *section_name)
{
	struct mach_header			*header;
	struct load_command			*lc;
	struct segment_command		*seg;
	struct section				*section;

	if ((void *)(header = (struct mach_header *)ptr_infos->ptr)
	+ sizeof(struct mach_header) > (void *)ptr_infos->ptr_end)
		return (NULL);
	if ((void *)(lc = (void *)ptr_infos->ptr + sizeof(*header))
	+ sizeof(struct load_command) > (void *)ptr_infos->ptr_end)
		return (NULL);
	ptr_infos->is_indian = is_indian;
	if (!(seg = ft_find_segment(lc,
		swap_uint32_check(header->ncmds, is_indian), segment_name, ptr_infos)))
		return (NULL);
	if (!(section = ft_find_section(seg, section_name, ptr_infos)))
		return (NULL);
	return (section);
}
