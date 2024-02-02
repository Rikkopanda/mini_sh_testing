/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:34:57 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/02 18:49:33 by rverhoev         ###   ########.fr       */
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

static int	interpret_line(char	*line)
{
	if (ft_strcmp(line, (char *)"exit") == 0)
	{
		cleaning_buffer(line);
		exit(0);
	}
	

	cleaning_buffer(line);
}

int	loop()
{
	char	*line;

	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		interpret_line(line);
		printf("%p %p\n", line, rl_line_buffer);
	}
	return (0);
}
// rl_redisplay();
// rl_on_new_line();

int	main(int argc, char **argv, char **envp)
{
	print_welcome();
	loop();

	return (0);
}
