/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/10 18:16:13 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	**ft_findpath(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*ft_path(t_var *var, char *av)
{
	char	*check;
	char	*try;
	int		a;

	a = 0;
	check = ft_strjoin("/", av);
	while (var->paths[a])
	{
		try = ft_strjoin(var->paths[a], check);
		if (access(try, F_OK) == 0)
			return (free(check), try);
		a++;
		free(try);
	}
	free(check);
	return (NULL);
}

void	ft_child1(t_var *var, char **env)
{
	pid_t	pid;

	pid = fork();
	ft_pid(pid, var);
	if (pid == 0)
	{
		dup2(var->p[0][1], 1);
		dup2(var->fd[0], 0);
		close_all(var);
		execve(var->cmd_path, var->cmd, env);
	}
	free(var->cmd_path);
	free_2d(var->cmd);
}

void	ft_child_middle(t_var *var, char **env)
{
	pid_t	pid;

	pid = fork();
	ft_pid(pid, var);
	if (pid == 0)
	{
		dup2(var->p[var->j - 3][0], 0);
		dup2(var->p[var->j - 2][1], 1);
		close_all(var);
		execve(var->cmd_path, var->cmd, env);
	}
	free(var->cmd_path);
	free_2d(var->cmd);
}

void	ft_child2(t_var *var, char **env)
{
	pid_t	pid;

	pid = fork();
	ft_pid(pid, var);
	if (pid == 0)
	{
		dup2(var->p[var->pipe_num - 1][0], 0);
		dup2(var->fd[1], 1);
		close_all(var);
		execve(var->cmd_path, var->cmd, env);
	}
	free(var->cmd_path);
	free_2d(var->cmd);
}

void	normal_mode(char **av, char **env, int ac)
{
	t_var	var;

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

void	mode_heredoc(char **av, char **env, int ac)
{
	printf("hello\n");
}

int	main(int ac, char **av, char *env[])
{
	t_var	var;

	if (ac < 5)
		return (ft_putstr_fd("input error\n", 2), 0);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		mode_heredoc(av, env, ac);
	else
		normal_mode(av, env, ac);
	return (0);
}
