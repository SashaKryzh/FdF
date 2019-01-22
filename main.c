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

void	draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	bool	steep;
	int		dx;
	int		dy;
	int		derror;
	int		error;

	steep = false;
	if (ft_abs(x0 - x1) < ft_abs(y0 - y1))
	{
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
		steep = true;
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1);
		ft_swap(&y0, &y1);
	}
	dx = x1 - x0;
	dy = y1 - y0;
	derror = ft_abs(dy) * 2;
	error = 0;
	while (x0 < x1)
	{
		if (!steep)
			mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF);
		else
			mlx_pixel_put(mlx_ptr, win_ptr, y0, x0, 0xFFFFFF);
		error += derror;
		if (error > dx)
		{
			y0 += y1 > y0 ? 1 : -1;
			error -= dx * 2; 
		}
		x0++;
	}
}

void	magic(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	draw_line(mlx_ptr, win_ptr, 500, 500, 0, 0);
	draw_line(mlx_ptr, win_ptr, 250, 0, 250, 500);
	draw_line(mlx_ptr, win_ptr, 500, 0, 0, 500);
	draw_line(mlx_ptr, win_ptr, 0, 250, 500, 250);
	mlx_key_hook(win_ptr, key_hook, (void *)0);
	mlx_loop(mlx_ptr);
}

int		main(int ac, char *av[])
{
	t_map	map;

	// get_map(&map, ac, av);
	print_map(&map); //
	magic();
	return (0);
}
