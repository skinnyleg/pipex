/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:11:20 by hmoubal           #+#    #+#             */
/*   Updated: 2021/11/07 13:40:09 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst,	void (*del)(void *))
{
	t_list	*p;
	t_list	*m;

	p = *lst;
	if (!lst || !del)
		return ;
	while (p->next != NULL)
	{
		m = p->next;
		del(p->content);
		free(p);
		p = m;
	}
	del(p->content);
	free(p);
	*lst = NULL;
}
