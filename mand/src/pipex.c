/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/18 17:48:37 by hmoubal          ###   ########.fr       */
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
	char	*check;
	char	*try;
	int		a;

	a = 0;
	try = NULL;
	if (access(av, F_OK) == 0)
		return (ft_strdup(av));
	path = ft_split(env + 5, ':');
	check = ft_strjoin_pipex("/", av);
	while (path[a])
	{
		try = ft_strjoin_pipex(path[a], check);
		if (access(try, F_OK) == 0)
			return (free_memory_pipex(path),
				free(check), try);
		a++;
		free(try);
	}
	free_memory_pipex(path);
	free(check);
	return (NULL);
}

int	ft_child1(char *paths, char **av, int *p, char **env)
{
	char	*path;
	char	**cmd;
	int		fd[2];
	pid_t	pid;

	cmd = ft_split(av[2], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		fd[0] = open(av[1], O_RDWR);
		ft_file(fd[0], path, cmd);
		dup2(p[1], 1);
		close(p[0]);
		dup2(fd[0], 0);
		close(p[1]);
		close(fd[0]);
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd, 2);
	}
	return (free(path), free_memory_pipex(cmd), pid);
}

int	ft_child2(char *paths, char **av, int *p, char **env)
{
	char	*path;
	char	**cmd;
	int		fd[2];
	pid_t	pid;

	cmd = ft_split(av[3], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		ft_read(p, path, cmd);
		fd[0] = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
		ft_file(fd[0], path, cmd);
		dup2(p[0], 0);
		close(p[1]);
		dup2(fd[0], 1);
		close(p[0]);
		close(fd[0]);
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd, 3);
	}
	return (free(path), free_memory_pipex(cmd), pid);
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
	wait(&pid[0]);
	pid[1] = ft_child2(paths, av, p, env);
	close(p[0]);
	close(p[1]);
	waitpid(-1, 0, 0);
	return (0);
}
