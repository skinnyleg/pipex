/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/18 22:57:48 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

	cmd = ft_split(av[2], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		ft_read(p, path, cmd);
		fd[0] = open(av[3], O_RDWR | O_CREAT | O_TRUNC, 0777);
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
	int		pid;
	char	*paths;
	int		i;
	char	**cmd;
	char	*path;
	int		j;

	paths = ft_findpath(env);
	ft_path_checker(paths);
	if (ac - 1 == 1)
	{
		pid = ft_child_one(paths, av, env);
		wait(&pid);
		return (0);
	}
	int fd[2];
	fd[0] = open(av[1], O_RDWR);
	fd[1] = open(av[ac -1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd[0] < 0 || fd[1] < 0)
	{
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
	int num_fork = ac - 3;
	int **p;
	p = (int **)malloc(sizeof(int *) * (num_fork - 1));
	i = 0;
	while (i < num_fork - 1)
	{
		p[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(p[i]) == -1)
			return (ft_putstr_fd("pipe error", 1), 0);
		i++;
	}
	j = 2;
	cmd = ft_split(av[j], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		dup2(p[0][1], 1);
		close(p[0][0]);
		dup2(fd[0], 0);
		close(p[0][1]);
		// close(p[1][1]);
		// close(p[1][0]);
		close(fd[0]);
		close(fd[1]);
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd, 2);
	}
	else
	{
		wait(NULL);
		close(p[0][0]);
		close(p[0][1]);
		free_memory_pipex(cmd);
		free(path);
	}
	num_fork--;
	i = 0;
	while (num_fork != 1)
	{
		j++;
		i++;
		cmd = ft_split(av[j], ' ');
		ft_split_check(cmd);
		path = ft_path(paths, cmd[0]);
		ft_path_null(path, cmd);
		pid = fork();
		ft_pid(pid, path, cmd);
		if (pid == 0)
		{
			dup2(p[i][0], 0);
			printf("asj\n");
			dup2(p[i][1], 1);
			close(p[i][0]);
			close(p[i][1]);
			close(fd[0]);
			close(fd[1]);
			if (execve(path, cmd, env) == -1)
				ft_execve_error(path, cmd, 2);
		}
		else
		{
			wait(NULL);
			close(p[i][0]);
			close(p[i][1]);
			free_memory_pipex(cmd);
			free(path);
		}
	}
	cmd = ft_split(av[ac - 2], ' ');
	ft_split_check(cmd);
	path = ft_path(paths, cmd[0]);
	ft_path_null(path, cmd);
	pid = fork();
	ft_pid(pid, path, cmd);
	if (pid == 0)
	{
		// ft_read(p, path, cmd);
		dup2(p[0][0], 0);
		// close(p[1][1]);
		dup2(fd[1], 1);
		// close(p[1][0]);
		close(p[0][0]);
		close(p[0][1]);
		close(fd[0]);
		if (execve(path, cmd, env) == -1)
			ft_execve_error(path, cmd, 3);
	}
	else
	{
		wait(NULL);
		printf("asd\n");
		close(p[1][1]);
		close(p[1][0]);
		free_memory_pipex(cmd);
		free(path);
	}
	return (0);
}
