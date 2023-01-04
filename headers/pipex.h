/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:31:56 by romachad          #+#    #+#             */
/*   Updated: 2023/01/04 03:18:24 by romachad         ###   ########.fr       */
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
	int		pid[2];
	int		flag;
}	t_pipex;

char	*path_search(char *envp[], const char *cmd);
void	*free_char_array(char **array);
void	treat_quotes(char *str);
void	add_space(char **str);
int		child_prog(int *pipe, t_pipex *args, char **envp);
int		free_args(t_pipex *args);
int		check_outfile(char *outfile);
int		check_infile(char *infile);

#endif
