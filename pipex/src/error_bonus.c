/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:52:33 by moabid            #+#    #+#             */
/*   Updated: 2022/05/26 16:56:13 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("\033[33mSyntax Error :\n./pipex infile cmd cmd outfile\n\
Or\n./pipex here_doc LIMITER cmd cmd outfile\033[0m", 2);
	exit(0);
}

void	error_file(char *file)
{
	ft_putstr_fd("\033[33mno such file or directory : ", 2);
	ft_putendl_fd(file, 2);
	exit(0);
}

void error_command(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("\033[33m: command not found\033[0m", 2);
	exit(0);
}
