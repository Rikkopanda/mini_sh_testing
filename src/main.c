/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:34:57 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/03 13:10:45 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// void set_color(const char color[])
// {
// 	printf(color);
// }

int g_signal;

void action(int signum)
{
	g_signal = signum;
	printf("hello signal %d\n",  signum);
	exit(0);
}

void	cleaning_buffer(char *line)
{
	free(line);
	line = (char *)NULL;
}

void test_sigaction_kill()
{
	struct sigaction sa;

	sa.sa_handler = action;
	sigaction(SIGTERM, &sa, NULL);
	pid_t p = fork();

	if (!p)
	{
		printf("child made\n");
		while (1);
		//also manually:
		//ps ax | grep exe
		//kill -s USR1 <pid>
	}
	usleep(2000 * 1000);
	kill(p, SIGUSR1);
	waitpid(p, NULL, 0);
	printf("%d has exit\n", p);
}

void print_welcome()
{
	printf(COLOUR_GREEN);
	printf("****************\n");
	printf(COLOUR_END);
	printf("WELCOME TO MINISHELL\n");
	printf(COLOUR_GREEN);
	printf("****************\n");
	printf(COLOUR_END);
}

int	test_path(int argc, char **argv, char **envp)
{
	if (argc != 2)
		return (printf("2 arguments needed\n"), 0);
	printf("%s\n", argv[1]);
	printf("%s\n", envp[0]);
	pid_t p = fork();
	char	path[200000];

	strcpy(path, "/bin/");
	if (!p)
	{
		execve(strcat(path, argv[1]), &argv[1], envp);
	}
	return (0);
}


/*
	format piping:
	< [infile] [CMD + args] > [outfile] 
	< [infile] [CMD+ args] > [outfile] 
	< [infile] [CMD + args] (goes to stdout)
	
	[CMD + args] > out
	[CMD + args] (goes to stdout)
*/

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

void init_tokens(t_shell_data *data)
{
	ft_strcpy(data->tokens.pipe, "|");
	ft_strcpy(data->tokens.direct_in, "<");
	ft_strcpy(data->tokens.direct_out, ">");
	ft_strcpy(data->tokens.heredoc, "<<");
	ft_strcpy(data->tokens.append, ">>");
	ft_strcpy(data->tokens.pipe_chrs, "<>|");
	data->tokens.pipex = FALSE;
}

/*
	use pipex in orignal format,
	so parse with >, <, <<, etc and put in pipex format?
	_______________
	check if format is correct? > < >> << etc..
*/
static int	parsing_line(t_shell_data *data, char	*line)
{
	if (ft_strstr_chr(line, data->tokens.pipe_chrs) != NULL)
	{
		printf("yes\n");
		data->tokens.pipex = TRUE;
	}
	return (0);
}

static int	init_line(t_shell_data *data, char	*line)
{
	int		i;

	data->split_line = ft_split(line, ' ');
	i = 0;
	while (data->split_line[i] != NULL)
	{
		//printf("%s\n", split_args[i]);
		i++;
	}
	data->argc = i;
	printf("%d\n", i);
	return (0);
}

static int	interpret_line(t_shell_data *data, char	*line)
{
	if (ft_strcmp(line, (char *)"exit") == 0)
	{
		cleaning_buffer(line);
		exit(0);
	}
	init_line(data, line);
	parsing_line(data, line);
	if (data->tokens.pipex == TRUE)
		piping(data->argc, data->split_line, data->envp);
	/*
		piping should cleanly exit on succes and fail.
		also perhaps a usefull status value set somewhere
	*/
	free_double_array((void **)data->split_line);
	cleaning_buffer(line);
	return (0);
}

void	set_minish_data(t_shell_data *data, char **envp)
{
	data->envp = envp;
	init_tokens(data);
}

int	loop(t_shell_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		interpret_line(data, line);
	}
	return (0);
}
// rl_redisplay();
// rl_on_new_line();

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	data;
	(void)argv;
	(void)argc;


	set_minish_data(&data, envp);
	print_welcome();
	loop(&data);

	return (0);
}
