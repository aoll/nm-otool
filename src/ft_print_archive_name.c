/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_archive_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:14 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:34:15 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_print_archive_name(char *s1, char *s2)
{
	write(1, s1, ft_strlen(s1));
	write(1, s2, ft_strlen(s2));
	write(1, "\n", 1);
}
