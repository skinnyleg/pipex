/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_rep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:25:33 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/18 22:13:47 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_child_rep(char *paths, char **av, int *p, char **env)
{
	char	*path;
	char	**cmd;
	pid_t	pid;

	cmd = ft_split(av[0], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		// fd[0] = open(av[1], O_RDWR);
		// ft_file(fd[0], path, cmd);
		dup2(p[0], 0);
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		// printf("asbd\n");
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd, 2);
	}
	return (free(path), free_memory_pipex(cmd), pid);
}

int	ft_child_one(char *paths, char **av, char **env)
{
	char	*path;
	char	**cmd;
	pid_t	pid;

	cmd = ft_split(av[1], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd, 2);
	}
	return (free(path), free_memory_pipex(cmd), pid);
}