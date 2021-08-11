#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

void child_call(int ac, char **ag, char **ep, int fd[2])
{
	char *argv[2] = {"-la", NULL};
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execve("/usr/bin/ls", argv, ep);
}

void parent_call(int ac, char **ag, char **ep, int fd[2])
{
	char *buf;

	printf("%ld", read(fd[0], buf, 10));
	printf("%s", buf);
}

int main(int ac, char **ag, char **ep)
{
	pid_t	pid;
	int		fd[2];
	int		*status;

	if (ac != 5)
	{
		ft_putstr_fd("Error: Need exactly 5 arguements!\n", 1);
		return (0);
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
    	child_call(ac, ag, ep, fd);
	else
	{
		waitpid(-1, NULL, 0);
		parent_call(ac, ag ,ep, fd);
	}
	close(fd[0]);
	close(fd[1]);
}