/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:52:07 by moabid            #+#    #+#             */
/*   Updated: 2022/05/26 16:55:56 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	openfile(char *file, int re_or_wr)
{
	int	ret;

	if (re_or_wr == 0)
	{
		ret = open(file, O_RDONLY, 0777);
		if (access(file, F_OK | R_OK) != 0)
			error_file(file);
	}
	if (re_or_wr == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (re_or_wr == 2)
		ret = open(file , O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	freeme(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

