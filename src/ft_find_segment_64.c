/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_segment_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:20:28 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:33:22 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct segment_command_64	*ft_find_segment_64(
	struct load_command *lc, int ncmds, char *segment_name, t_ptr *ptr_infos)
{
	struct segment_command_64	*seg;
	int							i;
	int							nb_seg;

	seg = NULL;
	i = 0;
	nb_seg = 0;
	while (i < ncmds)
	{
		if (swap_uint32_check(lc->cmd, ptr_infos->is_indian) == LC_SEGMENT_64)
		{
			if ((void *)(seg = (struct segment_command_64 *)lc)
			+ sizeof(struct segment_command) > (void *)ptr_infos->ptr_end)
				return (NULL);
			if (ft_strcmp(seg->segname, segment_name) == 0 || ncmds == 1)
				return (seg);
			nb_seg++;
		}
		if ((void *)(lc = (void *)lc
		+ swap_uint32_check(lc->cmdsize, ptr_infos->is_indian)) + sizeof(*lc)
		> (void *)ptr_infos->ptr_end)
			return (NULL);
		i++;
	}
	return (seg);
}
