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

# define MAP_ERROR "Map error"
# define COLOR_ERROR "Color error"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define SEGM (WIN_HEIGHT / (fdf->w > fdf->h ? fdf->w : fdf->h) / 2)

typedef struct		s_cell
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_cell;

typedef struct		s_map
{
	t_cell			**map;
	int				w;
	int				h;

	void			*mlx_ptr;
	void			*win_ptr;

	char			*filename;
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
int			ft_atoi_hex(char *s);
int			line_width(char **token);

/*
**	Tests
*/

void		print_map(t_map *map);

#endif
