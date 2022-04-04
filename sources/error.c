/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:15:20 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/04 13:59:00 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	__error(char *str, int err)
{
	fprintf(stderr, "%s\n", str);
	return (err);
}

int	__free_error(char *str, t_data *pipex)
{
	if (pipex->pipe[1] != -1)
		close(pipex->pipe[1]);
	if (pipex->pipe[0] != -1)
		close(pipex->pipe[0]);
	if (pipex->pipe)
	{
		free(pipex->pipe);
		pipex->pipe = NULL;
	}
	if (pipex->fd1 != -1)
		close(pipex->fd1);
	if (pipex->fd2 != -1)
		close(pipex->fd2);
	return (__error(str, pipex->ret));
}

void	__free_ok(t_data *pipex)
{
	if (pipex->pipe[1] != -1)
		close(pipex->pipe[1]);
	if (pipex->pipe[0] != -1)
		close(pipex->pipe[0]);
	if (pipex->pipe)
	{
		free(pipex->pipe);
		pipex->pipe = NULL;
	}
	if (pipex->fd1 != -1)
		close(pipex->fd1);
	if (pipex->fd2 != -1)
		close(pipex->fd2);
}

int	__free_parent(int id1, int id2, t_data *pipex)
{
	int	status;

	status = 0;
	if (id1 != 0 && id2 != 0)
	{
		__free_ok(pipex);
		waitpid (id1, &status, 0);
		if ((0 < waitpid (id2, &status, 0)) && (WIFEXITED (status)))
			return (WEXITSTATUS (status));
	}
	return (errno);
}

void	__free_split(char **split, int i)
{
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}
