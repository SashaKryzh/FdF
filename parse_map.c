/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 19:23:05 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/22 19:23:05 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		manage_color(t_cell *line, char **token, int i)
{
	char **tab;

	if (!(tab = ft_strsplit(token[i], ',')))
		exit_func(COLOR_ERROR);
	if (line_width(tab) != 2)
		exit_func(COLOR_ERROR);
	if (!ft_strnequ(tab[1], "0x", 2))
		exit_func(COLOR_ERROR);
	line[i].color = ft_atoi_hex(&tab[1][2]);
	if (line[i].color == 0 && tab[1][2] != '0')
		exit_func(COLOR_ERROR);
	free(tab[0]);
	free(tab[1]);
	free(tab);
}

t_cell		*manage_line(t_map *map, char *ln)
{
	char		**token;
	t_cell		*line;
	int			i;

	token = ft_strsplit(ln, ' ');
	free(ln);
	map->w = !map->w ? line_width(token) : map->w;
	line = (t_cell *)ft_memalloc(sizeof(t_cell) * map->w);
	i = 0;
	while (map->w && token && token[i])
	{
		if (i < map->w)
		{
			line[i].z = ft_atoi(token[i]);
			if (ft_strchr(token[i], ','))
				manage_color(line, token, i);
		}
		free(token[i]);
		i++;
	}
	if (!map->w || i < map->w)
		exit_func(MAP_ERROR);
	free(token);
	return (line);
}

void		convert_map(t_map *map, t_read *read)
{
	t_read	*tmp;
	int		i;
	int		j;

	map->map = (t_cell **)ft_memalloc(sizeof(t_cell *) * map->h);
	i = 0;
	while (i < map->h)
	{
		map->map[i] = read->l;
		j = 0;
		while (j < map->w)
		{
			map->map[i][j].x = j;
			map->map[i][j].y = i;
			if (!map->map[i][j].color)
				map->map[i][j].color = 0xFFFFFF;
			j++;
		}
		tmp = read;
		read = read->next;
		free(tmp);
		i++;
	}
}

void		parse_map(t_map *map, char *file)
{
	t_read	*read;
	char	*line;
	int		fd;
	int		ret;

	read = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		exit_func(OPEN_ERROR);
	map->filename = ft_strdup(file);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		add_line(&read, manage_line(map, line));
		map->h += 1;
	}
	if (ret < 0 || close(fd) < 0)
		exit_func(ret < 0 ? READ_ERROR : CLOSE_ERROR);
	convert_map(map, read);
}

void		get_map(t_map *map, int ac, char *av[])
{
	char	*s;

	if (ac == 2)
	{
		if (!(s = ft_strrchr(av[1], '.')))
			exit_func(FILE_ERROR);
		if (!ft_strequ(s, ".fdf"))
			exit_func(FILE_ERROR);
		parse_map(map, av[1]);
	}
	else
	{
		ft_printf("Usage : ./fdf <filename>\n");
		exit(0);
	}
}
