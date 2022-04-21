/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:25:08 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/21 11:18:11 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data_b	pipex;	

	pipex = (t_data_b){-1, -1, argc, argc - 3, 2 * (argc - 4), 0, 0, -1, 0, \
	NULL, argv, envp, NULL, NULL, NULL, NULL, NULL, NULL};
	if (argc < 5)
		return (__error("./pipex file1 cmd1 cmd2 file2", &pipex));
	__get_file(&pipex);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nbr);
	if (!pipex.pipe)
		return (__error("Pipe allocation error", &pipex));
	pipex.env_path = __path(&pipex);
	if (pipex.env_path != NULL)
	{
		pipex.cmd_paths = __split(pipex.env_path, ':');
		if (pipex.cmd_paths == NULL)
			return (__error("Split fail", &pipex));
	}
	__pipe_time(&pipex);
	while (++(pipex.i) < pipex.cmd_nbr)
		__child_bonus(pipex);
	__close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	__free_close(&pipex);
	return (0);
}

int	__get_file(t_data_b *pipex)
{
	if (__strncmp(pipex->argv[1], "here_doc", 9) == 0)
	{
		__here_doc(pipex);
		pipex->fd2 = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_CREAT \
		| O_APPEND, 0000644);
		if (pipex->fd2 == -1)
			return (__error(strerror(errno), pipex));
	}
	else
	{
		pipex->fd1 = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd1 == -1)
			return (__error(strerror(errno), pipex));
		pipex->fd2 = open(pipex->argv[pipex->argc - 1], O_CREAT | O_RDWR \
		| O_TRUNC, 0000644);
		if (pipex->fd2 == -1)
			return (__error(strerror(errno), pipex));
	}
	return (0);
}

char	*__path(t_data_b *pipex)
{
	int	i;

	i = 0;
	while (pipex->envp[i] != NULL)
	{
		if (__strnstr(pipex->envp[i], "PATH", 4) != NULL)
			return (pipex->envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	__pipe_time(t_data_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipe + (2 * i)) < 0)
			__error("Pipe process fail", pipex);
		i++;
	}
}
