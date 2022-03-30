/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:52:31 by ldubuche          #+#    #+#             */
/*   Updated: 2022/03/30 12:11:37 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	pi[2];
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		printf("./pipex file1 cmd1 cmd2 file2\n");
		return (0);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY | O_TRUNC);
	if (fd1 == -1 || fd2 == -1)
	{
		printf("Fail during opening files\n");
		return (0);
	}
	pipe(pi);
	__time_to_fork(fd1, fd2, pi, envp, argv);
	return (0);
}

int	__time_to_fork(int fd1, int fd2, int pi[2], char *envp[], char *argv[])
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
		__child1(fd1, pi, envp, argv);
	else if (id2 == 0)
		__child2(fd2, pi, envp, argv);
	wait(&id1);
	wait(&id2);
	return (0);
}

int	__child1(int fd1, int pi[2], char *envp[], char *argv[])
{
	int		i;
	int		j;
	char	*line;
	char	*path;
	char	**cmds;
	char	**paths;

	i = 0;
	dup2(fd1, STDIN_FILENO);
	dup2(pi[1], STDOUT_FILENO);
	close (fd1);
	close(pi[1]);
	fprintf(stderr, "Child 1 here\n");
	cmds = __split(argv[2], ' ');
	while (envp[i] != NULL)
	{
		if (__strnstr(envp[i], "PATH", 4) != NULL)
		{
			line = __strdup(&(envp[i][5]));
			paths = __split(line, ':');
			free(line);
			j = 0;
			while (paths[j] != NULL)
			{
				line = __strjoin(paths[j], "/");
				path = __strjoin(line, cmds[0]);
				if (access(path, X_OK) == 0)
				{
					execve(path, cmds, envp);
					fprintf(stderr, "Commande found\n");
					return (0);
				}
				free (path);
				free (line);
				free (paths[j++]);
			}
			fprintf(stderr, "Commande not found\n");
		}
		i++;
	}
	return (0);
}

int	__child2(int fd2, int pi[2], char *envp[], char *argv[])
{
	int		i;
	int		j;
	char	*line;
	char	*path;
	char	**cmds;
	char	**paths;

	i = 0;
	dup2(pi[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	fprintf(stderr, "Child 2 here\n");
	close (fd2);
	close(pi[0]);
	cmds = __split(argv[3], ' ');
	while (envp[i] != NULL)
	{
		if (__strnstr(envp[i], "PATH", 4) != NULL)
		{
			line = __strdup(&(envp[i][5]));
			paths = __split(line, ':');
			free(line);
			j = 0;
			while (paths[j] != NULL)
			{
				line = __strjoin(paths[j], "/");
				path = __strjoin(line, cmds[0]);
				if (access(path, X_OK) == 0)
				{
					execve(path, cmds, envp);
					fprintf(stderr, "Commande found\n");
					return (0);
				}
				free (path);
				free (line);
				free (paths[j++]);
			}
			fprintf(stderr, "Commande not found\n");
		}
		i++;
	}
	return (0);
}
