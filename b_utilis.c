/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utilis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:23:43 by hbakrim           #+#    #+#             */
/*   Updated: 2024/03/24 23:29:52 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile(char **av, t_pipex *pipex)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror("infile fail");
		exit(-1);
	}
	close(pipex->end[0]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->end[1]);
}

void	outfile(int ac, char **av, t_pipex *pipex)
{
	if (pipex->indixe == 2)
		pipex->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		pipex->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	close(pipex->end[0]);
	close(pipex->end[1]);
	if (pipex->outfile == -1)
	{
		perror("outfile fail");
		exit(-1);
	}
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
}

void	all_cmd(int ac, char **av, char **env, t_pipex *pipex)
{
	if (pipex->i == 2)
		infile(av, pipex);
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

void	handle_child_exit_status(int status)
{
	int	exit_status;

	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			exit(exit_status);
	}
	else
		exit(EXIT_SUCCESS);
}
