/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:50:10 by hbakrim           #+#    #+#             */
/*   Updated: 2024/02/28 15:50:15 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(char **av, char **env, t_pipex *pipex)
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
	ft_excute(av[2], env);
}

void	child_process_2(char **av, char **env, t_pipex *pipex)
{
	pipex->outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror("outfile fail");
		exit(-1);
	}
	close(pipex->end[1]);
	dup2(pipex->end[0], STDIN_FILENO);
	close(pipex->end[0]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	ft_excute(av[3], env);
}

pid_t	pid_one(char **av, char **env, t_pipex *pipex)
{
	if (pipex->pid1 == -1)
		ft_error_2();
	else if (pipex->pid1 == 0)
		child_process_1(av, env, pipex);
	else if (pipex->pid1 != 0)
		return (pipex->pid1);
	return (0);
}

pid_t	pid_two(char **av, char **env, t_pipex *pipex)
{
	if (pipex->pid2 == -1)
		ft_error_2();
	else if (pipex->pid2 == 0)
		child_process_2(av, env, pipex);
	else if (pipex->pid2 != 0)
		return (pipex->pid2);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		status;

	pipex.a[0] = 0;
	pipex.a[1] = 0;
	if (ac == 5)
	{
		if (pipe(pipex.end) == -1)
			ft_error_2();
		pipex.pid1 = fork();
		pipex.a[0] = pid_one(av, env, &pipex);
		pipex.pid2 = fork();
		pipex.a[1] = pid_two(av, env, &pipex);
		close(pipex.end[0]);
		close(pipex.end[1]);
		waitpid(pipex.a[0], &status, 0);
		waitpid(pipex.a[1], &status, 0);
		handle_child_exit_status(status);
	}
	else
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	return (0);
}
