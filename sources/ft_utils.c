/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:06:10 by marvin            #+#    #+#             */
/*   Updated: 2021/08/16 13:06:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*string;
	unsigned int	i;

	if (!s1)
		return (NULL);
	if (!ft_strlen(s1) && !ft_strlen(s2))
		return (ft_strdup(""));
	string = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!string)
		return (NULL);
	ft_bzero(string, (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	while (*s1)
		string[i++] = *s1++;
	while (*s2)
		string[i++] = *s2++;
	return (string);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}

void	ft_putstr_fd(char *s, int fd)
{
	char	c;

	if (!s)
		return ;
	while (*s)
	{
		c = *s;
		write(fd, &c, 1);
		s++;
	}	
}

int	count_size(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**process_path(char *str, char *ag)
{
	int		i;
	char	**fpath;
	char	**temp;
	char	*suffix;

	suffix = ft_strjoin("/", ag);
	temp = ft_split(ft_strchr(str, '/'), ':');
	fpath = malloc(sizeof(char *) * (count_size(temp) + 1));
	i = 0;
	fpath[count_size(temp)] = '\0';
	while (temp[i])
	{
		fpath[i] = ft_strjoin(temp[i], suffix);
		free(temp[i]);
		i++;
	}
	free(temp);
	free(suffix);
	return (fpath);
}
