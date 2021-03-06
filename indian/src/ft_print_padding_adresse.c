/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding_adresse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:23 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:22:24 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_print_padding_adresse(
	long int addr, size_t len_padding, char *padding)
{
	char	*addr_str;

	addr_str = ft_strdup(padding);
	if (addr > 0)
		ft_get_adress_str(addr, &addr_str, len_padding - 1);
	write(1, addr_str, len_padding);
	free(addr_str);
}
