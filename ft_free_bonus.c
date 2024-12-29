/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:14:24 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/27 19:14:27 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_alloc	*ft_lstlast(t_alloc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_alloc	*ft_lstnew(void *ptr)
{
	t_alloc	*str;

	str = (t_alloc *)malloc(sizeof(t_alloc));
	if (str == NULL)
		return (NULL);
	str->data = ptr;
	str->next = NULL;
	return (str);
}

void	ft_lstadd_back(t_alloc **lst, t_alloc *new)
{
	t_alloc	*ptr;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			new->next = NULL;
			return ;
		}
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}

void	ft_lstclear(t_alloc **lst)
{
	t_alloc	*head;
	t_alloc	*copy;

	if (lst && *lst)
	{
		head = *lst;
		while (head != NULL)
		{
			copy = head;
			free(head->data);
			head = head->next;
			free(copy);
		}
		*lst = NULL;
	}
}

void	*gc_malloc(t_alloc **gc, int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_lstclear(gc);
		exit(1);
	}
	ft_lstadd_back(gc, ft_lstnew(ptr));
	return (ptr);
}
