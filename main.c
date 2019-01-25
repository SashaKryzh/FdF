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
	param = 0;
	if (key == 53)
		exit(0);
	return (0);
}

void	draw_line(void *mlx_ptr, void *win_ptr, t_cell p1, t_cell p2, int segm)
{
	bool	steep;
	int		dx;
	int		dy;
	int		derror;
	int		error;

	steep = false;
	p1.x *= segm;
	p1.y *= segm;
	p2.x *= segm;
	p2.y *= segm;
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
			mlx_pixel_put(mlx_ptr, win_ptr, p1.x + 10, p1.y + 10, 0xFFFFFF);
		else
			mlx_pixel_put(mlx_ptr, win_ptr, p1.y + 10, p1.x + 10, 0xFFFFFF);
		error += derror;
		if (error > dx)
		{
			p1.y += p2.y > p1.y ? 1 : -1;
			error -= dx * 2; 
		}
		p1.x++;
	}
}

void	draw_grid(t_map *fdf)
{
	int i;
	int	j;

	i = 0;
	while (i < fdf->h)
	{
		j = 0;
		while (j < fdf->w - 1)
		{
			ft_printf("(%d %d) (%d %d)\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j + 1].x, fdf->map[i][j + 1].y);
			draw_line(fdf->mlx_ptr, fdf->win_ptr, fdf->map[i][j], fdf->map[i][j + 1], SEGM);
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
			ft_printf("(%d %d) (%d %d)\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i + 1][j].x, fdf->map[i + 1][j].y);
			draw_line(fdf->mlx_ptr, fdf->win_ptr, fdf->map[i][j], fdf->map[i + 1][j], SEGM);
			j++;
		}
		i++;
	}
}

void	magic(t_map *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, fdf->filename);
	draw_grid(fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, (void *)0);
	mlx_loop(fdf->mlx_ptr);
}

int		main(int ac, char *av[])
{
	t_map	fdf;

	get_map(&fdf, ac, av);
	// print_map(&fdf); //
	magic(&fdf);
	return (0);
}
