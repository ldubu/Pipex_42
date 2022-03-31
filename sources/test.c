/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:27:52 by ldubuche          #+#    #+#             */
/*   Updated: 2022/03/31 13:36:35 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	pipex;

	if (argc != 5)
	{
		printf("./pipex file1 cmd1 cmd2 file2\n");
		return (0);
	}
	pipex = (t_data){open(argv[1], O_RDONLY), open(argv[4], O_WRONLY | O_TRUNC) \
	, argv, argc, envp, NULL, NULL, NULL};
	pipex.pipe = (int *) malloc(sizeof(int) * 2);
	if (pipex.fd1 == -1 || pipex.fd2 == -1)
	{
		printf("Fail during opening files\n");
		return (0);
	}
	pipe(pipex.pipe);
	__time_to_fork(&pipex);
	fprintf(stderr, "Some proof that processes succeed\n");
	return (0);
}

int	__time_to_fork(t_data *pipex)
{
	int		id1;
	int		id2;

	id2 = -1;
	id1 = fork();
	if (id1 != 0)
	{
		id2 = fork();
	}
	if (id1 == 0)
		__child1(pipex);
	else if (id2 == 0)
		__child2(pipex);
	wait(&id1);
	wait(&id2);
	return (0);
}

int	__child1(t_data *pipex)
{
	int		i;

	i = 0;
	fprintf(stderr, "Child 1 here\n");
	dup2(pipex->fd1, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->fd1);
	close(pipex->pipe[1]);
	if (write(1, "Samael BONJOUR", 15) == -1)
		fprintf(stderr, "errno = %s\n", strerror(errno));
	return (0);
}

int	__child2(t_data *pipex)
{
	int		i;
	int		j;
	char	*buff = NULL;

	i = 0;
	buff = (char *) malloc(sizeof(char) * 13);
	fprintf(stderr, "Child 2 here\n");
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(pipex->fd2, STDOUT_FILENO);
	close(pipex->fd2);
	close(pipex->pipe[0]);
	j = read(0, buff, 12);
	fprintf(stderr, "j = %d\n", j);
	fprintf(stderr, "buff = %s\n", buff);
	fprintf(stderr, "errno = %s\n", strerror(errno));
	return (0);
}
