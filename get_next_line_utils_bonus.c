/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbourziq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:00:34 by sbourziq          #+#    #+#             */
/*   Updated: 2023/12/06 21:00:36 by sbourziq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_checkline(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

ssize_t	ft_strlen1(char *s)
{
	ssize_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_substr1(char *s, int start, int end)
{
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	res = (char *)malloc(end - start + 1);
	if (!res)
		return (0);
	i = 0;
	while (start < end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_substr1(s2, 0, ft_strlen1(s2)));
	else
	{
		result = (char *)malloc(ft_strlen1(s2) + ft_strlen1(s1) + 1);
		if (!result)
			return (0);
		i = -1;
		while (s1[++i])
			result[i] = s1[i];
		j = 0;
		while (s2[j])
			result[i++] = s2[j++];
		result[i] = '\0';
		return (result);
	}
}
