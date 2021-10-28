/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/27 22:18:24 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	exe_cmd(char const *full_cmd_line, t_env *env, int id)
{
	char	**argv_cmd;
	char	*cmd_path;
	int		ret;

	argv_cmd = ft_split(full_cmd_line, ' ');
	cmd_path = get_cmd_path(argv_cmd[0], env->envp);
	ret = execve(cmd_path, argv_cmd, env->envp);
	if (argv_cmd)
		free_array(argv_cmd);
	if (cmd_path)
		free(cmd_path);
	close(env->pipes_handles[id]);
	if (ret < 0)
		exit_error(EXEC_ERROR);
}

void	start_child(char const*file, char const*cmd, t_env *env, int id, void (*cmd_prep_fun)(char const*, t_env *env))
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
		return ;
	if (child_pid)
	{
		cmd_prep_fun(file, env);
		exe_cmd(cmd, env, id);
		exit(0);
	}
	waitpid(child_pid, NULL, 0);
}

void	child_cmd1(char const *infile, t_env *env)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY, 0777);
	if (infile_fd == -1)
		exit_error(OPEN_FILE_ERROR);
	dup2(env->pipes_handles[ID_C1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(env->pipes_handles[ID_C2]);
}

void	child_cmd2(char const *outfile, t_env *env)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		exit_error(OPEN_FILE_ERROR);
	dup2(env->pipes_handles[ID_C2], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(env->pipes_handles[ID_C1]);
}

int	main(int argc, char const *argv[], char **envp)
{
	t_env	env;

	(void)argc;
	(void)argv;
	if (argc != 5)
		return (-1);
	env = (t_env){};
	pipe(env.pipes_handles);
	env.envp = envp;
	start_child(argv[1], argv[2], &env, ID_C1, &child_cmd1);
	start_child(argv[4], argv[3], &env, ID_C2, &child_cmd2);
	close(env.pipes_handles[ID_C2]);
	close(env.pipes_handles[ID_C1]);
	return (EXIT_SUCCESS);
}
