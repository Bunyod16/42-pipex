/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:29:54 by bshamsid          #+#    #+#             */
/*   Updated: 2021/08/12 17:21:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	count;
	size_t	length;

	count = 0;
	length = len;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (len-- > 0 && *haystack)
	{
		if (*haystack == *needle)
			if (ft_strncmp(needle, haystack, ft_strlen(needle)) == 0)
				if (count + ft_strlen(needle) <= length)
					return ((char *)haystack);
		count++;
		haystack++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	rep;

	rep = (char)c;
	while (*s != '\0')
	{
		if (*s == rep)
			return ((char *)s);
		s++;
	}
	if (*s == rep)
		return ((char *)s);
	return (NULL);
}
