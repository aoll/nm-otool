/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outpout_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:23:38 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:46:09 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	case_n_sect(
	struct nlist_64 *nlist, t_seg_infos *seg_infos, char *type)
{
	if (nlist->n_sect == seg_infos->text_nsect)
		*type = 't';
	else if (nlist->n_sect == seg_infos->data_nsect)
		*type = 'd';
	else if (nlist->n_sect == seg_infos->bss_nsect)
		*type = 'b';
	else
		*type = 's';
	if (nlist->n_sect == seg_infos->bss_nsect)
	{
		*type = 'b';
	}
}

static void	case_n_undef(struct nlist_64 *nlist, char *type)
{
	*type = 'u';
	if (nlist->n_value != 0)
	{
		if ((nlist->n_type & N_EXT))
			*type = 'c';
		else
			*type = '?';
	}

}

static int	set_type(struct nlist_64 *nlist, t_seg_infos *seg_infos)
{
	char				type;
	int					c;

	type = '?';
	c = nlist->n_type & N_TYPE;
	if (c == N_UNDF)
		case_n_undef(nlist, &type);
	else if (c == N_ABS)
		type = 'a';
	else if (c == N_SECT)
		case_n_sect(nlist, seg_infos, &type);
	else if (c == N_PBUD)
		type = 'u';
	else if (c == N_INDR)
		type = 'i';
	return (type);
}

int			print_outpout_64(
	struct nlist_64 *nlist, char *stringtable,
	t_seg_infos *seg_infos, t_cmd_flag *cmd_f)
{
	char				type;

	// printf("n_desc: %d ,", nlist->n_desc);
	// printf("n_sect: %d ,", nlist->n_sect);
	// printf("n_type: %d ,", nlist->n_type);
	// printf("n_un.n_strx: %d\n", nlist->n_un.n_strx);
	// return (0);

	if ((nlist->n_type & N_STAB) != 0)
		return (EXIT_SUCCESS);
	type = set_type(nlist, seg_infos);
	if (cmd_f->u && type != 'u')
		return (EXIT_SUCCESS);
	if (cmd_f->uu && type == 'u')
		return (EXIT_SUCCESS);
	if (cmd_f->g && !(nlist->n_type & N_EXT))
		return (EXIT_SUCCESS);
	if ((nlist->n_type & N_EXT) && type != '?')
			type = ft_toupper(type);
	if ((int)nlist->n_un.n_strx > -1)
		print_outpout_format_64(
			nlist, type, stringtable
			+ swap_uint32_check(nlist->n_un.n_strx, cmd_f->is_indian), cmd_f);
	else
	{
		// if (type == 'U')
		// 	type = '?';
		// if (type >= 'a' && type <= 'z')
		// 	type = '?';
		print_outpout_format_64(
			nlist, type, BAD_STRING_INDEX, cmd_f);
	}

	return (EXIT_SUCCESS);
}
