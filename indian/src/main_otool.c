/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:23:28 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:38:12 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int	execute_is_otool(char *av, t_cmd_flag *cmd_f)
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
	ret = ft_otool(ptr, (void *)ptr + buf.st_size, av, cmd_f);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (ret);
}

int			main(int ac, char **av)
{
	int			ret;
	int			i;
	t_cmd_flag	cmd_f;

	if (ac < 2)
		return (EXIT_FAILURE);
	if ((i = set_cmd_flag(ac, av, &cmd_f, IS_OTOOL)) < 0)
	{
		if (i == HELP_FLAG)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	while (i < ac)
	{
		ret = execute_is_otool(av[i], &cmd_f);
		i++;
	}
	return (ret);
}
