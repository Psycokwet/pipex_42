/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/26 21:36:01 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	exit_error(int err)
{
	perror(g_error_messages[err]);
	exit(-err);
}

char *get_cmd_path(char *cmd_name, char **envp)
{
	char	*cmd_path;
	char	**pures_paths;
	char	*cmd_end_path;
	char	**possibles_paths;
	int		i;

	i = 0;
	cmd_path = NULL;
	cmd_end_path = ft_strjoin("/", cmd_name);
	while(strncmp("PATH", envp[i], 4) != 0)
		i++;
	pures_paths = ft_split(envp[i], '=');
	possibles_paths = ft_split(pures_paths[1], ':');
	i = 0;

	while(possibles_paths[i])
	{
		if (cmd_path)
			free(cmd_path);
		cmd_path = ft_strjoin(possibles_paths[i], cmd_end_path);
		if (access(cmd_path, F_OK) == 0)
			break;
		i++;
	}
	if (possibles_paths)
		free_array(possibles_paths);
	if (pures_paths)
		free_array(pures_paths);
	free(cmd_end_path);
	return (cmd_path);
}

void	exe_cmd(char const *full_cmd_line, char **envp)
{
	char **argv_cmd;
	char *cmd_path;

	argv_cmd = ft_split(full_cmd_line, ' ');
	cmd_path = get_cmd_path(argv_cmd[0], envp);
	if (execve(cmd_path, argv_cmd, envp) < 0)
		exit_error(EXEC_ERROR);
	if (argv_cmd)
		free_array(argv_cmd);
	if (cmd_path)
		free(cmd_path);
}


void start_child(char const*file, char const*cmd, t_env *env, void (*cmd_prep_fun)(char const*, t_env *env))
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		return ;
	}
	if (child_pid)
	{
		cmd_prep_fun(file, env);
		exe_cmd(cmd, env->envp);
		exit(0);
	}
	waitpid(child_pid, NULL, 0);
}

void child_cmd1(char const *infile, t_env *env)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY, 0777);
	if (infile_fd == -1)
		exit_error(OPEN_FILE_ERROR);
	dup2(env->pipes_handles[ID_C1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(env->pipes_handles[ID_C2]);
	printf("HELLO 1\n");
}

void child_cmd2(char const *outfile, t_env *env)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		exit_error(OPEN_FILE_ERROR);
	dup2(env->pipes_handles[ID_C2], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(env->pipes_handles[ID_C1]);
	printf("HELLO 2\n");
}


int	main(int argc, char const *argv[], char **envp)
{
	t_env env;
	(void)argc;
	(void)argv;
	if (argc != 5)
		return (-1);

	env = (t_env){};
	pipe(env.pipes_handles);
	env.envp = envp;
	start_child(argv[1], argv[2], &env, &child_cmd1);
	start_child(argv[4], argv[3], &env, &child_cmd2);

	close(env.pipes_handles[ID_C2]);
	close(env.pipes_handles[ID_C1]);
	printf("HELLO PARENT\n");
	return (EXIT_SUCCESS);
}
