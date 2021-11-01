/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/01 18:33:51 by scarboni         ###   ########.fr       */
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
	if (cmd_path)
	{
		ret = execve(cmd_path, argv_cmd, env->envp);
		free(cmd_path);
	}
	else
		ret = 1;
	if (argv_cmd)
		free_array(argv_cmd);
	close(env->pipes_handles[id]);
	if (ret < 0)
		exit_error(EXEC_ERROR);
	exit(ret);
}

int	start_child(t_child_env c_env, t_env *env,
void (*cmd_prep_fun)(char const*, t_env *env))
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
		return (-1);
	if (child_pid == 0)
	{
		cmd_prep_fun(c_env.file, env);
		exe_cmd(c_env.cmd, env, c_env.id);
		exit(0);
	}
	return (child_pid);
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
	int		c1_ret;
	int		c2_ret;

	(void)argc;
	(void)argv;
	if (argc != 5)
		return (0);
	env = (t_env){0};
	env.exit_value = EXIT_SUCCESS;
	pipe(env.pipes_handles);
	env.envp = envp;
	c1_ret = start_child((t_child_env){argv[1], argv[2], ID_C1}, &env,
			&child_cmd1);
	c2_ret = start_child((t_child_env){argv[4], argv[3], ID_C2}, &env,
			&child_cmd2);
	ft_wait(c1_ret, c2_ret, &env);
	ft_wait(c1_ret, c2_ret, &env);
	return (env.exit_value);
}
