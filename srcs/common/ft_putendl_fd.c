/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/30 09:27:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	ft_putchar_fd('\n', fd);
}
/*
** #1. La chaine de caracteres a ecrire.
** #2. Le file descriptor sur lequel ecrire.
** Valeur de retour None
** Fonctions externes autorisees
** write
** Description Ecrit La chaine de caracteres 's' sur le file
** descriptor donne, suivie d'un retour a la ligne.
*/
