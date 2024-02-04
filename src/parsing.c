/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:53:34 by rik               #+#    #+#             */
/*   Updated: 2024/02/04 19:08:43 by rik              ###   ########.fr       */
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
	data->argc = i;
	printf("%d\n", i);
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
