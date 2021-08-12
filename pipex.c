#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

// void		free_pp(char **str)
// {
// 	free(str);
// }

static void child_call(int fd1, char **ag, char **envp, int fd[2], char **path)
{
	const char **argv = (const char **) ft_split(ag[2], ' ');
	int i;
	int ffd;

	dup2(fd[1], 1);
	dup2(fd1, 0);
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (path[i]);
	{
		execve(path[i], (char **) argv, envp);
		i++;
	}
}

static void parent_call(int fd2, char **ag, char **ep, int fd[2])
{
	char *buf;

	close(fd[1]);
	read(fd[0], &buf, 10);
	close(fd[0]);
	write(fd2, "hello", 6);
}

int pipex(int fd1, int fd2, char **argv, char **envp)
{
	pid_t	pid;
	int		pipe_end[2];
	int		i;
	char	**path;

	i = 0;
	while(!ft_strnstr(envp[i] ,"PATH", 4))
		i++;
	path = process_path(envp[i], argv);
	pipe(pipe_end);
	pid = fork();
	close(pipe_end[1]);
	close(pipe_end[0]);
	if (pid == -1)
		perror("Could not fork");
	else if (pid == 0)
    	child_call(fd1, argv, envp, pipe_end, path);
	else if (pid > 0)
		parent_call(fd2, argv ,envp, pipe_end);
	i = 0;
	while (path[i] && *path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
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
         return (-1);
    pipex(fd1, fd2, argv, envp);
    return (0);
}