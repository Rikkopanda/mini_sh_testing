/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:34:57 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/03 12:00:58 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// argv[1],argv[2],argv[3],argv[4], NULL	argc = 5
// < file | cmd1 | cmd2 > file2
// zelfde als(als shell command):
// < file cmd1 | cmd2 > file2 (vanwege <)

void	closing_parent_pipes_if(int *i, int *pipe_i, t_data *data)
{
	if (*pipe_i == 2)
		close((*data).pipe_array[*pipe_i - 1][READ]);
	else if (*pipe_i > 2 && *i != (*data).nbr_of_cmds)
		close_pipes((*data).pipe_array[*pipe_i - 1], 0);
	errno = 0;
}

int	fork_func(t_data *data, pid_t *p)
{
	*p = fork();
	if (*p == -1)
		return (-1);
	else
		(*data).nbr_of_forks++;
	return (0);
}

int	pipe_loop(int *i, int *pipe_i, t_data *data)
{
	pid_t	p;

	while (1)
	{
		if (fork_func(data, &p) == -1)
			return (close_pipes((*data).pipe_array[*pipe_i], 1),
				wait_children(data), -1);
		if (p != 0)
			closing_parent_pipes_if(i, pipe_i, data);
		if (p == 0)
			cmd((*data).pipe_array[*pipe_i - 1],
				(*data).pipe_array[*pipe_i], *i, data);
		if (*i == 1 || (*i == 2 && (*data).heredoc_bool))
			write_from_parent_to_cmd((*data).pipe_array[*pipe_i - 1],
				(*data).pipe_array[*pipe_i], (*data).buf, data);
		if (*i == (*data).nbr_of_cmds)
			break ;
		(*i)++;
		(*pipe_i)++;
		if (pipe((*data).pipe_array[*pipe_i]) == -1)
			return (wait_children(data),
				close_pipes((*data).pipe_array[*pipe_i - 1], 1), -1);
	}
	return (0);
}

int	start_piping(t_data *data)
{
	int		i;
	int		pipe_i;

	alloc_pipe_array(data);
	if (pipe((*data).pipe_array[0]) == -1)
		return (-1);
	if (pipe((*data).pipe_array[1]) == -1)
		return (close_pipes((*data).pipe_array[0], 0), -1);
	pipe_i = 1;
	if ((*data).heredoc_bool)
		i = 2;
	else
		i = 1;
	if (pipe_loop(&i, &pipe_i, data) == -1)
		return (-1);
	receive((*data).pipe_array[pipe_i - 1],
		(*data).pipe_array[pipe_i], data, &i);
	return (0);
}

int	piping(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 3)
		return (0);
	set_data(argc - 2, envp, &data);
	//printf("hello %d\n", 0);
	if (parse_args(&data.args, argv, argc, &data) == -1)
		return (free_args(&data.args), 1);
	//printf("hello %d\n", 1);
	if (data.heredoc_bool && argc < 5)
		return (free_args(&data.args), 1);
	//printf("hello %d\n", 2);
	data.buf = read_file(argv[0], -1, &data, &data.args);
	//printf("hello %d\n", 3);
	if (start_piping(&data) == -1)
		return (free_args(&data.args), free(data.buf), 1);
	//printf("hello %d\n", 4);
	write_out_pluscleanup(&data, data.buf, argc - 1);
	//printf("hello %d\n", 5);
	return (WEXITSTATUS(data.status));
}
//printf("%d\n", 	errno);
//printf("%d", WEXITSTATUS(errno));

void	free_double_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

//int main(int argc, char **argv, char **envp)
//{
//	char 	*line = readline("Minishell>");
//	char 	**split_args;
//	int		i;
//	(void)argv;
//	(void)argc;

//	split_args = ft_split(line, ' ');
//	i = 0;
//	while (split_args[i] != NULL)
//	{
//		printf("%s\n", split_args[i]);
//		i++;
//	}
//	printf("%d\n", i);
//	piping(i, split_args, envp);
//	free_double_array((void **)split_args);
//	free(line);
//}
