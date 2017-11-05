/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct section	*ft_find_section(
	struct segment_command *segment, char *section_name)
{
	struct section			*section;
	uint32_t				loop;

	loop = 0;
	section = (void *)segment + sizeof(*segment);
	while (loop < segment->nsects)
	{
		if (!ft_strcmp(section->sectname, section_name))
		{
			return (section);
		}
		section = (void *)section + sizeof(*section);
		loop++;
	}
	return (NULL);
}
