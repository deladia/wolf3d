#include "wolf3d.h"

int	ft_close(int param)
{
	(void)param;
	exit(0);
}

void	ft_move_w(t_plr *plr, char **map)
{
	if (map[(int)(plr->coor.x + plr->dir.x * 0.3)][(int)plr->coor.y] != '1')
		plr->coor.x += plr->dir.x * 0.1;
	if (map[(int)(plr->coor.x)][(int)(plr->coor.y + plr->dir.y * 0.3)] != '1')
		plr->coor.y += plr->dir.y * 0.1;
}

void	ft_move_a(t_plr *plr, char **map)
{
	if (map[(int)(plr->coor.x - plr->plane.x * 0.3)][(int)plr->coor.y] != '1')
		plr->coor.x -= plr->plane.x * 0.1;
	if (map[(int)(plr->coor.x)][(int)(plr->coor.y - plr->plane.y * 0.3)] != '1')
		plr->coor.y -= plr->plane.y * 0.1;
}

void	ft_move_s(t_plr *plr, char **map)
{
	if (map[(int)(plr->coor.x - plr->dir.x * 0.3)][(int)plr->coor.y] != '1')
		plr->coor.x -= plr->dir.x * 0.1;
	if (map[(int)(plr->coor.x)][(int)(plr->coor.y - plr->dir.y * 0.3)] != '1')
		plr->coor.y -= plr->dir.y * 0.1;
}

void	ft_move_d(t_plr *plr, char **map)
{
	if (map[(int)(plr->coor.x + plr->plane.x * 0.3)][(int)plr->coor.y] != '1')
		plr->coor.x += plr->plane.x * 0.1;
	if (map[(int)(plr->coor.x)][(int)(plr->coor.y + plr->plane.y * 0.3)] != '1')
		plr->coor.y += plr->plane.y * 0.1;
}
