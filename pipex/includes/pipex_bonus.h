/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:19:24 by moabid            #+#    #+#             */
/*   Updated: 2022/05/26 17:12:15 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define FALSE	0
# define TRUE	1

void	freeme(char **paths);
int		openfile(char *file, int re_or_wr);

void	executeme(char *cmd, char **env);
void	childprocess(char *cmd, char **env);
void	execute_heredoc(char **argv, int *pfd);
void	handle_heredoc(int ac, char **av);

char	*parser(char *cmd, char *paths);
char	*get_path(char *cmd, char **env);

void	error_file(char *file);
void	error(int n_exit);
void	error_command(char *cmd);





#endif