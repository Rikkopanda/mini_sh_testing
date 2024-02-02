/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:34:57 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/02 12:20:39 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define COLOUR_GREEN "\033[0;32m"
#define COLOUR_PURPLE "\033[0;35m"
#define COLOUR_END "\033[0m"
#define COLOUR_BLUE "\033[0;34"
#define COLOUR_LIGHT_BLUE "\033[1;34"
#define COLOUR_CYAN "\033[0;36"
#define COLOUR_LIGHT_CYAN "\033[1;36"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

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


void action(int signum)
{
	printf("hello signal %d\n",  signum);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	// set_color(COLOUR_GREEN);
	printf(COLOUR_PURPLE);
	printf("Hello\n");
	printf(COLOUR_END);
	printf("Hello, just testing functions\n");

	{
		char *line;

		line = readline("Enter something: ");
		if (line)
			add_history(line);
		free(line),
		line = (char *)NULL;
		line = readline("Enter something: ");
		printf("%s\n", rl_line_buffer);
		// rl_redisplay();
		// rl_on_new_line();
		free(line);
		line = (char *)NULL;
	}
	{
		struct sigaction sa;

		sa.sa_handler = action;
		sigaction(SIGUSR1, &sa, NULL);
		while (1);
		//ps ax | grep exe
		//kill -s USR1 <pid>
	}

	return (0);
}
