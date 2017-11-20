/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:46 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:22:47 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	handle_64_text(char *ptr, char *ptr_end, char *av)
{
	struct mach_header_64		*header;
	struct section_64			*section;

	if ((void *)ptr + sizeof(struct mach_header_64) > (void *)ptr_end)
	{
		return (EXIT_FAILURE);
	}
	header = (struct mach_header_64 *)ptr;
	if ((void *)ptr + header->sizeofcmds > (void *)ptr_end)
	{
		return (EXIT_FAILURE);
	}
	if (!(section = ft_find_segment_section_64(
		ptr, header, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	write(1, av, ft_strlen(av));
	write(1, ":\n", 2);
	// print_text_text_section(
		// (void*)ptr + section->offset, section->addr, section->size, 1);
	return (EXIT_SUCCESS);
}
