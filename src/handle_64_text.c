/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:46 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/29 13:49:46 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_name(char *av)
{
	if (av)
	{
		write(1, av, ft_strlen(av));
		write(1, ":\n", 2);
	}
}

int			handle_64_text(char *ptr, char *ptr_end, char *av, int is_indian)
{
	struct mach_header_64		*header;
	struct section_64			*section;
	t_ptr						ptr_infos;

	ptr_infos.ptr = ptr;
	ptr_infos.ptr_end = ptr_end;
	ptr_infos.is_indian = is_indian;
	ptr_infos.is_64 = 1;
	if ((void *)ptr + sizeof(struct mach_header_64) > (void *)ptr_end)
		return (EXIT_FAILURE);
	header = (struct mach_header_64 *)ptr;
	if ((void *)ptr + swap_uint32_check(header->sizeofcmds, is_indian)
	> (void *)ptr_end)
		return (EXIT_FAILURE);
	if (!(section = ft_find_segment_section_64(
		&ptr_infos, is_indian, SEG_TEXT, SECT_TEXT)))
		return (EXIT_FAILURE);
	print_name(av);
	print_text_text_section(
		(void*)ptr + swap_uint32_check(section->offset, is_indian)
		, section->addr,
		swap_uint32_check(section->size, is_indian), &ptr_infos);
	return (EXIT_SUCCESS);
}
