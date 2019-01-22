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

void	add_line(t_read **read, t_cell *line)
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

int		line_width(char **token)
{
	int i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

t_cell	*manage_line(t_map *map, char *l)
{
	char		**token;
	t_cell		*line;
	int			i;

	token = ft_strsplit(l, ' ');
	free(l);
	map->w = !map->w ? line_width(token) : map->w;
	line = (t_cell *)ft_memalloc(sizeof(t_cell) * map->w);
	i = 0;
	while (token[i] && i < map->w)
	{
		line[i].x = i;
		line[i].y = map->h;
		line[i].z = ft_atoi(token[i]);
		i++;
	}
	return (line);
}

void	convert_map(t_map *map, t_read *read)
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

void	parse_map(t_map *map, char *file)
{
	t_read	*read;
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) < 0)
		exit(1);
	read = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		add_line(&read, manage_line(map, line));
		map->h += 1;
	}
	if (ret < 0 || close(fd) < 0)
		exit(1);
	convert_map(map, read);
}

void	get_map(t_map *map, int ac, char *av[])
{
	char	*s;

	if (ac == 2)
	{
		if (!(s = ft_strrchr(av[1], '.')))
			exit(1);
		if (!ft_strequ(s, ".fdf"))
			exit(1);
		parse_map(map, av[1]);
	}
}

void	print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			ft_printf("%3d ", map->map[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int		main(int ac, char *av[])
{
	t_map	map;

	map.w = 0;
	map.h = 0;
	get_map(&map, ac, av);
	print_map(&map);
	system("leaks fdf");
	return (0);
}
