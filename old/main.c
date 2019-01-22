/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:25:05 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/21 13:25:06 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int key, void *param)
{
	param = 0;
	if (key == 53)
		exit(0);
	return (0);
}

void	 drawline(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int dx, dy, p, x, y;
 
	dx=x1-x0;
	dy=y1-y0;
 
	x=x0;
	y=y0;
 
	p=2*dy-dx;
 
	while(x<x1)
	{
		if(p>=0)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
			p=p+2*dy;
		}
		x=x+1;
	}
}

void	draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int		steep;
	int		dx;
	int		dy;
	int		p;

	steep = FALSE;
	if (ft_abs(x0 - x1) < ft_abs(y0 - y1))
	{
		steep = TRUE;
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
		printf("1\n");
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1);
		ft_swap(&y0, &y1);
		printf("2\n");
	}
	dx = x1 - x0;
	dy = y1 - y0;
	p = (2 * dy) - dx;
	printf("%d %d %d\n", dx, dy, p);
	while (x0 <= x1)
	{
		if (!steep)
			mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF);
		else
			mlx_pixel_put(mlx_ptr, win_ptr, y0, x0, 0xFFFFFF);
		p = p + (2 * dy) - (2 * dx);
		if (p >= 0)
			y0 += y1 >= y0 ? 1 : -1;
		else
			p = p + (2 * dx);
		x0 += 1;
	}
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	draw_line(mlx_ptr, win_ptr, 0, 0, 500, 500);
	draw_line(mlx_ptr, win_ptr, 250, 0, 250, 500);
	draw_line(mlx_ptr, win_ptr, 0, 500, 500, 0);
	mlx_key_hook(win_ptr, key_hook, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
