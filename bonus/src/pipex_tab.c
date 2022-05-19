/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/19 19:22:12 by hmoubal          ###   ########.fr       */
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

void	ft_first(t_all *var, char **av, char **env, int index)
{
	char	*path;
	char	**cmd;
	int		j;
	int		i;

	i = 0;
	j = (index + index);
	if (j != 0)
		j = j - 2;
	cmd = ft_split(av[index + 2], ' ');
	ft_split_check(cmd);
	path = ft_path(var->paths, cmd[0]);
	ft_path_null(path, cmd);
	while (i < var->fork_num * 2)
	{
		if (i == index + 1)
			close(var->arr[i]);
		i++;
	}
	dup2(var->arr[j + 1], 1);
	dup2(var->fd[0], 0);
	close(var->fd[0]);
	close(var->arr[j + 1]);
	close(var->fd[1]);
	if (execve(path, cmd, env) == -1)
		ft_execve_error(path, cmd, 3);
}

void	ft_middle(t_all *var, char **av, char **env, int index)
{
	char	*path;
	char	**cmd;
	int		j;
	int		i;

	i = 0;
	j = (index + index);
	if (j != 0)
		j = j - 2;
	cmd = ft_split(av[index + 2], ' ');
	ft_split_check(cmd);
	path = ft_path(var->paths, cmd[0]);
	ft_path_null(path, cmd);
	while (i < var->fork_num * 2)
	{
		if (i == index + 1 && i != j)
			close(var->arr[i]);
		i++;
	}
	dup2(var->arr[j], 0);
	dup2(var->arr[j + 3], 1);
	close(var->fd[0]);
	close(var->fd[1]);
	close(var->arr[j]);
	close(var->arr[j + 3]);
	if (execve(path, cmd, env) == -1)
		ft_execve_error(path, cmd, 3);
}

void	ft_last(t_all *var, char **av, char **env, int index)
{
	char	*path;
	char	**cmd;
	int		j;
	int		i;

	i = 0;
	j = (index + index);
	if (j != 0)
		j = j - 2;
	cmd = ft_split(av[index + 2], ' ');
	ft_split_check(cmd);
	path = ft_path(var->paths, cmd[0]);
	ft_path_null(path, cmd);
	while (i < var->fork_num * 2)
	{
		if (i != j)
			close(var->arr[i]);
		i++;
	}
	dup2(var->arr[j], 0);
	dup2(var->fd[1], 1);
	close(var->fd[0]);
	close(var->fd[1]);
	close(var->arr[j]);
	if (execve(path, cmd, env) == -1)
		ft_execve_error(path, cmd, 3);
}

int	main(int ac, char **av, char *env[])
{
	t_all	var;

	var.paths = ft_findpath(env);
	ft_path_checker(var.paths);
	var.i = 0;
	var.j = 0;
	var.fork_num = ac - 3;
	var.pipe_num = var.fork_num;
	var.fd[0] = open(av[1], O_RDWR);
	if (var.fd[0] < 0)
	{
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
	var.fd[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (var.fd[1] < 0)
	{
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
	var.arr = (int *)malloc(sizeof(int) * var.pipe_num * 2);
	if (var.arr == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	var.i = 0;
	while (var.i < var.fork_num * 2)
	{
		if (pipe(var.arr + var.i) == -1)
		{
			printf("ERROR\n");
			exit(1);
		}
		var.i += 2;
	}
	var.pid = (pid_t *)malloc(sizeof(pid_t) * var.fork_num);
	if (var.pid == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	var.i = 0;
	while (var.i < var.fork_num)
	{
		var.pid[var.i] = fork();
		if (var.pid[var.i] == -1)
		{
			printf("ERROR\n");
			exit(1);
		}
		if (var.pid[var.i] == 0)
		{
			if (var.i == 0)
			{
				//first child
				ft_first(&var, av, env, var.i);
			}
			if (var.i > 0 && var.i < var.fork_num - 1)
			{
				// middle child or multiple childs
				ft_middle(&var, av, env, var.i);
			}
			if (var.i == var.fork_num - 1)
			{
				// last child
				ft_last(&var, av, env, var.i);
			}
			return (0);
		}
		(var.i)++;
	}
	var.j = 0;
	while (var.j < var.pipe_num * 2)
	{
		close(var.arr[var.j]);
		(var.j)++;
	}
	var.i = 0;
	while (var.i < var.fork_num)
	{
		wait(NULL);
		(var.i)++;
	}
	printf("hello form main process\n");
	return (0);
}
