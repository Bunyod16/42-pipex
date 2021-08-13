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


char *find_cmd(char *str)
{
	int i;
	char *ret;

	i = 0;
	while(str[i] != ' ' && str[i])
		i++;
	ret = malloc(sizeof(char) * i + 1);
	i = 0;
	while(str[i] != ' ' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char **assign_array(char **str)
{
	int i;
	char **ret;

	i = 0;
	while (str[i])
		i++;
	ret = malloc(sizeof(char) * i + 1);
	*ret[i] = 0;
	return(ret);
}

char **process_path(char *str, char **ag)
{
	int i;
	char **fpath;
	char **temp;
	char *suffix;
	char *cmd;

	cmd = find_cmd(ag[2]);
	suffix = ft_strjoin("/", cmd);
	free(cmd);
	temp = ft_split(ft_strchr(str, '/'), ':');
	i = 0;
	fpath = assign_array(temp);
	while(temp[i])
	{
		fpath[i] = ft_strdup(ft_strjoin(temp[i], suffix));
		free(temp[i]);
		i++;
	}
	free(temp);
	free(suffix);
	return (fpath);
}
