#include "wolf3d.h"

void	ft_delta_dist(t_xy *ray_dir, t_xy *delta_dist)
{
	if (ray_dir->y == 0)
		delta_dist->x = 0;
	else if (ray_dir->x == 0)
		delta_dist->x = 1;
	else
		delta_dist->x = fabs(1 / ray_dir->x);
	if (ray_dir->x == 0)
		delta_dist->y = 0;
	else if (ray_dir->y == 0)
		delta_dist->y = 1;
	else
		delta_dist->y = fabs(1 / ray_dir->y);
}

void ft_step(t_ray *ray, t_plr *plr)
{
	if (ray->ray_dir.x < 0)
	{
		ray->stepx = -1;
		ray->side_dist.x = (plr->coor.x - ray->mapx) * ray->delta_dist.x;
	}
	else
	{
		ray->stepx = 1;
		ray->side_dist.x = (ray->mapx + 1.0 - plr->coor.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->stepy = -1;
		ray->side_dist.y = (plr->coor.y - ray->mapy) * ray->delta_dist.y;
	}
	else
	{
		ray->stepy = 1;
		ray->side_dist.y = (ray->mapy + 1.0 - plr->coor.y) * ray->delta_dist.y;
	}
}

void	ft_dda(t_ray *ray, char **map)
{
	while (ray->hit != 1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->mapx += ray->stepx;
			if (ray->stepx > 0)
				ray->side = so;
			else
				ray->side = no;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->mapy += ray->stepy;
			if (ray->stepy > 0)
				ray->side = ea;
			else
				ray->side = we;
		}
		if (map[ray->mapx][ray->mapy] == '1')
			ray->hit = 1;
	}
}

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
		ray->perp_wall_dist = (ray->mapx - plr->coor.x + (1 - ray->stepx) / 2) / ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->mapy - plr->coor.y + (1 - ray->stepy) / 2) / ray->ray_dir.y;
	ray->line_h = (int)(height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_h / 2 + height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + height / 2;
	if (ray->draw_end >= height)
		ray->draw_end = height - 1;
}

int	raycast(t_wolf *wolf)
{
	t_ray	ray;
	float	*zbuffer;

	ray.x = 0;
	zbuffer = (float *)ft_memalloc(sizeof(int) * wolf->mlx.width);
	clear_arr(&wolf->mlx, wolf->tex);
	while (ray.x < wolf->mlx.width)
	{
		ray.camx = 2 * ray.x / (float)wolf->mlx.width - 1;
		ray.ray_dir.x = wolf->plr.dir.x + wolf->plr.plane.x * ray.camx;
		ray.ray_dir.y = wolf->plr.dir.y + wolf->plr.plane.y * ray.camx;
		ray.mapx = (int)(wolf->plr.coor.x);
		ray.mapy = (int)(wolf->plr.coor.y);
		ray.hit = 0;
		ft_delta_dist(&ray.ray_dir, &ray.delta_dist);
		ft_step(&ray, &wolf->plr);
		ft_dda(&ray, wolf->map);
		ft_perp_wall(&ray, &wolf->plr, wolf->mlx.height);
		zbuffer[ray.x] = ray.perp_wall_dist;
		ft_texture_wall(wolf->tex, &ray, &wolf->plr, &wolf->mlx);
		ft_texture_cell_floor(&ray, &wolf->mlx, &wolf->plr, wolf->tex);
		ray.x++;
	}
	ft_sprite(wolf, zbuffer);
	free(zbuffer);
	return (0);
}