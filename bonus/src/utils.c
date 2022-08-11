/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:29:09 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/11 12:12:12 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strjoin_custom(char const *s1,	char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	tab = (char *)malloc(i + j + 1);
	if (tab == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		tab[i] = s1[i];
	while (*s2 != '\0')
	{
		tab[i] = (char)*s2++;
		i++;
	}
	tab[i] = '\0';
	free((void *)s1);
	return (tab);
}

void	close_all(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->pipe_num)
	{
		close(var->p[i][0]);
		close(var->p[i][1]);
		i++;
	}
	close(var->fd[0]);
	close(var->fd[1]);
}

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
