/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:46:21 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/06 15:46:21 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	__bonus_free_error(char *str, t_data_b *pipex)
{
	int i;

	i = 2;
	while (i < (pipex->cmd_nbr - 1) * 2)
	{
		if (pipex->pipe[i] != -1)
			close(pipex->pipe[i]);
		i++;
	}
	if (pipex->fd1 != -1)
		close(pipex->fd1);
	if (pipex->fd2 != -1)
		close(pipex->fd2);
	return (__error(str, pipex->ret));
}

void	__bonus_free_ok(t_data_b *pipex)
{
	int i;

	i = 2;
	while (i < pipex->argc -1)
	{
		if (pipex->pipe[i] != -1)
			close(pipex->pipe[i]);
		i++;
	}
	if (pipex->fd1 != -1)
		close(pipex->fd1);
	if (pipex->fd2 != -1)
		close(pipex->fd2);
}
