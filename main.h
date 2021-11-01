/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/05/06 09:33:00 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define BYTE_SIZE 8

# include <stddef.h>
# include <stdbool.h>

# include <unistd.h>

// int access(const char *pathname, int mode);
// int unlink(const char *pathname);
// int close(int fd);
// ssize_t read(int fd, void *buf, size_t count);
// ssize_t write(int fd, const void *buf, size_t count);
// int pipe(int pipefd[2]);
// int dup(int oldfd);
// int dup2(int oldfd, int newfd);
// int execve(const char *filename, char *const argv[],
// 			char *const envp[]);
// pid_t fork(void);

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

// int open(const char *pathname, int flags);
// int open(const char *pathname, int flags, mode_t mode);

# include <stdlib.h>

// void *malloc(size_t size);
// free
// void exit(int status);
# include <sys/wait.h>

// pid_t wait(int *wstatus);
// pid_t waitpid(pid_t pid, int *wstatus, int options);

# include <stdio.h>

// void perror(const char *s);

# include <string.h>

// char *strerror(int errnum);

typedef struct s_env {
	int		pipes_handles[2];
	char	**envp;
	int		status;
}				t_env;

typedef struct s_child_env {
	char const		*file;
	char const		*cmd;
	int				id;
}				t_child_env;

# define FORK_ERROR 0
# define FORK_MSG "Fork: "
# define OPEN_FILE_ERROR 1
# define OPEN_FILE_MSG "Error while opening a file."
# define EXEC_ERROR 127
# define EXEC_MSG "Error while executing a command."
# define MAX_ERRORS 128

static char	*g_error_messages[MAX_ERRORS] = {
	FORK_MSG,
	OPEN_FILE_MSG,
	EXEC_MSG
};

# define ID_C1 1
# define ID_C2 0

void		free_array(char **splitted);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dst_len_mx);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t len_mx);
void		exit_error(int err);
char		*get_cmd_path(char *cmd_name, char **envp);

#endif
