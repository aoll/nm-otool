/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:52 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/22 21:16:25 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int					free_seg_infos(t_seg_infos **seg_infos, int ret)
{
	free(*seg_infos);
	return (ret);
}

static t_seg_infos	*init_loop_handle_64(char *ptr, char *ptr_end,
	struct mach_header_64 *header, struct load_command **lc)
{
	t_seg_infos	*seg_infos;

	if ((void *)(*lc = (void *)ptr + sizeof(*header))
	+ sizeof(struct load_command) > (void *)ptr_end)
		return (NULL);
	if (!(seg_infos = ft_infos_segment_64(ptr, ptr_end, header, *lc)))
		return (NULL);
	return (seg_infos);
}

static int			loop_handle_64(char *ptr, char *ptr_end,
	struct mach_header_64 *header, t_cmd_flag *cmd_f)
{
	uint32_t				i;
	t_seg_infos				*seg_infos;
	struct symtab_command	*sym;
	struct load_command		*lc;

	if (!(seg_infos = init_loop_handle_64(ptr, ptr_end, header, &lc)))
		return (EXIT_FAILURE);
	i = -1;
	seg_infos->cmd_f = cmd_f;
	while (++i < swap_uint32_check(header->ncmds, cmd_f->is_indian))
		if (swap_uint32_check(lc->cmd, cmd_f->is_indian) == LC_SYMTAB)
		{
			if ((void *)(sym = (struct symtab_command *)lc) + sizeof(*sym)
			> (void *)ptr_end)
				return (free_seg_infos(&seg_infos, EXIT_FAILURE));
			else if (sort_and_print_outpout_64(sym, ptr, ptr_end, seg_infos))
				return (free_seg_infos(&seg_infos, EXIT_FAILURE));
			break ;
		}
		else if ((void *)(lc = (void *)lc
		+ swap_uint32_check(lc->cmdsize, cmd_f->is_indian))
		+ sizeof(struct load_command) > (void *)ptr_end)
			return (free_seg_infos(&seg_infos, EXIT_FAILURE));
	return (free_seg_infos(&seg_infos, EXIT_SUCCESS));
}

int			handle_64(char *ptr, char *ptr_end, t_cmd_flag *cmd_f)
{
	struct mach_header_64	*header;

	if ((void *)(header = (struct mach_header_64 *)ptr)
	+ sizeof(struct mach_header) > (void *)ptr_end)
		return (EXIT_FAILURE);
	if ((void *)ptr + swap_uint32_check(header->sizeofcmds, cmd_f->is_indian)
	> (void *)ptr_end)
		return (EXIT_FAILURE);
	if (loop_handle_64(ptr, ptr_end, header, cmd_f))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
