/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshamsid <bshamsid@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:12:18 by bshamsid          #+#    #+#             */
/*   Updated: 2021/08/17 01:45:48 by bshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include <stdio.h>

void	free_pp(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && *str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	child_call(int input_fd, char **ag, char **envp, int fd[2])
{
	char	**argv;
	char	**path;
	int		i;

	argv = ft_split(ag[2], ' ');
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path = process_path(envp[i], argv[0]);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(input_fd, 0);
	close(input_fd);
	i = -1;
	while (path[++i])
	{
		execve(path[i], argv, envp);
		free(path[i]);
	}
	free_pp(argv);
	free(path);
	exit(0);
}

static void	child_call2(int output_fd, char **ag, char **envp, int fd[2])
{
	char	**argv;
	char	**path;
	int		i;

	argv = ft_split(ag[3], ' ');
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	close(fd[1]);
	path = process_path(envp[i], argv[0]);
	dup2(fd[0], 0);
	dup2(output_fd, 1);
	close(fd[0]);
	i = -1;
	while (path[++i])
	{
		execve(path[i], argv, envp);
		free(path[i]);
	}
	free_pp(argv);
	free(path);
	exit(0);
}

void	pipex(char **argv, char **envp)
{
	pid_t		pid;
	int			pipe_end[2];
	const int	fd1 = open(argv[1], O_RDONLY);
	const int	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);

	if (fd1 < 0 || fd2 < 0)
		perror("Error reading file");
	pipe(pipe_end);
	pid = fork();
	if (pid == -1)
		perror("Could not fork\n");
	else if (pid == 0)
		child_call(fd1, argv, envp, pipe_end);
	pid = fork();
	if (pid == -1)
		perror("Could not fork\n");
	else if (pid == 0)
		child_call2(fd2, argv, envp, pipe_end);
	close(pipe_end[1]);
	close(pipe_end[0]);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putstr_fd("Need exactly 5 arguements!\n", 1);
		return (-1);
	}
	if (check_acess(envp, argv) == 0)
		return (-1);
	if (!check_commands(envp, argv, get_fa(argv[2]))
		|| !check_commands(envp, argv, get_fa(argv[3])))
		return (-1);
	pipex(argv, envp);
	return (0);
}
