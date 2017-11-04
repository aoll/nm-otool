/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_archive_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char	*ft_format_archive_name(char *n1, char *n2, char *n3, char *n4)
{
	char	*s;
	int		l1;
	int		l2;
	int		l3;

	l1 = ft_strlen(n1);
	l2 = ft_strlen(n2);
	l3 = ft_strlen(n3);
	if (!(s = malloc(sizeof(char) * l1 + l2 + l3 + ft_strlen(n4) + 1)))
	{
		return (NULL);
	}
	s[l1 + l2 + l3 + ft_strlen(n4)] = '\0';
	ft_strcpy(s, n1);
	ft_strcpy(s + l1, n2);
	ft_strcpy(s + l1 + l2, n3);
	ft_strcpy(s + l1 + l2 + l3, n4);
	return (s);
}
