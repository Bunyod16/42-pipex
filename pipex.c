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

static void child_call(int input_fd, char **ag, char **envp, int fd[2], char **path)
{
	char **argv; (const char **) ft_split(ag[2], ' ');
	int i;
	char **dup_env;

	argv = ft_split(ag[2], ' ');
	i = 0;
	while(!ft_strnstr(envp[i] ,"PATH", 4))
		i++;
	path = process_path(envp[i], ag);
	i = 0;
	printf("%s\n",path[0]);
	printf("%d\n",i);
	while (path[i]);
	{
		printf("PRINTING %d\n",i);
		printf("%s\n",path[i++]);
	}
	// dup2(fd[1], fileno(stdout));
	// dup2(input_fd, fileno(stdin));
	char *tda[4][10] = {"ls","-la",NULL};
	i = -1;
	while (path[++i]);
	{
		execve(path[i], *tda, envp);
	}
	free_pp(path);
	exit(0);
}

static void parent_call(int fd2, char **ag, char **ep, int fd[2])
{
	char buf[100];
	// dup2(fd2, fileno(stdout));
	// write(fd2, , 3);

	// wait(0);
	// read(fd[0], buf, 10);
	// write(fd2, buf, 10);
	// close(fd[1]);
	// close(fd[0]);
	exit(0);
}

int pipex(int fd1, int fd2, char **argv, char **envp)
{
	pid_t	pid;
	int		pipe_end[2];
	int		i;
	char	**path;

	pipe(pipe_end);
	pid = fork();
	if (pid == -1)
		perror("Could not fork");
	else if (pid == 0)
    	child_call(fd1, argv, envp, pipe_end, path);
	else
		parent_call(fd2, argv ,envp, pipe_end);
	printf("returned\n");
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
         return (-1);
    pipex(fd1, fd2, argv, envp);
    return (0);
}