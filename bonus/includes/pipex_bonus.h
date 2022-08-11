/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:38:35 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/11 12:13:10 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include "../../libft/includes/libft.h"

typedef struct s_var
{
	char	*cmd_path;
	char	**cmd;
	int		**p;
	char	**paths;
	int		i;
	int		j;
	int		ac;
	int		fork_num;
	int		pipe_num;
	int		fd[2];
}	t_var;

void	free_2d(char **s);
void	ft_file(t_var *var);
void	ft_pid(pid_t pid, t_var *var);
void	close_all(t_var *var);
void	ft_check_env(t_var *var);
void	ft_check_cmd(t_var *var);
void	init_cmd(t_var *var, char *cmd);
void	init(t_var *var, char **av, char **env, int ac);
void	ft_check_path(t_var *var);
char	**ft_findpath(char **env);
char	*ft_path(t_var *var, char *av);
char	*ft_strjoin_custom(char const *s1,	char const *s2);
void	free_int(int **s,	int block);
void	mode_heredoc(char **av, char **env, int ac, t_var var);
void	normal_mode(char **av, char **env, int ac, t_var var);
void	ft_child1(t_var *var, char **env);
void	ft_child2(t_var *var, char **env);
void	ft_child_middle(t_var *var, char **env);
#endif
