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

void	ft_rotate_l(t_plr *plr)
{
	float	olddirx;
	float	oldplnx;

	olddirx = plr->dir.x;
	plr->dir.x = plr->dir.x * cos(0.1) - plr->dir.y * sin(0.1);
	plr->dir.y = olddirx * sin(0.1) + plr->dir.y * cos(0.1);
	oldplnx = plr->plane.x;
	plr->plane.x = plr->plane.x * cos(0.1) - plr->plane.y * sin(0.1);
	plr->plane.y = oldplnx * sin(0.1) + plr->plane.y * cos(0.1);
}

void	ft_rotate_r(t_plr *plr)
{
	float	olddirx;
	float	oldplnx;

	olddirx = plr->dir.x;
	plr->dir.x = plr->dir.x * cos(-0.1) - plr->dir.y * sin(-0.1);
	plr->dir.y = olddirx * sin(-0.1) + plr->dir.y * cos(-0.1);
	oldplnx = plr->plane.x;
	plr->plane.x = plr->plane.x * cos(-0.1) - plr->plane.y * sin(-0.1);
	plr->plane.y = oldplnx * sin(-0.1) + plr->plane.y * cos(-0.1);
}

int	key_press(int keycode, t_wolf *wolf)
{
	float	olddirx;
	float	oldplanex;

	olddirx = 0;
	oldplanex = 0;
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		ft_move_w(&wolf->plr, wolf->map);
	if (keycode == 0)
		ft_move_a(&wolf->plr, wolf->map);
	if (keycode == 1)
		ft_move_s(&wolf->plr, wolf->map);
	if (keycode == 2)
		ft_move_d(&wolf->plr, wolf->map);
	if (keycode == 123)
		ft_rotate_l(&wolf->plr);
	if (keycode == 124)
		ft_rotate_r(&wolf->plr);
	raycast(wolf);
	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.mlx_win, wolf->mlx.img, 0, 0);
	return (0);
}

void mlx_create(t_wolf *wolf)
{
	// map->mlx.mlx = mlx_init();
	wolf->mlx.mlx_win = mlx_new_window(wolf->mlx.mlx_ptr,
			wolf->mlx.width, wolf->mlx.height, "wolf3d");
	wolf->mlx.img = mlx_new_image(wolf->mlx.mlx_ptr,
			wolf->mlx.width, wolf->mlx.height);
	wolf->mlx.addr = (int *)mlx_get_data_addr(wolf->mlx.img,
			&wolf->mlx.bit_per_pixel, &wolf->mlx.line_len, &wolf->mlx.endian);
	// texture_init(wolf->wall, &wolf->tex, &wolf->mlx);
	raycast(wolf);

	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.mlx_win, wolf->mlx.img, 0, 0);
	mlx_hook(wolf->mlx.mlx_win, 17, 0, ft_close, 0);
	mlx_hook(wolf->mlx.mlx_win, 2, 0, key_press, wolf);
	mlx_loop(wolf->mlx.mlx_ptr);
}