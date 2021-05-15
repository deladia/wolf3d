#include "wolf3d.h"

t_texture	*find_texture(t_texture *head, int key)
{
	t_texture	*search;

	search = head;
	while(search != NULL)
	{
		if (search->key == key)
			return (search);
		search = search->next;
	}
	return (NULL);
}

void	ft_draw_texture(t_buf_tex *param, t_ray *ray, t_mlx *mlx, t_texture *tmp)
{
	int	y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		param->tex_y = (int)param->tex_pos & (tmp->height - 1);
		param->tex_pos += param->step;
		mlx->addr[ray->x + y * mlx->width] = tmp->image[tmp->height * param->tex_y + param->tex_x];
		y++;
	}
}

void	ft_texture_wall(t_texture *tex_list, t_ray *ray, t_plr *plr, t_mlx *mlx)
{
	t_buf_tex	param;
	t_texture	*tmp;

	if (ray->side == so || ray->side == no)
		ray->wall_x = plr->coor.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		ray->wall_x = plr->coor.x + ray->perp_wall_dist * ray->ray_dir.x;
	ray->wall_x = ray->wall_x - (int)ray->wall_x;
	tmp = find_texture(tex_list, ray->side);
	if (tmp == NULL)
		ft_exit("Not found texture in RayCast");
	param.tex_x = (int)(ray->wall_x * (float)tmp->width);
	if (((ray->side == no || ray->side == so) && ray->ray_dir.x > 0) || ((ray->side == we || ray->side == ea) && ray->ray_dir.y < 0))
		param.tex_x = tmp->width - param.tex_x - 1;
	param.step = 1.0f * (float)tmp->height / (float)ray->line_h;
	param.tex_pos = (ray->draw_start - mlx->height / 2 + ray->line_h / 2) * param.step;
	ft_draw_texture(&param, ray, mlx, tmp);
}