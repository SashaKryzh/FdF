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
	if (key == 53 || key == 12)
	{
		// system("leaks fdf");
		exit(0);
	}
	if (key == 13 || key == 126 || key == 1 || key == 125)
		fdf->ox += key == 1 || key == 125 ? 1 : -1;
	else if (key == 0 || key == 123 || key == 2 || key == 124)
		fdf->oy += key == 0 || key == 123 ? -1 : 1;
	else if (key == 33 || key == 30)
		fdf->oz += key == 33 ? -1 : 1;
	else if (key == 27 || key == 78 || key == 24 || key == 69)
	{
		fdf->zoom += key == 27 || key == 78 ? -1 : 1;
		if (!fdf->zoom)
			fdf->zoom = key == 27 || key == 78 ? -1 : 1;
	}
	else if (key >= 82 && key <= 92)
		fdf->depth = key - 82;
	else if (key == 15)
	{
		fdf->zoom = 1;
		fdf->projection = fdf_none;
		fdf->ox = 0;
		fdf->oy = 0;
		fdf->oz = 0;
	}
	else if (key == 34)
		fdf->projection = fdf_iso;
	rotation(fdf);
	return (0);
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
	if (fdf->projection == fdf_iso)
	{
		iso(fdf);
		return ;
	}
	img = (t_cell **)ft_memalloc(sizeof(t_cell *) * fdf->h);
	print_rotation_info(fdf);
	i = 0;
	while (i < fdf->h)
	{
		img[i] = (t_cell *)ft_memalloc(sizeof(t_cell) * fdf->w);
		ft_memcpy(img[i], fdf->map[i], sizeof(t_cell) * fdf->w);
		zoom(fdf, img[i]);
		rot_x(fdf, img[i]);
		rot_y(fdf, img[i]);
		rot_z(fdf, img[i]);
		i++;
	}
	// print_map(fdf, img);
	draw_grid(fdf, img);
}

void	magic(t_map *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, fdf->filename);
	fdf->zoom = 1;
	fdf->depth = 1;
	rotation(fdf);
	// mlx_key_hook(fdf->win_ptr, key_hook, (void *)fdf);
	mlx_hook(fdf->win_ptr, 2, 5, key_hook, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
}

int		main(int ac, char *av[])
{
	t_map	fdf;

	ft_bzero(&fdf, sizeof(t_map));
	get_map(&fdf, ac, av);
	// print_map(&fdf); //
	magic(&fdf);
	return (0);
}
