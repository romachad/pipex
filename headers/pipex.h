/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:31:56 by romachad          #+#    #+#             */
/*   Updated: 2023/01/08 06:26:43 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct p_pipex
{
	char	*infile;
	char	*outfile;
	char	*cmd_str;
	char	**cmd_args;
	char	*fpath;
	int		*pid;
	int		*pipes;
	int		flag;
	int		argc;
	int		qtd_cmd;
	int		cmd_n;
	int		pipe_i;
}	t_pipex;

char	*path_search(char *envp[], const char *cmd);
char	**treat_str(char *str);
void	*free_char_array(char **array);
//void	close_pipes(int *pipe, t_pipex *args);
void	close_pipes(t_pipex *args);
int		create_pipes(t_pipex *args);
//int		child_prog(int *pipe, t_pipex *args, char **envp);
int		child_prog(t_pipex *args, char **envp);
int		free_args(t_pipex *args);
int		check_outfile(char *outfile);
int		check_infile(char *infile);

#endif
