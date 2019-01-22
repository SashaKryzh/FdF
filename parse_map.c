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

void		add_line(t_read **read, t_cell *line)
{
	t_read	*new;
	t_read	*tmp;

	new = (t_read *)ft_memalloc(sizeof(t_read));
	new->l = line;
	if (!*read)
		*read = new;
	else
	{
		tmp = *read;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
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
	while (token[i] && i < map->w)
	{
		line[i].x = i;
		line[i].y = map->h;
		line[i].z = ft_atoi(token[i]);
		free(token[i]);
		i++;
	}
	free(token);
	return (line);
}

void		convert_map(t_map *map, t_read *read)
{
	t_read	*tmp;
	int		i;

	map->map = (t_cell **)ft_memalloc(sizeof(t_cell *) * map->h);
	i = 0;
	while (i < map->h)
	{
		map->map[i] = read->l;
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
	ft_bzero(map, sizeof(t_map));
	if ((fd = open(file, O_RDONLY)) < 0)
		exit_func(OPEN_ERROR);
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
}
