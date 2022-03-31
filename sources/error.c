/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:15:20 by ldubuche          #+#    #+#             */
/*   Updated: 2022/03/31 16:57:00 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	__error(char *str)
{
	ft_printf("%s\n", str);
	return (2);
}

int	__free_error(char *str, t_data *pipex)
{
	if (pipex->pipe)
	{
		free(pipex->pipe);
		pipex->pipe = NULL;
	}
	close(pipex->pipe[1]);
	close(pipex->pipe[0]);
	close(pipex->fd1);
	close(pipex->fd2);
	return (__error(str));
}

void	__free_ok(t_data *pipex)
{
	if (pipex->pipe)
	{
		free(pipex->pipe);
		pipex->pipe = NULL;
	}
	close(pipex->pipe[1]);
	close(pipex->pipe[0]);
	close(pipex->fd1);
	close(pipex->fd2);
}

int	__free_parent(int id1, int id2, t_data *pipex)
{
	if (id1 != 0 && id2 != 0)
	{
		__free_ok(pipex);
		waitpid(id1, NULL, 0);
		waitpid(id2, NULL, 0);
	}
	return (0);
}