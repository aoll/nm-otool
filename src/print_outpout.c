/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outpout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:24:01 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:46:19 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int swap_uint32_check_no(int val, int a)
{
	if (a)
		return (val);
	return (val);
}

static void	case_n_sect(
	struct nlist *nlist, t_seg_infos *seg_infos, char *type, t_cmd_flag *cmd_f)
{
	if ((int)swap_uint32_check_no(nlist->n_sect, cmd_f->is_indian) == seg_infos->text_nsect)
		*type = 't';
	else if ((int)swap_uint32_check_no(nlist->n_sect, cmd_f->is_indian) == seg_infos->data_nsect)
		*type = 'd';
	else if ((int)swap_uint32_check_no(nlist->n_sect, cmd_f->is_indian) == seg_infos->bss_nsect)
		*type = 'b';
	else
		*type = 's';
	if ((int)swap_uint32_check_no(nlist->n_sect, cmd_f->is_indian) == seg_infos->bss_nsect)
	{
		*type = 'b';
	}
}

static void	case_n_undef(struct nlist *nlist, char *type, t_cmd_flag *cmd_f)
{
	*type = 'u';
	if (swap_uint32_check_no(nlist->n_value, cmd_f->is_indian) != 0)
		*type = 'c';
}

static int	set_type(
	struct nlist *nlist, t_seg_infos *seg_infos, t_cmd_flag *cmd_f)
{
	char				type;
	int					c;

	type = '?';
	c = swap_uint32_check_no(nlist->n_type, cmd_f->is_indian) & N_TYPE;
	if (c == N_UNDF)
		case_n_undef(nlist, &type, cmd_f);
	else if (c == N_ABS)
		type = 'a';
	else if (c == N_SECT)
		case_n_sect(nlist, seg_infos, &type, cmd_f);
	else if (c == N_PBUD)
		type = 'u';
	else if (c == N_INDR)
		type = 'i';
	return (type);
}

int			print_outpout(
	struct nlist *nlist, char *stringtable,
	t_seg_infos *seg_infos, t_cmd_flag *cmd_f)
{
	char				type;

	if ((swap_uint32_check_no(nlist->n_type, cmd_f->is_indian) & N_STAB) != 0)
		return (EXIT_SUCCESS);
	type = set_type(nlist, seg_infos, cmd_f);
	if (cmd_f->u && type != 'u')
		return (EXIT_SUCCESS);
	if (cmd_f->uu && type == 'u')
		return (EXIT_SUCCESS);
	if (cmd_f->g
		&& !(swap_uint32_check_no(nlist->n_type, cmd_f->is_indian) & N_EXT))
		return (EXIT_SUCCESS);
	if ((swap_uint32_check_no(nlist->n_type, cmd_f->is_indian) & N_EXT)
	&& type != '?')
		type = ft_toupper(type);
	print_outpout_format(
		nlist, type, stringtable
		+ swap_uint32_check(nlist->n_un.n_strx, cmd_f->is_indian), cmd_f);
	return (EXIT_SUCCESS);
}
