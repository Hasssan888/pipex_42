/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:28:19 by hbakrim           #+#    #+#             */
/*   Updated: 2024/02/28 16:28:21 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_pipex
{
	int		end[2];
	int		status;
	int		status_1;
	int		i;
	int		indixe;
	int		outfile;
	int		infile;
	int		infile_here_doc;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	a[2];
	char	*line;
	pid_t	pid;
	int		fd;
	int		save1;
	pid_t	r;
}			t_pipex;

typedef struct s_path
{
	char	*path_from_envp;
	char	**mypaths;
	char	*part_path;
	char	*path;
	int		i;
}			t_path;

// b_utilis.c
void		outfile(int ac, char **av, t_pipex *pipex);
void		infile(char **av, t_pipex *pipex);
void		all_cmd(int ac, char **av, char **env, t_pipex *pipex);
void		handle_child_exit_status(int status);

// b_utilis_2.c
void		all_cmd_here_doc(int ac, char **av, char **env, t_pipex *pipex);
void		infile_here_doc(t_pipex *pipex);
void		ft_norm_1(int ac, char **av, t_pipex *pipex);
void		ft_normi_2(t_pipex *pipex);

// error.c
void		ft_error(char *av);
void		ft_error_2(void);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);

// split.c
char		**ft_split(char const *s, char c);

// utilis
size_t		ft_strlen(const char *str);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strdup(const char *str);
char		*ft_substr(const char *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// pipex_utilis.c
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_excute(char *av, char **env);
char		*function(char **env);
char		*search_path(char *mycmdargs, char **env);

// pipex.c
void		child_process_1(char **av, char **env, t_pipex *pipex);
void		child_process_2(char **av, char **env, t_pipex *pipex);
pid_t		pid_one(char **av, char **env, t_pipex *pipex);
pid_t		pid_two(char **av, char **env, t_pipex *pipex);

// pipex_bonus.c
void		here_doc(int ac, char **av, t_pipex *pipex);
pid_t		fork_pipe(int ac, char **av, char **env, t_pipex *pipex);

// get_next_line,.c

char		*get_next_line(int fd);

#endif
