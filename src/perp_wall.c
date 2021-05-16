#include "wolf3d.h"

void	clear_arr(t_mlx *mlx, t_texture *head)
{
	int			color;
	int			i;
	t_texture	*tmp;

	i = 0;
	color = 0x000000;
	tmp = find_texture(head, c);
	if (tmp->image == NULL)
		color = tmp->width;
	while (i < mlx->width * mlx->height / 2)
	{
		mlx->addr[i] = color;
		i++;
	}
	tmp = find_texture(head, f);
	if (tmp->image == NULL)
		color = tmp->width;
	while (i < mlx->width * mlx->height)
	{
		mlx->addr[i] = color;
		i++;
	}
}

void	ft_perp_wall(t_ray *ray, t_plr *plr, int height)
{
	if (ray->side == so || ray->side == no)
		ray->perp_wall_dist = (ray->mapx - plr->coor.x
				+ (1 - ray->stepx) / 2) / ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->mapy - plr->coor.y
				+ (1 - ray->stepy) / 2) / ray->ray_dir.y;
	ray->line_h = (int)(height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_h / 2 + height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + height / 2;
	if (ray->draw_end >= height)
		ray->draw_end = height - 1;
}
