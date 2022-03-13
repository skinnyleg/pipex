/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/03/13 22:24:30 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_findpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_path(char *env, char *av)
{
	char	**path;
	char	**cmd;
	char	*check;
	char	*try;
	int		a;

	a = 0;
	try = NULL;
	path = ft_split(env + 5, ':');
	cmd = ft_split(av, ' ');
	check = ft_strjoin_pipex("/", cmd[0]);
	while (path[a])
	{
		try = ft_strjoin_pipex(path[a], check);
		if (access(try, F_OK) == 0)
			return (free_memory_pipex(path), free_memory_pipex(cmd),
				free(check), try);
		a++;
		free(try);
	}
	free_memory_pipex(path);
	free_memory_pipex(cmd);
	free(check);
	return (NULL);
}

int	ft_child1(char *paths, char **av, int *p, char **env)
{
	char	*path;
	char	**cmd;
	int		fd;
	pid_t	pid;

	cmd = ft_split(av[2], ' ');
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		fd = open(av[1], O_RDWR);
		ft_file(fd, path, cmd);
		dup2(p[1], 1);
		close(p[0]);
		dup2(fd, 0);
		close(p[1]);
		close(fd);
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd);
	}
	free(path);
	free_memory_pipex(cmd);
	return (pid);
}

int	ft_child2(char *paths, char **av, int *p, char **env)
{
	char	*path;
	char	**cmd;
	int		fd;
	pid_t	pid;

	cmd = ft_split(av[3], ' ');
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_file(fd, path, cmd);
		dup2(p[0], 0);
		close(p[1]);
		dup2(fd, 1);
		close(p[0]);
		close(fd);
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd);
	}
	free(path);
	free_memory_pipex(cmd);
	return (pid);
}

int	main(int ac, char **av, char *env[])
{
	int		p[2];
	int		pid[2];
	char	*paths;

	if (ac != 5)
		return (ft_putstr_fd("input error", 1), 0);
	if (pipe(p) == -1)
		return (ft_putstr_fd("pipe error", 1), 0);
	paths = ft_findpath(env);
	ft_path_checker(paths);
	pid[0] = ft_child1(paths, av, p, env);
	pid[1] = ft_child2(paths, av, p, env);
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
