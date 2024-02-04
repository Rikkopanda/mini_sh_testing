/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:34:57 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/04 19:06:20 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

void action(int signum)
{
	g_signal = signum;
	printf("hello signal %d\n",  signum);
	exit(0);
}

//void test_sigaction_kill()
//{
//	struct sigaction sa;

//	sa.sa_handler = action;
//	sigaction(SIGTERM, &sa, NULL);
//	pid_t p = fork();

//	if (!p)
//	{
//		printf("child made\n");
//		while (1);
//		//also manually:
//		//ps ax | grep exe
//		//kill -s USR1 <pid>
//	}
//	usleep(2000 * 1000);
//	kill(p, SIGUSR1);
//	waitpid(p, NULL, 0);
//	printf("%d has exit\n", p);
//}

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

/*
	format piping:
	< [infile] [CMD + args] > [outfile] 
	< [infile] [CMD+ args] > [outfile] 
	< [infile] [CMD + args] (goes to stdout)
	
	[CMD + args] > out
	[CMD + args] (goes to stdout)
*/
void init_symbols(t_shell_data *data)
{
	ft_strcpy(data->symbols.pipe, "|");
	ft_strcpy(data->symbols.direct_in, "<");
	ft_strcpy(data->symbols.direct_out, ">");
	ft_strcpy(data->symbols.heredoc, "<<");
	ft_strcpy(data->symbols.append, ">>");
	ft_strcpy(data->symbols.pipe_chrs, "<>|");
}
void	set_minish_data(t_shell_data *data, char **envp)
{
	data->envp = envp;
	init_symbols(data);
}

void	clearing(t_shell_data *data, char	*line)
{
	free_double_array((void **)data->split_line);
	free(line);
	line = (char *)NULL;
}

int	loop(t_shell_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		parse(data, line);
		launch(data);
		clearing(data, line);
	}
	return (0);
}

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
