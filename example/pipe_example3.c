#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define READ	0
#define WRITE	1
#define pipe_ea	5
#define MAXLINE 4096 /* max line length */ 

int main(void)
{
    int n, fd[2];
    pid_t	pid;
	int		i;
    char line[MAXLINE];

	pipe(fd);
	i = 0;
	while (i < pipe_ea)
	{
		pid = fork();
		if (pid != 0)
			dup2(fd)

		i++;


	}
    if (pipe(fd) < 0)
	{
        printf("pipe error \n");
        return(-1);
    }
    if ((pid = fork()) < 0)
	{
        printf("fork error \n");
        return(-2);
    }
	else if (pid != 0)   // 부모
	{
        close(fd[0]);		// Read
        write(fd[1], "Hello world\n", 12);
    }
	else
	{ /* child */
        close(fd[1]);		// write
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
	while (1);
    return(0);
}
/* [1] fd[0] */

