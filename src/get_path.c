/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rik <rik@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:19:26 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/04 12:23:36 by rik              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define YES 99

static char *get_env_paths(char **env)
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

static char	*try_local(char *arg)
{
	if (access(arg, X_OK) == 0)
		return (arg);
	return (NULL);
}

static char	*check_env_path(char *arg, char **envp)
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
	char	*path;

	path = NULL;
	path = try_local(arg);
	if (path != NULL)
		return (path);
	path = check_env_path(arg, envp);
	return (path);
}
