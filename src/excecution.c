/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:53:31 by rik               #+#    #+#             */
/*   Updated: 2024/02/04 19:04:39 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_shell_data *data)
{
	if (data->pipex == TRUE)
		piping(data->argc, data->split_line, data->envp);
	if (data->pipex == FALSE)
	{
		pid_t p = fork();
		int		status;

		if (!p)
		{
			char	*path = find_cmd_path(data->split_line[0], data->envp);
			if (path != NULL)
				execve(path, &data->split_line[0], data->envp);
			exit(0);
		}
		waitpid(p, &status, 0);
	}
}