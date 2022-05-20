/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:42:43 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/20 18:00:04 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

size_t	ft_strlen(char const	*str)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}

void	ft_init(t_all *var, char **env, int ac, char **av)
{
	var->paths = ft_findpath(env);
	ft_path_checker(var->paths);
	var->i = 0;
	var->j = 0;
	var->fork_num = ac - 3;
	var->pipe_num = var->fork_num;
	var->fd[0] = open(av[1], O_RDWR);
	if (var->fd[0] < 0)
	{
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
	var->fd[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (var->fd[1] < 0)
	{
		ft_putstr_fd("unreadable file", 1);
		exit(1);
	}
}

void	ft_init2(t_all *var)
{
	var->p = (int **)malloc(sizeof(int *) * var->pipe_num);
	ft_malloc(var->p);
	var->pid = (pid_t *)malloc(sizeof(pid_t) * var->fork_num);
	ft_malloc(var->pid);
	while (var->i < var->pipe_num)
	{
		var->p[var->i] = (int *)malloc(sizeof(int) * 2);
		if (var->p[var->i] == NULL)
		{
			printf("ERROR\n");
			exit(1);
		}
		if (pipe(var->p[var->i]) == -1)
		{
			printf("ERROR\n");
			exit(1);
		}
		(var->i)++;
	}
}
