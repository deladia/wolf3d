#include "wolf3d.h"

void	init_plr(t_plr *plr, int x, int y, int *cnt_plr)
{
	plr->coor.x = (float)x + 0.5f;
	plr->coor.y = (float)y + 0.5f;
	plr->dir.x = -1;
	plr->dir.y = 0;
	plr->plane.y = 0.66f;
	plr->plane.x = 0;
	*cnt_plr += 1;
}

void	init_spr(t_coor_spr **coor, int i, int j, char ch)
{
	t_coor_spr	*tmp;

	tmp = (t_coor_spr *)ft_memalloc(sizeof(t_coor_spr));
	tmp->coor.x = (float)i + 0.5;
	tmp->coor.y = (float)j + 0.5;
	tmp->key = (int)ch - 65;
	tmp->next = *coor;
	*coor = tmp;
}

int	valid_map(t_wolf *wolf)
{
	int	i;
	int	j;
	int	cnt_plr;

	i = 0;
	cnt_plr = 0;
	while(wolf->map[i] != NULL)
	{
		j = 0;
		while (wolf->map[i][j] != '\0')
		{
			if (wolf->map[i][j] == 'P')
				init_plr(&wolf->plr, i, j, &cnt_plr);
			if (ft_isalpha_cap(wolf->map[i][j]) == 1 || wolf->map[i][j] == '0')
			{
				if (wolf->map[i][j] != '0' && wolf->map[i][j] != 'P')
					init_spr(&wolf->coor_spr, i, j, wolf->map[i][j]);
				if (flood_fill(wolf->map, i, j) != 0)
					ft_exit("Flood fill error");
			}
			else if (wolf->map[i][j] != '1')
				ft_exit("Wrong symbol in map");
			j++;
		}
		i++;
	}
	if (cnt_plr != 1)
		ft_exit("Error number of Player");
	return (0);
}