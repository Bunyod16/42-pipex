/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshamsid <bshamsid@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:12:05 by bshamsid          #+#    #+#             */
/*   Updated: 2021/08/16 15:22:54 by bshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_fa(char *argv)
{
	char	**split;
	char	*ret;

	split = ft_split(argv, ' ');
	ret = ft_strjoin("/", split[0]);
	free_pp(split);
	return (ret);
}

char	**split_path(char **envp)
{
	int		i;
	char	**ret;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	ret = ft_split(envp[i] + 5, ':');
	return (ret);
}

int	check_commands(char **envp, char **argv, char *cmd)
{
	char	*subpath;
	char	**paths;
	int		i;
	int		ok;

	paths = split_path(envp);
	ok = 0;
	i = -1;
	while (paths[++i])
	{
		subpath = ft_strjoin(paths[i], cmd);
		if (access(subpath, F_OK) == 0)
			ok += 1;
		free(subpath);
	}
	free_pp(paths);
	free(cmd);
	if (ok > 0)
		return (1);
	ft_putstr_fd("Error: no such command\n", 2);
	return (0);
}

int	check_acess(char **envp, char **argv)
{
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	while (!ft_strnstr(envp[i], "PWD", 3))
		i++;
	temp = ft_strjoin("/", argv[1]);
	path = ft_strjoin(envp[i] + 4, temp);
	free(temp);
	i = 0;
	if (access(path, F_OK) == -1)
		ft_putstr_fd("No such file or directory\n", 2);
	else
		i = 1;
	free(path);
	return (i);
}
