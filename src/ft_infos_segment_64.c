/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infos_segment_64.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:21:30 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:25:16 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	loop_segment64(
	struct load_command *lc, int *index, t_seg_infos *seg_infos)
{
	struct segment_command_64	*segment;
	struct section_64			*section;
	uint32_t					loop;

	segment = (struct segment_command_64*)lc;
	section = (void *)segment + sizeof(*segment);
	loop = 0;
	while (loop < segment->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			seg_infos->text_nsect = *index + 1;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			seg_infos->data_nsect = *index + 1;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			seg_infos->bss_nsect = *index + 1;
		section = (void *)section + sizeof(*section);
		loop++;
		*index = *index + 1;
	}
}

t_seg_infos	*ft_infos_segment_64(char *ptr, char *ptr_end,
	struct mach_header_64 *header, struct load_command *lc)
{
	t_seg_infos					*seg_infos;
	uint32_t					i;
	int							index;

	if (!(seg_infos = malloc(sizeof(t_seg_infos))))
		return (NULL);
	ft_init_seg_infos(seg_infos);
	if ((void *)(lc = (void *)ptr + sizeof(*header)) > (void *)ptr_end)
		return (NULL);
	if (ft_check_load(lc, header->ncmds, header->sizeofcmds))
		return (NULL);
	i = 0;
	index = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			loop_segment64(lc, &index, seg_infos);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (seg_infos);
}
