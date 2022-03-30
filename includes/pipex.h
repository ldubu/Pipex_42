/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:46:03 by ldubuche          #+#    #+#             */
/*   Updated: 2022/03/30 12:01:28 by ldubuche         ###   ########.fr       */
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

int	__time_to_fork(int fd1, int fd2, int pi[2], char *envp[], char *argv[]);
int	__child1(int fd1, int pi[2], char *envp[], char *argv[]);
int	__child2(int fd2, int pi[2], char *envp[], char *argv[]);

#endif
