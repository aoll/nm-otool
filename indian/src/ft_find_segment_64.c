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
	struct load_command *lc, int ncmds, char *segment_name)
{
	struct segment_command_64	*seg;
	int							i;
	int							nb_seg;

	i = 0;
	nb_seg = 0;
	seg = NULL;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			if (ft_strcmp(seg->segname, segment_name) == 0 || ncmds == 1)
			{
				return (seg);
			}
			nb_seg++;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg);
}
