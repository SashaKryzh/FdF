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

# define WIN_WIDTH 700
# define WIN_HEIGHT 700

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
	t_cell			**img;
	int				w;
	int				h;

	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	
	char			*img_p;
	int				bpp;
	int				size_line;
	int				endian;

	enum			e_projection
	{
		fdf_none,
		fdf_iso
	}				projection;

	int				zoom;
	int				depth;
	int				ox;
	int				oy;
	int				oz;

	char			*filename;
}					t_map;

typedef struct		s_read
{
	t_cell			*l;
	struct s_read	*next;
}					t_read;

void		get_map(t_map *map, int ac, char *av[]);

/*
**	Draw
*/

void		draw_line(t_map *fdf, t_cell p1, t_cell p2);
void		draw_map(t_map *fdf, t_cell **img);

void		get_color(t_cell *cur, t_cell *start, t_cell *end, int delta);

/*
**	Rotations
*/

void		rotation(t_map *fdf);

void		zoom(t_map *fdf, t_cell *img);
void		rot_x(t_map *fdf, t_cell *img);
void		rot_y(t_map *fdf, t_cell *img);
void		rot_z(t_map *fdf, t_cell *img);
void		iso(t_map *fdf);

/*
**	Utils
*/

void		exit_func(char *msg);
void		put_bytes(char *s, char *v);
int			ft_atoi_hex(char *s);
int			line_width(char **token);

/*
**	Tests
*/

void		print_map(t_map *fdf, t_cell **map);
void		print_rotation_info(t_map *fdf);

#endif
