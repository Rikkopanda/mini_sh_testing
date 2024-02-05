/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:04:52 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/05 14:41:55 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define COLOUR_GREEN "\033[0;32m"
#define COLOUR_PURPLE "\033[0;35m"
#define COLOUR_END "\033[0m"
#define COLOUR_BLUE "\033[0;34m"
#define COLOUR_LIGHT_BLUE "\033[1;34"
#define COLOUR_CYAN "\033[0;36"
#define COLOUR_LIGHT_CYAN "\033[1;36"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../pipex/pipex_src/pipex.h"
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define FALSE 0
#define TRUE 1

typedef int bool;


typedef struct s_symbols
{
	char	pipe[2];
	char	direct_in[2];
	char	direct_out[2];
	char	heredoc[3];
	char	append[3];
	char	pipe_chrs[4];
} t_symbols;

typedef struct s_sections
{
	char 	**content;
	bool	cmd;
	bool	infile;
	bool	outfile;
	bool	last_outfile;
	next;
} t_sections;
// content includes arguments

typedef struct s_shell_data
{
	bool		pipex;
	bool		heredoc;
	int			argc;
	t_sections	*sections;
	char		**split_line;
	char		**envp;
	t_symbols	symbols;
} t_shell_data;

int		parse(t_shell_data *data, char	*line);
char	*find_cmd_path(char *arg, char **envp);
void	launch(t_shell_data *data);
void	clearing(t_shell_data *data, char	*line);

#endif