/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/01 14:07:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	exit_error(int err)
{
	perror(g_error_messages[err]);
	exit(-err);
}

void	get_cmd_path_int_clean(char **possibles_paths, char **pures_paths,
char *cmd_end_path)
{
	if (possibles_paths)
		free_array(possibles_paths);
	if (pures_paths)
		free_array(pures_paths);
	free(cmd_end_path);
}

char	*get_cmd_path_int(char *cmd_end_path, char **possibles_paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	while (possibles_paths[i])
	{
		if (cmd_path)
			free(cmd_path);
		cmd_path = ft_strjoin(possibles_paths[i], cmd_end_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	if (cmd_path)
		free(cmd_path);
	return (NULL);
}

char	*get_cmd_path(char *cmd_name, char **envp)
{
	char	*cmd_path;
	char	**pures_paths;
	char	*cmd_end_path;
	char	**possibles_paths;
	int		i;

	i = 0;
	cmd_end_path = ft_strjoin("/", cmd_name);
	while (strncmp("PATH", envp[i], 4) != 0)
		i++;
	pures_paths = ft_split(envp[i], '=');
	possibles_paths = ft_split(pures_paths[1], ':');
	cmd_path = get_cmd_path_int(cmd_end_path, possibles_paths);
	get_cmd_path_int_clean(possibles_paths, pures_paths, cmd_end_path);
	return (cmd_path);
}
