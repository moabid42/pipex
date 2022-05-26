/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:53:10 by moabid            #+#    #+#             */
/*   Updated: 2022/05/26 16:54:05 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*parser(char *cmd, char *paths)
{
	char	*with_slash;
	char	*l_path;
	char	*path;
	
	with_slash = ft_strrchr(cmd, '/');
	if (with_slash)
	{
		path = ft_strjoin(paths, with_slash);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	else
	{
		l_path = ft_strjoin(paths, "/");
		path = ft_strjoin(l_path, cmd);
		free(l_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	free(path);
	return (0);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	
	i = 0;
	while(ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
		
	paths = ft_split(env[i] + 5,':');
	i = 0;
	while(paths[i])
	{
		path = parser(cmd, paths[i]);
		if (path)
			return (path);	
		i++;
	}
	error_command(cmd);
	freeme(paths);
	return (FALSE);
}