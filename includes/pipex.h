/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:46:03 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/01 10:51:27 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "struct.h"
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

int		__time_to_fork(t_data *pipex);
int		__child1(t_data *pipex);
int		__child2(t_data *pipex);
int		__cmd(t_data *pipex, int i);
int		__error(char *str, int err);
int		__free_error(char *str, t_data *pipex);
void	__free_ok(t_data *pipex);
int		__free_parent(int id1, int id2, t_data *pipex);

#endif
