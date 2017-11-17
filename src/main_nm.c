/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:23:16 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:38:02 by aollivie         ###   ########.fr       */
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

static void	print_chariot(char *s)
{
	ft_putchar('\n');
	ft_putstr(s);
	ft_putstr(":\n");
}

int			main(int ac, char **av)
{
	int			ret;
	int			i;
	t_cmd_flag	cmd_f;
	int			check;

	if (ac < 2)
		return (EXIT_FAILURE);
	if ((i = set_cmd_flag(ac, av, &cmd_f, IS_NM)) < 0)
	{
		if (i == HELP_FLAG)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	check = ac - i;
	while (i < ac)
	{
		if (check > 1)
			print_chariot(av[i]);
		ret = execute_is_otool(av[i], &cmd_f);
		i++;
	}
	return (ret);
}
