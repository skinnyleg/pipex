/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:07:53 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/11 12:15:12 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	read_write(char *c, char **tmp, char **av, int fd)
{
	while (read(0, c, 1) > 0)
	{
		if (c[0] != '\n')
			*tmp = ft_strjoin_custom(*tmp, c);
		if (c[0] == '\n')
		{
			if (ft_strncmp(*tmp, av[2], ft_strlen(*tmp)) == 0)
				break ;
			*tmp = ft_strjoin_custom(*tmp, c);
			write(fd, *tmp, ft_strlen(*tmp));
			free(*tmp);
			*tmp = ft_strdup("");
			if (*tmp == NULL)
			{
				free(c);
				ft_putstr_fd("Malloc Error\n", 2);
				exit(1);
			}
		}
	}
}

void	ft_create_heredoc(char **av)
{
	int		fd;
	char	*tmp;
	char	*c;

	fd = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0645);
	if (fd < 0)
	{
		ft_putstr_fd("Can't create here_doc file\n", 2);
		exit(1);
	}
	tmp = ft_strdup("");
	c = ft_strdup("");
	if (tmp == NULL || c == NULL)
	{
		free(c);
		free(tmp);
		ft_putstr_fd("Malloc Error\n", 2);
		exit(1);
	}
	read_write(c, &tmp, av, fd);
	free(c);
	free(tmp);
	close(fd);
}

void	normal_mode(char **av, char **env, int ac, t_var var)
{
	init(&var, av, env, ac);
	init_cmd(&var, av[var.j]);
	ft_child1(&var, env);
	var.j++;
	while (var.i < var.fork_num - 2)
	{
		init_cmd(&var, av[var.j]);
		ft_child_middle(&var, env);
		var.i++;
		var.j++;
	}
	init_cmd(&var, av[var.j]);
	ft_child2(&var, env);
	free_2d(var.paths);
	close_all(&var);
	var.i = 0;
	while (var.i < var.fork_num)
	{
		waitpid(-1, 0, 0);
		var.i++;
	}
}

void	mode_heredoc(char **av, char **env, int ac, t_var var)
{
	ft_create_heredoc(av);
	normal_mode(av, env, ac - 1, var);
	unlink("here_doc");
}
