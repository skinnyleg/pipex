/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/02/10 01:19:29 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_memory(char **s,	int block)
{
	while (block--)
		free(s[block]);
	return (NULL);
}

void	ft_file(void)
{
	ft_putstr_fd("unreadable file",1);
	exit(1);
}
int main(int ac, char **av, char *env[])
{
	int		p[2];
	char	*line;
	char	**path;
	char	*try;
	char	*try2;
	int		a;
	int		i;
	pid_t	pid;

	line = NULL;
	path = NULL;
	try = NULL;
	try2 = NULL;
	a = 0;
	i = 0;
	if (ac == 5)
	{
		pipe(p);
		p[0] = open(av[1], O_RDWR);
		if (p[0] < 0)
			ft_file();
		p[1] = open(av[4], O_RDWR | O_CREAT, 777);
		if (p[1] < 0)
			ft_file();
		while(env[i])
		{
			if(ft_strncmp(env[i],"PATH",4) == 0)
				break ;
			i++;
		}
		path = ft_split(env[i] + 5,':');
		pid = fork();
		if (!pid)
		{
			try2 = ft_strjoin("/", av[3]);
			while(path[a])
			{
				try = ft_strjoin(path[a], try2);
				if (execve(try, av, env) == -1)
				{
					printf("did not work\n");
					free(try);
				}
				else
				{
					printf("did work\n");
					free(try2);
					free(try);
					break ;
				}
				a++;
			}
		else if (pid)
		{
			wait(NULL);
			try2 = ft_strjoin("/", av[2]);
			while(path[a])
			{
				try = ft_strjoin(path[a], try2);
				if (execve(try, av, env) == -1)
				{
					printf("did not work\n");
					free(try);
				}
				else
				{
					printf("did work\n");
					free(try2);
					free(try);
					break ;
				}
				a++;
			}
		}
		line = get_next_line(1);
		while(line)
		{
			a = ft_strlen(line);
			write(p[1],line,a);
			free(line);
			line = get_next_line(p[0]);
		}
		close(p[0]);
		close(p[1]);
	}
	else
		perror("error");
	return (0);
}
