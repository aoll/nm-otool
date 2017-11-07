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

struct section	*ft_find_segment_section(char *ptr,
	struct mach_header *header, char *segment_name, char *section_name)
{
	struct load_command			*lc;
	struct segment_command		*seg;
	struct section				*section;

	lc = (void *)ptr + sizeof(*header);
	if (!(seg = ft_find_segment(lc, header->ncmds, segment_name)))
		return (NULL);
	if (!(section = ft_find_section(seg, section_name)))
		return (NULL);
	return (section);
}
