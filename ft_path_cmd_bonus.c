/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:16:21 by sbourziq          #+#    #+#             */
/*   Updated: 2024/04/27 19:16:23 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen_space(char *av, char c)
{
	int	i;

	i = 0;
	while (av[i] != '\0' && av[i] != c)
		i++;
	return (i);
}

char	*ft_check_space(char *av, char c, t_alloc **gc)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (av[j] == c || av[j] == 9)
		j++;
	while (av[j] != '\0' && av[j] != c && av[j] != 9 && ++j > -1)
		i++;
	str = (char *)gc_malloc(gc, (i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '/';
	j = j - i;
	i = 1;
	while (av[j] != '\0' && av[j] != c && av[j] != 9)
	{
		str[i] = av[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(char *str, char *path, int line)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (i < line)
	{
		if (str[i] == path[i])
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_find_path(t_cmd *ptr, char **str, char **cmd, t_alloc **gc)
{
	int	i;

	i = 0;
	ptr->access_path = ft_helper_find_path(gc, ptr);
	if (ptr->access_path == NULL)
		return (0);
	while ((ptr->access_path)[i] != NULL)
	{
		(ptr->access_path)[i] = ft_strjoin(gc, (ptr->access_path)[i], *cmd);
		if (access((ptr->access_path)[i], F_OK) == 0)
		{
			if (access((ptr->access_path)[i], X_OK) == 0)
				*str = (ptr->access_path)[i];
			else
				ft_erorr_cmmd(ptr, i, gc);
		}
		i++;
	}
	return (1);
}

char	*ft_check_path(t_cmd *ptr, char *argv, t_alloc **gc)
{
	char	*cmd;
	int		i;
	char	*str;

	i = 0;
	ft_empty(argv);
	cmd = ft_check_space(argv, ' ', gc);
	if (cmd == NULL)
		return (NULL);
	str = NULL;
	if (ft_strchr(argv, '/') != NULL || argv[0] == '.')
		ft_access_to_path(gc, ptr, &str, argv);
	else
	{
		if (ft_find_path(ptr, &str, &cmd, gc) == 0)
		{
			if (access(argv, X_OK) == 0)
				str = argv;
		}
	}
	return (str);
}
