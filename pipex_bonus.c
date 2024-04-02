/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:30:12 by hbakrim           #+#    #+#             */
/*   Updated: 2024/03/31 01:15:39 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	fork_pipe(int ac, char **av, char **env, t_pipex *pipex)
{
	int	pid;

	if (pipe(pipex->end) == -1)
		ft_error_2();
	pid = fork();
	if (pid == -1)
		ft_error_2();
	else if (pid == 0)
	{
		if (pipex->indixe == 2)
			all_cmd(ac, av, env, pipex);
		else if (pipex->indixe == 3)
			all_cmd_here_doc(ac, av, env, pipex);
	}
	close(pipex->end[1]);
	dup2(pipex->end[0], STDIN_FILENO);
	close(pipex->end[0]);
	return (pid);
}

void	here_doc_error(char **av)
{
	ft_putstr_fd("\nbash: warning: here-document at line \
	1 delimited by end-of-file wanted ", 2);
	ft_putstr_fd(av[2], 2);
	write(2, "\n", 1);
	exit(0);
	unlink("file_here_doc.txt");
}

void	here_doc(int ac, char **av, t_pipex *pipex)
{
	char	*str;

	if (ac < 6)
	{
		ft_putstr_fd("Ex: ./pipex \"here_doc\" <LIMITER> <cmd1> ... <file>\n",
			1);
		exit(0);
	}
	pipex->line = get_next_line(0);
	pipex->fd = open("file_here_doc.txt", O_RDWR | O_CREAT, 0644);
	str = ft_strjoin(av[2], "\n");
	if (pipex->line[0] == '\0')
		here_doc_error(av);
	while (pipex->line != NULL && ft_strcmp(pipex->line, str) != 0)
	{
		write(pipex->fd, pipex->line, ft_strlen(pipex->line));
		write(1, "heredoc> ", 9);
		free(pipex->line);
		pipex->line = get_next_line(0);
		if (pipex->line[0] == '\0')
			here_doc_error(av);
	}
	free(pipex->line);
	free(str);
}

int	main(int ac, char **av, char **en)
{
	t_pipex	pipex;

	pipex.save1 = dup(STDIN_FILENO);
	if (ac >= 5)
	{
		if (ft_strcmp(av[1], "here_doc") == 0)
			ft_norm_1(ac, av, &pipex);
		else
		{
			pipex.i = 2;
			pipex.indixe = 2;
		}
		while (pipex.i < ac - 1)
		{
			pipex.r = fork_pipe(ac, av, en, &pipex);
			if (ft_strcmp(av[pipex.indixe], "cat") != 0)
				waitpid(pipex.r, &pipex.status_1, 0);
			pipex.i++;
		}
		ft_normi_2(&pipex);
		handle_child_exit_status(pipex.status_1);
		unlink("file_here_doc.txt");
	}
	else
		ft_putstr_fd("Ex: ./P_bonus <file1> <cmd1> ... <file2>\n", 1);
}
