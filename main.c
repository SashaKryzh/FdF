/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:13:14 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/22 16:13:15 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_func(char *msg)
{
	perror(msg);
	exit(1);
}

int		key_hook(int key, void *param)
{
	t_map *fdf;

	fdf = (t_map *)param;
	if (key == 53)
		exit(0);
	if (key == 13 || key == 126 || key == 1 || key == 125)
		fdf->ox += key == 1 || key == 125 ? -0.2 : 0.2;
	else if (key == 0 || key == 123 || key == 2 || key == 124)
		fdf->oy += key == 0 || key == 123 ? 0.1 : -0.1;
	else if (key == 27 || key == 78 || key == 24 || key == 69)
		fdf->zoom += key == 27 || key == 78 ? -0.1 : 0.1;
	else if (key >= 83 && key <= 92)
		fdf->depth = 1 + 0.1 * key - 83;
	rotation(fdf);
	return (0);
}

void	draw_line(t_map *fdf, t_cell p1, t_cell p2)
{
	bool	steep;
	int		dx;
	int		dy;
	int		derror;
	int		error;

	steep = false;
	if (ft_abs(p1.x - p2.x) < ft_abs(p1.y - p2.y))
	{
		ft_swap(&p1.x, &p1.y);
		ft_swap(&p2.x, &p2.y);
		steep = true;
	}
	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	derror = ft_abs(dy) * 2;
	error = 0;
	ft_printf("(%d %d) (%d %d)\n", p1.x, p1.y, p2.x, p2.y);
	while (p1.x < p2.x)
	{
		if (!steep)
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, p1.x + WIN_WIDTH / 2, p1.y + WIN_HEIGHT / 2, 0xFFFFFF);
		else
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, p1.y + WIN_WIDTH / 2, p1.x + WIN_HEIGHT / 2, 0xFFFFFF);
		error += derror;
		if (error > dx)
		{
			p1.y += p2.y > p1.y ? 1 : -1;
			error -= dx * 2; 
		}
		p1.x++;
	}
}

void	draw_grid(t_map *fdf, t_cell **img)
{
	int i;
	int	j;

	i = 0;
	while (i < fdf->h)
	{
		j = 0;
		while (j < fdf->w - 1)
		{
			ft_printf("(%d %d) (%d %d)\n", img[i][j].x, img[i][j].y, img[i][j + 1].x, img[i][j + 1].y);
			draw_line(fdf, img[i][j], img[i][j + 1]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < fdf->h - 1)
	{
		j = 0;
		while (j < fdf->w)
		{
			ft_printf("(%d %d) (%d %d)\n", img[i][j].x, img[i][j].y, img[i + 1][j].x, img[i + 1][j].y);
			draw_line(fdf, img[i][j], img[i + 1][j]);
			j++;
		}
		i++;
	}
}

void	rotation(t_map *fdf)
{
	t_cell	**img;
	int		i;

	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	img = (t_cell **)ft_memalloc(sizeof(t_cell *) * fdf->h);
	i = 0;
	while (i < fdf->h)
	{
		img[i] = (t_cell *)ft_memalloc(sizeof(t_cell) * fdf->w);
		ft_memcpy(img[i], fdf->map[i], sizeof(t_cell) * fdf->w);
		zoom(fdf, img[i], i, fdf->zoom);
		rot_x(fdf, img[i], fdf->ox);
		rot_y(fdf, img[i], fdf->oy);
		rot_z(fdf, img[i], fdf->oz);
		i++;
	}
	draw_grid(fdf, img);
}

void	magic(t_map *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, fdf->filename);
	iso(fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
}

int		main(int ac, char *av[])
{
	t_map	fdf;

	ft_bzero(&fdf, sizeof(t_map));
	fdf.zoom = 1;
	fdf.depth = 1;
	get_map(&fdf, ac, av);
	// print_map(&fdf); //
	magic(&fdf);
	return (0);
}
