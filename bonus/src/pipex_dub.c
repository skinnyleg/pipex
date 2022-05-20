/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/20 18:00:17 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void	ft_first(t_all *var, char **av, char **env, int index)
{
	char	*path;
	char	**cmd;
	int		j;

	j = 0;
	cmd = ft_split(av[index + 2], ' ');
	ft_split_check(cmd);
	path = ft_path(var->paths, cmd[0]);
	ft_path_null(path, cmd);
	while (j < var->pipe_num)
	{
		close(var->p[j][0]);
		if (j != index + 1)
			close(var->p[j][1]);
		j++;
	}
	dup2(var->p[index + 1][1], 1);
	dup2(var->fd[0], 0);
	close(var->fd[0]);
	close(var->p[index + 1][index + 1]);
	close(var->fd[1]);
	if (execve(path, cmd, env) == -1)
		ft_execve_error(path, cmd, 3);
}

void	ft_middle(t_all *var, char **av, char **env, int index)
{
	char	*path;
	char	**cmd;
	int		j;

	j = 0;
	cmd = ft_split(av[index + 2], ' ');
	ft_split_check(cmd);
	path = ft_path(var->paths, cmd[0]);
	ft_path_null(path, cmd);
	while (j < var->pipe_num)
	{
		if (j != index)
			close(var->p[j][0]);
		if (j != index + 1)
			close(var->p[j][1]);
		j++;
	}
	dup2(var->p[index][0], 0);
	dup2(var->p[index + 1][1], 1);
	close(var->fd[0]);
	close(var->fd[1]);
	close(var->p[index][0]);
	close(var->p[index + 1][1]);
	if (execve(path, cmd, env) == -1)
		ft_execve_error(path, cmd, 3);
}

void	ft_last(t_all *var, char **av, char **env, int index)
{
	char	*path;
	char	**cmd;
	int		j;

	j = 0;
	cmd = ft_split(av[index + 2], ' ');
	ft_split_check(cmd);
	path = ft_path(var->paths, cmd[0]);
	ft_path_null(path, cmd);
	while (j < var->pipe_num)
	{
		if (j != index)
			close(var->p[j][0]);
		close(var->p[j][1]);
		j++;
	}
	dup2(var->p[index][0], 0);
	dup2(var->fd[1], 1);
	close(var->fd[0]);
	close(var->fd[1]);
	close(var->p[index - 1][0]);
	if (execve(path, cmd, env) == -1)
		ft_execve_error(path, cmd, 3);
}

int	main(int ac, char **av, char *env[])
{
	t_all	var;

	ft_init(&var, env, ac, av);
	ft_init2(&var);
	ft_routine(&var, av, env);
	var.j = 0;
	while (var.j < var.pipe_num)
	{
		close(var.p[var.j][0]);
		close(var.p[var.j][1]);
		(var.j)++;
	}
	close(var.fd[0]);
	close(var.fd[1]);
	var.i = 0;
	while (var.i < var.fork_num)
	{
		wait(NULL);
		(var.i)++;
	}
	return (0);
}
