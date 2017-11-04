/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infos_segment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	loop_segment(
	struct load_command *lc, int *index, t_seg_infos *seg_infos)
{
	struct segment_command	*segment;
	struct section			*section;
	int							loop;

	segment = (struct segment_command *)lc;
	section = (void *)segment + sizeof(*segment);
	loop = 0;
	while (loop < segment->nsects)
	{
		if(ft_strcmp(section->sectname, SECT_TEXT) == 0)
			seg_infos->text_nsect = *index + 1;
		else if(ft_strcmp(section->sectname, SECT_DATA) == 0)
			seg_infos->data_nsect = *index + 1;
		else if(ft_strcmp(section->sectname, SECT_BSS) == 0)
			seg_infos->bss_nsect = *index + 1;
		section = (void *)section + sizeof(*section);
		loop++;
		*index = *index + 1;
	}
}

t_seg_infos	*ft_infos_segment(char *ptr, char *ptr_end,
	struct mach_header *header, struct load_command *lc)
{
	t_seg_infos					*seg_infos;
	int							i;
	int							index;

	if (!(seg_infos = malloc(sizeof(t_seg_infos))))
		return (NULL);
	lc = (void *)ptr + sizeof(*header);
	if (ft_check_load(ptr, lc, header->ncmds, header->sizeofcmds))
		return (NULL);
	ft_init_seg_infos(seg_infos);
	i = 0;
	index = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			loop_segment(lc, &index, seg_infos);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg_infos);
}
