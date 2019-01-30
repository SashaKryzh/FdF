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
		system("leaks fdf");
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

void	rotation(t_map *fdf)
{
	int		i;

	if (fdf->projection == fdf_iso)
	{
		iso(fdf);
		return ;
	}
	print_rotation_info(fdf);
	i = 0;
	while (i < fdf->h)
	{
		ft_memcpy(fdf->img[i], fdf->map[i], sizeof(t_cell) * fdf->w);
		zoom(fdf, fdf->img[i]);
		rot_x(fdf, fdf->img[i]);
		rot_y(fdf, fdf->img[i]);
		rot_z(fdf, fdf->img[i]);
		i++;
	}
	draw_map(fdf, fdf->img);
}

void	magic(t_map *fdf)
{
	int		i;

	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, fdf->filename);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->img_p = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp,
		&fdf->size_line, &fdf->endian);
	fdf->zoom = 1;
	fdf->depth = 1;
	fdf->img = (t_cell **)ft_memalloc(sizeof(t_cell *) * fdf->h);
	i = 0;
	while (i < fdf->h)
	{
		fdf->img[i] = (t_cell *)ft_memalloc(sizeof(t_cell) * fdf->w);
		i++;
	}
	rotation(fdf);
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
