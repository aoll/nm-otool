/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outpout_format_64.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int	print_outpout_format_64(struct nlist_64 *nlist, char type, char *name)
{
	if (nlist->n_value || type != 'U')
	{
		ft_print_padding_adresse(nlist->n_value, ft_strlen(PADDING_STR_64), PADDING_STR_64);
		// printf("%016llx",nlist->n_value);
	}
	else
	{
		write(1, PADDING_SPACE_64, ft_strlen(PADDING_SPACE_64));
	}
	write(1, " ", 1);
	write(1, &type, 1);
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

