/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:25:36 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/21 13:25:37 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "mlx.h"

# include "libft.h"

# define FILE_ERROR "Invalid file"
# define OPEN_ERROR "File open error"
# define READ_ERROR "Read error"
# define CLOSE_ERROR "Close error"

typedef struct		s_cell
{
	int				x;
	int				y;
	int				z;
}					t_cell;

typedef struct		s_map
{
	t_cell			**map;
	int				w;
	int				h;
}					t_map;

typedef struct		s_read
{
	t_cell			*l;
	struct s_read	*next;
}					t_read;

void		get_map(t_map *map, int ac, char *av[]);

/*
**	Utils
*/

void		exit_func(char *msg);
int			line_width(char **token);

/*
**	Tests
*/

void		print_map(t_map *map);

#endif
