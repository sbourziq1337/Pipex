/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_erorre_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:17:04 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/27 19:17:09 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_erorr_infile(t_cmd *str, int i, t_alloc **gc)
{
	if ((access(str->av[1], F_OK)) == 0)
	{
		if ((access(str->av[i + 1], R_OK)) < 0)
		{
			perror(str->av[1]);
			(ft_lstclear(gc), exit(1));
		}
	}
	write(2, str->av[1], ft_strlen(str->av[1]));
	write(2, ": No such file or directory\n", 29);
	(ft_lstclear(gc), exit(1));
}

void	ft_erorr_outfiel(t_cmd *str, t_alloc **gc)
{
	perror(str->av[str->ac - 1]);
	(ft_lstclear(gc), exit(1));
}

void	ft_erorr_cmmd(t_cmd *ptr, int i, t_alloc **gc)
{
	perror((ptr->access_path)[i]);
	(ft_lstclear(gc), exit(126));
}

void	ft_empty(char *av)
{
	if (av[0] == '.' && av[1] == '\0')
	{
		write(2, ".: filename argument required\n", 31);
		write(2, ".: usage: . filename [arguments]\n", 34);
		exit(2);
	}
	if (av[0] == '\0')
		exit(0);
}

int	ft_strcmp(char *str, char *path)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != path[i])
			return (1);
		else if (str[i + 1] == '\0' && path[i + 1] == '\n')
			return (0);
		i++;
	}
	if (str[i] == path[i])
		return (0);
	return (1);
}
