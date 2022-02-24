/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitam <haitam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/02/24 23:25:40 by haitam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_memory_pipex(char **s)
{
	int	block;

	block = 0;
	while (s[block])
	{
		free(s[block]);
		block++;
	}
}

void	ft_file(int	fd)
{
	if (fd < 0)
	{
		ft_putstr_fd("unreadable file",1);
		exit(1);
	}
}
char	*ft_findpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i],"PATH",4) == 0)
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
		if(access(try, F_OK) == 0)
			return (free_memory_pipex(path), free_memory_pipex(cmd), free(check), try);
		a++;
		free(try);
	}
	free_memory_pipex(path);
	free_memory_pipex(cmd);
	free(check);
	return (NULL);
}

int	ft_child1(char **env, char **av, int *p)
{
	char	*path;
	char	*paths;
	char	**cmd;
	int		fd;
	pid_t	pid;

	paths = ft_findpath(env);
	cmd = ft_split(av[2], ' ');
	path = ft_path(paths, cmd[0]);
	pid = fork();
	if(pid == 0)
	{
		fd = open(av[1], O_RDWR);
		ft_file(fd);
		dup2(p[1], 1);
		close(p[0]);
		dup2(fd, 0);
		close(p[1]);
		close(fd);
		execve(path, cmd, env);
	}
	free(path);
	free_memory_pipex(cmd);
	return (pid);
}

int	ft_child2(char **env, char **av, int *p)
{
	char	*path;
	char	*paths;
	char	**cmd;
	int		fd;
	pid_t	pid;

	paths = ft_findpath(env);
	cmd = ft_split(av[3], ' ');
	path = ft_path(paths, cmd[0]);
	pid = fork();
	if(pid == 0)
	{
		fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 777);
		ft_file(fd);
		dup2(p[0], 0);
		close(p[1]);
		dup2(fd, 1);
		close(p[0]);
		close(fd);
		execve(path, cmd, env);
	}
	free(path);
	free_memory_pipex(cmd);
	return (pid);
}

int main(int ac, char **av, char *env[])
{
	int	p[2];
	int	pid[2];
	int	state;

	if (ac != 5)
		return(0);
	if (pipe(p) == -1)
		return (0);
	pid[0] = ft_child1(env, av, p);
	pid[1] = ft_child2(env, av, p);
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &state, 0);
	waitpid(pid[1], &state, 0);
	return (0);
}