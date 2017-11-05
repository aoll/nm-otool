/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_segment_section_64.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct section_64 *ft_find_segment_section_64(char *ptr,
	struct mach_header_64 *header, char *segment_name, char *section_name)
{
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*section;

	lc = (void *)ptr + sizeof(*header);
	if (ft_check_load(lc, header->ncmds, header->sizeofcmds))
		return (NULL);
	if (!(seg = ft_find_segment_64(lc, header->ncmds, segment_name)))
		return (NULL);
	if (!(section = ft_find_section_64(seg, section_name)))
		return (NULL);
	return (section);
}
