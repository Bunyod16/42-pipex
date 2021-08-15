#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

void		free_pp(char **str)
{
	unsigned int i;

	i = 0;
	while (str[i] && *str[i])
	{
	    if (*str[i] == '/')
	        free(str[i]);
		i++;
	}
}

static void child_call(int input_fd, char **ag, char **envp, int fd[2])
{
	char	**argv;
	char	**path;
	int		i;

	argv = ft_split(ag[2], ' ');
	i = 0;
	while(!ft_strnstr(envp[i] ,"PATH", 4))
		i++;
	path = process_path(envp[i], argv[0]);
	close(fd[0]);
	dup2(fd[1], fileno(stdout));
	close(fd[1]);
	dup2(input_fd, fileno(stdin));
	close(input_fd);
	i = -1;
	while (path[++i])
	{
		execve(path[i], argv, envp);
		free(path[i]);
	}
	free_pp(argv);
	free(path);
}

static void child_call2(int output_fd, char **ag, char **envp, int fd[2])
{
	char	**argv;
	char	**path;
	int		i;

	argv = ft_split(ag[3], ' ');
	i = 0;
	while(!ft_strnstr(envp[i] ,"PATH", 4))
		i++;
	close(fd[1]);
	path = process_path(envp[i], argv[0]);
	dup2(fd[0], fileno(stdin));
	dup2(output_fd, fileno(stdout));
	close(fd[0]);
	i = -1;
	printf("PATH:%s\n",path[0]);
	while (path[++i])
	{
		execve(path[i], argv, envp);
		free(path[i]);
	}
	free_pp(argv);
	free(path);
}

int pipex(int fd1, int fd2, char **argv, char **envp)
{
	pid_t	pid;
	int		pipe_end[2];

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

int main(int argc, char **argv, char **envp)
{
    const int fd1 = open(argv[1], O_RDONLY);
    const int fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    
	if (argc != 5)
	{
		ft_putstr_fd("Need exactly 5 arguements!", 1);
		return (-1);
	}
	if (fd1 < 0 || fd2 < 0)
         perror("Error reading file");
    pipex(fd1, fd2, argv, envp);
    return (0);
}