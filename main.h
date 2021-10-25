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

#endif
