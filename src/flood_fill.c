#include "wolf3d.h"

int	flood_fill_angle(char **map, int i, int j)
{
	int	ok;

	ok = 4;
	if (i - 1 >= 0 && j - 1 >= 0 && (int)ft_strlen(map[i - 1]) > j - 1)
		if (map[i - 1][j - 1] != ' ')
			ok--;
	if (i - 1 >= 0 && (int)ft_strlen(map[i - 1]) > j + 1)
		if (map[i - 1][j + 1] != ' ')
			ok--;
	if (map[i + 1] != NULL && j - 1 >= 0 && (int)ft_strlen(map[i + 1]) > j - 1)
		if (map[i + 1][j - 1] != ' ')
			ok--;
	if (map[i + 1] != NULL && (int)ft_strlen(map[i + 1]) > j + 1)
		if (map[i + 1][j + 1] != ' ')
			ok--;
	return (ok);
}

int	flood_fill(char **map, int i, int j)
{
	int	ok;

	ok = 4;
	if (flood_fill_angle(map, i, j) != 0)
		return (ok);
	if (j - 1 >= 0)
		if (map[i][j - 1] != ' ')
			ok--;
	if (j + 1 < (int)ft_strlen(map[i]))
		if (map[i][j + 1] != ' ')
			ok--;
	if (i - 1 >= 0 && (int)ft_strlen(map[i - 1]) > j)
		if (map[i - 1][j] != ' ')
			ok--;
	if (map[i + 1] != NULL && (int)ft_strlen(map[i + 1]) > j)
		if (map[i + 1][j] != ' ')
			ok--;
	return (ok);
}
