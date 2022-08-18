/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 06:29:15 by moabid            #+#    #+#             */
/*   Updated: 2022/05/26 18:26:45 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	executeme(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (path == FALSE)
		exit(EXIT_FAILURE);
	if (execve(path, s_cmd, env) == -1)
	{
		error_command(s_cmd[0]);
		freeme(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void	childprocess(char *cmd, char **env)
{
	pid_t	pid;
	int		pfd[2];

	if (pipe(pfd) == -1)
		error(1);
	pid = fork();
	if (pid == -1)
		error(1);
	if (!pid)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		executeme(cmd, env);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

void	execute_heredoc(char **argv, int *pfd)
{
	char	*line;
	close(pfd[0]);
	while (1)
	{
		write(1, "\033[31mEvilPipex 👻> ", 23);
		write(1, "\033[0m", 5);
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pfd[1]);
		free(line);
	}
}

void	handle_heredoc(int ac, char **av)
{
	pid_t	pid;
	int		pfd[2];

	if (ac < 6)
		error(1);
	if (pipe(pfd) == -1)
		error(1);
	pid = fork();
	if (pid == -1)
		error(1);
	if (!pid)
		execute_heredoc(av, pfd);
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (ac < 5)
		error(1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i = 3;
		fd_out = openfile(av[ac - 1], 2);
		handle_heredoc(ac, av);
	}
	else
	{
		i = 2;
		fd_in = openfile(av[1], 0);
		fd_out = openfile(av[ac - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < ac - 2)
		childprocess(av[i++], env);
	dup2(fd_out, 1);
	executeme(av[ac - 2], env);
}
