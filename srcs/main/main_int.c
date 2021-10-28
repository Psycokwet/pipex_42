/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/27 22:18:44 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	exit_error(int err)
{
	perror(g_error_messages[err]);
	exit(-err);
}

char	*get_cmd_path(char *cmd_name, char **envp)
{
	char	*cmd_path;
	char	**pures_paths;
	char	*cmd_end_path;
	char	**possibles_paths;
	int		i;

	i = 0;
	cmd_path = NULL;
	cmd_end_path = ft_strjoin("/", cmd_name);
	while (strncmp("PATH", envp[i], 4) != 0)
		i++;
	pures_paths = ft_split(envp[i], '=');
	possibles_paths = ft_split(pures_paths[1], ':');
	i = 0;
	while (possibles_paths[i])
	{
		if (cmd_path)
			free(cmd_path);
		cmd_path = ft_strjoin(possibles_paths[i], cmd_end_path);
		if (access(cmd_path, F_OK) == 0)
			break ;
		i++;
	}
	if (possibles_paths)
		free_array(possibles_paths);
	if (pures_paths)
		free_array(pures_paths);
	free(cmd_end_path);
	return (cmd_path);
}
