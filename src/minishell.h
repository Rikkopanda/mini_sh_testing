/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:04:52 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/03 15:21:10 by rverhoev         ###   ########.fr       */
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


typedef struct s_tokens
{
	char	pipe[2];
	char	direct_in[2];
	char	direct_out[2];
	char	heredoc[3];
	char	append[3];
	char	pipe_chrs[4];
	bool	pipex;
} t_tokens;

typedef struct s_shell_data
{
	int			argc;
	char		**split_line;
	char		**envp;
	t_tokens	tokens;
} t_shell_data;



char *get_env_paths(char **env);


#endif