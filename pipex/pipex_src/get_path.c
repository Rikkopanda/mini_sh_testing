/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:19:26 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/02 17:19:06 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_env_paths(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		i++;
	}
}


char **all_paths;

all_paths = get_env_paths(env);