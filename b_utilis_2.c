/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utilis_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:52:47 by hbakrim           #+#    #+#             */
/*   Updated: 2024/03/31 01:13:40 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_here_doc(t_pipex *pipex)
{
	if (pipex->fd == -1)
	{
		perror("infile fail");
		exit(-1);
	}
	close(pipex->end[0]);
	dup2(pipex->fd, STDIN_FILENO);
	close(pipex->fd);
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->end[1]);
}

void	all_cmd_here_doc(int ac, char **av, char **env, t_pipex *pipex)
{
	if (pipex->i == 3)
		infile_here_doc(pipex);
	else if (ac - 2 != pipex->i)
	{
		close(pipex->end[0]);
		dup2(pipex->end[1], STDOUT_FILENO);
		close(pipex->end[1]);
	}
	else
		outfile(ac, av, pipex);
	ft_excute(av[pipex->i], env);
}

void	ft_norm_1(int ac, char **av, t_pipex *pipex)
{
	pipex->i = 3;
	pipex->indixe = 3;
	write(1, "heredoc> ", 9);
	here_doc(ac, av, pipex);
}

void	ft_normi_2(t_pipex *pipex)
{
	while (pipex->i != -1)
		pipex->i = waitpid(pipex->r, &pipex->status_1, 0);
	dup2(pipex->save1, STDIN_FILENO);
	close(pipex->save1);
}
