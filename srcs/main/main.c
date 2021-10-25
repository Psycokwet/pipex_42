/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/25 19:50:42 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void start_child(char *file, char *cmd, int pipes_handles[2], void (*cmd_fun)(char*, char*, int[2]))
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Fork: ");
		return ;
	}
	if (child_pid)
		cmd_fun(file, cmd, pipes_handles);
	else
		waitpid(child_pid, NULL, 0);
}

void child_cmd1(char *infile, char *cmd1, int pipes_handles[2])
{
	printf("HELLO 1\n");
	exit(0);
}
void child_cmd2(char *outfile, char *cmd2, int pipes_handles[2])
{
	printf("HELLO 2\n");
	exit(0);
}

int	main(int argc, char const *argv[], char **envp)
{
	int		pipes_handles[2];

	(void)argc;
	(void)argv;
	// if (argc != 5)
	// 	return (-1);

	pipe(pipes_handles);
	start_child(argv[1], argv[2], pipes_handles, &child_cmd1);
	start_child(argv[4], argv[3], pipes_handles, &child_cmd2);

	printf("HELLO PARENT\n");
	return (EXIT_SUCCESS);
}
