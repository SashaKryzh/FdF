/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:56:32 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/03 15:56:33 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

typedef struct	s_gnl
{
	char			*str;
	int				fd;
	struct s_gnl	*next;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
