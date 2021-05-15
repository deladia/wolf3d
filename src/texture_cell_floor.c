#include "wolf3d.h"

void	ft_floor_wall(t_ray *ray, t_buf_floor *param)
{
	if (ray->side == so && ray->ray_dir.x > 0)
		param->floor_wall = (t_xy){(float)ray->mapx, (float)ray->mapy + ray->wall_x};
	else if (ray->side == no && ray->ray_dir.x < 0)
		param->floor_wall = (t_xy){(float)ray->mapx + 1.0f, (float)ray->mapy + ray->wall_x};
	else if (ray->side == ea && ray->ray_dir.y > 0)
		param->floor_wall = (t_xy){(float)ray->mapx + ray->wall_x, (float)ray->mapy};
	else
		param->floor_wall = (t_xy){(float)ray->mapx + ray->wall_x, (float)ray->mapy + 1};
}

void	ft_color_floor(t_texture *tmp, t_buf_floor *param, t_mlx *mlx, int ind)
{
	// t_texture	*tmp;

	// tmp = find_texture(tex_list, c);
	if (tmp == NULL)
		ft_exit("Not found texture in RayCast");
	if (tmp->image != NULL)
	{
		param->floor_tex_x = (int)(param->cur_floor.x * tmp->width) % tmp->width;
		param->floor_tex_y = (int)(param->cur_floor.y * tmp->height) % tmp->height;
		mlx->addr[ind] = tmp->image[tmp->width * param->floor_tex_y + param->floor_tex_x];
	}
}

void	ft_texture_cell_floor(t_ray *ray, t_mlx *mlx, t_plr *plr, t_texture *tex_list)
{
	t_buf_floor	param;
	t_texture	*tmp;

	ft_floor_wall(ray, &param);
	// param.dist_wall = ray->perp_wall_dist;
	// param.dist_plr = 0.0f;
	// //? зачем этот if?
	// if (ray->draw_end < 0)
	// 	ray->draw_end = mlx->height;
	param.y = ray->draw_end + 1;
	while (param.y < mlx->height)
	{
		param.dist_cur = mlx->height / (2.0f * param.y - mlx->height);
		param.weight = (param.dist_cur /* - param.dist_plr*/) / (ray->perp_wall_dist/*param.dist_wall - param.dist_plr*/);
		param.cur_floor.x = param.weight * param.floor_wall.x + (1.0f - param.weight) * plr->coor.x;
		param.cur_floor.y = param.weight * param.floor_wall.y + (1.0f - param.weight) * plr->coor.y;
		tmp = find_texture(tex_list, c);
		ft_color_floor(tmp, &param, mlx, ray->x + param.y * mlx->width);
		tmp = find_texture(tex_list, f);
		ft_color_floor(tmp, &param, mlx, ray->x + (mlx->height - param.y) * mlx->width);
		// tmp = find_texture(tex_list, c);
		// if (tmp == NULL)
		// 	ft_exit("Not found texture in RayCast");
		// if (tmp->image != NULL)
		// {
		// 	param.floor_tex_x = (int)(param.cur_floor.x * tmp->width) % tmp->width;
		// 	param.floor_tex_y = (int)(param.cur_floor.y * tmp->height) % tmp->height;
		// 	mlx->addr[ray->x + param.y * mlx->width] = tmp->image[tmp->width * param.floor_tex_y + param.floor_tex_x];
		// }

		// tmp = find_texture(tex_list, f);
		// if (tmp == NULL)
		// 	ft_exit("Not found texture in RayCast");
		// if (tmp->image != NULL)
		// {
		// 	param.floor_tex_x = (int)(param.cur_floor.x * tmp->width) % tmp->width;
		// 	param.floor_tex_y = (int)(param.cur_floor.y * tmp->height) % tmp->height;
		// 	mlx->addr[ray->x + (mlx->height - param.y) * mlx->width] = tmp->image[tmp->width * param.floor_tex_y + param.floor_tex_x];
		// }
		param.y++;
	}
}