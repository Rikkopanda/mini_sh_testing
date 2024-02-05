/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:53:34 by rik               #+#    #+#             */
/*   Updated: 2024/02/05 16:53:13 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_arguments(t_shell_data *data, char	*line)
{
	int		i;

	data->split_line = ft_split(line, ' ');
	i = 0;
	while (data->split_line[i] != NULL)
		i++;
	t_sections *sections = malloc(sizeof(t_sections) * i);

	while (i >= 0)
	{
		sections[i].content = malloc(sizeof(sections->content) * 4);
		sections[i].content[0] = NULL;
		sections[i].infile = FALSE;
		sections[i].outfile = FALSE;
		sections[i].cmd = FALSE;
		i--;
	}
	while (data->split_line[i] != NULL)
	{
		printf("%s\n", data->split_line[i]);
		if (i == 0 && data->split_line[i][0] == '<')
		{
			sections[i].infile = TRUE;
			sections[i].content[0] = data->split_line[i + 1];
			sections[i].content[1] = NULL;
			i++;
		}
		else
		{
			sections[i].cmd = TRUE;
			int	cmd_args_i = 0;
			while (ft_strstr_chr(data->split_line[i + cmd_args_i], data->symbols.pipe_chrs) == NULL &&
					data->split_line[i + cmd_args_i] != NULL)
			{
				sections[i].content[cmd_args_i] = data->split_line[i + cmd_args_i];
				cmd_args_i++;
			}
			sections[i].content[cmd_args_i] = NULL;
		}
		i++;
	}
	data->argc = i;
	return (0);
}

/*
	handle first argument being a command.
	piping should cleanly exit on succes and fail.
	also perhaps a usefull status value set somewhere
	_______________

	use pipex in orignal format?,
	so parse with >, <, <<, etc and put in pipex format?
	_______________
	check if format is correct? > < >> << etc..
*/
int	parse(t_shell_data *data, char	*line)
{
	init_arguments(data, line);
	if (ft_strcmp(line, (char *)"exit") == 0)
	{
		clearing(data, line);
		exit(0);
	}
	data->pipex = FALSE;
	if (data->split_line[0][0] == '<')
		data->pipex = TRUE;
	return (0);
}
