/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:20:55 by sbourziq          #+#    #+#             */
/*   Updated: 2024/05/04 19:20:57 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exit2(t_alloc **gc, t_cmd *str)
{
	ft_lstclear(gc);
	if (open(str->av[str->ac - 2], O_DIRECTORY) != -1)
	{
		write(2, str->av[str->ac - 2], ft_strlen(str->av[str->ac - 2]));
		write(2, ": is a directory\n", 18);
	}
	else
		perror("");
	(ft_lstclear(gc), exit(126));
}

void	ft_exit1(t_alloc **gc, t_cmd *str, int i)
{
	ft_lstclear(gc);
	if (open(str->av[i + 1], O_DIRECTORY) != -1)
	{
		write(2, str->av[i + 1], ft_strlen(str->av[i + 1]));
		write(2, ": is a directory\n", 18);
	}
	else
		perror("");
	(ft_lstclear(gc), exit(126));
}

char	**ft_helper_find_path(t_alloc **gc, t_cmd *ptr)
{
	while (*(ptr->env))
	{
		if (ft_strncmp(*(ptr->env), "PATH=", 5) == 0)
		{
			ptr->access_path = ft_split((*(ptr->env) + 5), ':', gc);
			break ;
		}
		(ptr->env)++;
	}
	return (ptr->access_path);
}

void	ft_access_to_path(t_alloc **gc, t_cmd *ptr, char **str, char *argv)
{
	ptr->access_path = ft_split(argv, ' ', gc);
	if (access((ptr->access_path)[0], F_OK) == 0)
	{
		if (access((ptr->access_path)[0], X_OK) == 0)
			*str = (ptr->access_path)[0];
		else
			ft_erorr_cmmd(ptr, 0, gc);
	}
}
