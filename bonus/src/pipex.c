/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/11 14:07:47 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		dup2(var->p[var->i][0], 0);
		dup2(var->p[var->i + 1][1], 1);
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

int	main(int ac, char **av, char *env[])
{
	t_var	var;

	if (ac < 5)
		return (ft_putstr_fd("input error\n", 2), 0);
	var.ac = ac;
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		if (ac <= 5)
			return (ft_putstr_fd("input error\n", 2), 0);
		var.j = 1;
		mode_heredoc(av, env, ac, var);
	}
	else
	{
		var.j = 0;
		normal_mode(av, env, ac, var);
	}
	return (0);
}
