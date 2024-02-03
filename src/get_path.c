/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:19:26 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/03 15:20:47 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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