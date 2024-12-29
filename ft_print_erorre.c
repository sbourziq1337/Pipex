/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_erorre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:04:42 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/23 17:04:45 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_erorr_infile(t_cmd *str, int i, t_alloc **gc)
{
	if ((access(str->av[1], F_OK)) == 0)
	{
		if ((access(str->av[i + 1], R_OK)) < 0)
		{
			write(2, str->av[1], ft_strlen(str->av[1]));
			write(2, ": Permission denied\n", 21);
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
