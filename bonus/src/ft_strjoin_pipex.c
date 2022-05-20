/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:01:34 by hmoubal           #+#    #+#             */
/*   Updated: 2022/05/20 17:59:29 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strjoin_pipex(char const *s1,	char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	tab = (char *)malloc(i + j + 1);
	if (tab == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		tab[k] = (char)*s1++;
		k++;
	}
	while (*s2 != '\0')
	{
		tab[k] = (char)*s2++;
		k++;
	}
	tab[k] = '\0';
	return (tab);
}

void	ft_routine(t_all *var, char **av, char **env)
{
	var->i = 0;
	while (var->i < var->fork_num)
	{
		var->pid[var->i] = fork();
		if (var->pid[var->i] == -1)
		{
			printf("ERROR\n");
			exit(1);
		}
		if (var->pid[var->i] == 0)
		{
			if (var->i == 0)
				ft_first(var, av, env, var->i);
			if (var->i > 0 && var->i < var->fork_num - 1)
				ft_middle(var, av, env, var->i);
			if (var->i == var->fork_num - 1)
				ft_last(var, av, env, var->i);
			return ;
		}
		(var->i)++;
	}
}
