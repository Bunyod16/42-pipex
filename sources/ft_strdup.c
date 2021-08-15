/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 19:57:09 by bshamsid          #+#    #+#             */
/*   Updated: 2021/08/15 15:44:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*orig;

	orig = dst;
	if (!dst && !src)
		return (orig);
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (orig);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, ft_strlen(s1) + 1);
	return (ret);
}
