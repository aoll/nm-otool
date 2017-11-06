/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/03/17 12:34:50 by aollivie            #+#    #+#             */
/*   Updated: 11/03/17 12:34:50 by aollivie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	execute_is_otool(char *av, int is_otool)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	int			ret;

	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_putstr(NO_ACCESS);
		ft_putstr(av);
		ft_putstr("\n");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	if ((ptr = mmap(
		0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	ret = ft_otool(ptr, (void *)ptr + buf.st_size, av, is_otool);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (ret);
}

int			main(int ac, char **av)
{
	int			ret;
	int			i;
	t_cmd_flag	cmd_f;

	cmd_f.is_otool = 0;
	if (ac < 2)
		return (EXIT_FAILURE);
	i = 1;
	while (i < ac)
	{
		ret = execute_is_otool(av[i], 0);
		i++;
	}
	return (ret);
}
