/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:34:57 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/03 15:55:59 by rverhoev         ###   ########.fr       */
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

void	cleaning_buffer(char *line)
{
	free(line);
	line = (char *)NULL;
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
	//if (ft_strstr_chr(line, data->tokens.pipe_chrs) != NULL)
	//{
	//	printf("yes\n");
	//	data->tokens.pipex = TRUE;
	//}

	if (data->split_line[0][0] == '<')
		data->tokens.pipex = TRUE;
	else
		data->tokens.pipex = FALSE;


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

	if (data->tokens.pipex == FALSE)
	{
		pid_t p = fork();

		if (!p)
		{
		}
	}

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


char *get_env_paths(char **env)
{
	int		i;
	char	*ret_ptr;

	i = 0;
	ret_ptr = NULL;
	while(env[i])
	{
		ret_ptr = ft_strnstr(env[i], "PATH", 4);
		if (ret_ptr != NULL)
			return (&ret_ptr[5]);
		i++;
	}
}

#define YES 99

int	check_if_local(char *arg)
{

}

char	*check_env_path(char *arg, char **envp)
{
	int		i;
	char	*try_path;
	char	*command;
	char	**bin_paths;

	bin_paths = ft_split(get_env_paths(envp), ':');
	command = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	ft_strcpy(command, "/");
	ft_strcat(command, arg);
	i = 0;
	while (bin_paths[i] != NULL)
	{
		try_path = ft_strjoin(bin_paths[i], command);
		if (access(try_path, X_OK) == 0)
			return (try_path);
		i++;
		printf("%s\n", try_path);
		free(try_path);
		try_path = 0;
	}
	return (NULL);
}

char	*find_cmd_path(char *arg, char **envp)
{
	int		i;
	char	*path;
	char	*command;
	char	**bin_paths;
	
	//if (check_if_local(arg) == YES)



	return (check_env_path(arg, envp));
}


int	main(int argc, char **argv, char **envp)
{
	t_shell_data	data;
	(void)argv;
	(void)argc;

	char	*try_path = find_cmd_path(argv[1], envp);

	execve(try_path, &argv[1], envp);



	//set_minish_data(&data, envp);
	//print_welcome();
	//loop(&data);

	return (0);
}
