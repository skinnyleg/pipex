/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:55 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/10 14:50:43 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strjoin(char const *s1,	char const *s2)
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

size_t	ft_strlen(char const	*str)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}

int	ft_strncmp(const char *str,	const char *tab,	size_t a)
{
	size_t	i;

	i = 0;
	while (str[i] == tab[i] && a != 0 && str[i] != '\0' && tab[i] != '\0')
	{
		i++;
		a--;
	}
	if (a == 0)
		return (0);
	return ((unsigned char)str[i] - (unsigned char)tab[i]);
}

void	*ft_memcpy(void *dest,	const void *src,	size_t size)
{
	char	*p1;
	char	*p2;
	int		i;

	p1 = dest;
	p2 = (char *)src;
	if (!p1 && !p2)
		return (NULL);
	i = 0;
	while (size != 0)
	{
		p1[i] = p2[i];
		i++;
		size--;
	}
	return (dest);
}

void	ft_putstr_fd(char *s,	int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
