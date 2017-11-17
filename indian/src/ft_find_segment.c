/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:21:09 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:32:47 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct segment_command	*ft_find_segment(
	struct load_command *lc, int ncmds, char *segment_name)
{
	struct segment_command	*seg;
	int						i;
	int						nb_seg;

	seg = NULL;
	i = 0;
	nb_seg = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
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
