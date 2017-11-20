/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:17 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:20:19 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct section	*ft_find_section(
	struct segment_command *segment, char *section_name, t_ptr *ptr_infos)
{
	struct section			*section;
	uint32_t				loop;

	loop = 0;
	if ((void *)(section = (void *)segment + sizeof(*segment))
	+ sizeof(struct section) > (void *)ptr_infos->ptr_end)
		return (NULL);
	while (loop < swap_uint32_check(segment->nsects, ptr_infos->is_indian))
	{
		if (!ft_strcmp(section->sectname, section_name))
		{
			return (section);
		}
		if ((void *)(section = (void *)section + sizeof(*section))
		+ sizeof(struct section) > (void *)ptr_infos->ptr_end)
			return (NULL);
		loop++;
	}
	return (NULL);
}
