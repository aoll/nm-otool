/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outpout_format_64.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:23:46 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:23:47 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	print_outpout_format_64(
	struct nlist_64 *nlist, char type, char *name, t_cmd_flag *cmd_flag)
{
	if (!cmd_flag->u && !cmd_flag->j)
	{
		if (nlist->n_value || type != 'U')
		{
			ft_print_padding_adresse(
				nlist->n_value, ft_strlen(PADDING_STR_64), PADDING_STR_64);
		}
		else
		{
			write(STDOUT, PADDING_SPACE_64, ft_strlen(PADDING_SPACE_64));
		}
		write(STDOUT, " ", 1);
		write(STDOUT, &type, 1);
		write(STDOUT, " ", 1);
	}
	if (name)
		write(STDOUT, name, ft_strlen(name));
	write(STDOUT, "\n", 1);
	return (EXIT_SUCCESS);
}
