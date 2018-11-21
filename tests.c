
#include "fdf.h"

int		**test_map(void)
{
	int **map;

	map = (int **)malloc(sizeof(int *) * 5);
	for (int i = 0; i < 5; i++)
		map[i] = (int *)malloc(sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			map[i][j] = 0;
	return (map);
}

void	test_print(int **map)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			printf("%-3d", map[i][j]);
		printf("\n");
	}
}
