#include "wolf3d.h"

t_coor_spr	*ft_sort_sprite(t_coor_spr *root)
{
    t_coor_spr *new_root = NULL;

    while (root != NULL)
    {
        t_coor_spr *node = root;
        root = root->next;
        if ( new_root == NULL || node->dist < new_root->dist )
        {
            node->next = new_root;
            new_root = node;
        }
        else
        {
            t_coor_spr *current = new_root;
            while ( current->next != NULL && !( node->dist < current->next->dist ) )
            {                   
                  current = current->next;
            }                

            node->next = current->next;
            current->next = node;
        }
    }

    return (new_root);
}

void	ft_dist_sprite(t_coor_spr *spr_list, t_plr *plr)
{
	t_coor_spr	*tmp;

	tmp = spr_list;
	while (tmp != NULL)
	{
		tmp->dist = ((plr->coor.x - tmp->coor.x) * (plr->coor.x - tmp->coor.x) + (plr->coor.y - tmp->coor.y) * (plr->coor.y - tmp->coor.y));
		tmp = tmp->next;
	}
}

void	ft_param_sprite(t_buf_spr *param, t_coor_spr *tmp, t_plr *plr, t_mlx *mlx)
{
	param->coor.x = tmp->coor.x - plr->coor.x;
	param->coor.y = tmp->coor.y - plr->coor.y;
	param->inv_det = 1.0f / (plr->plane.x * plr->dir.y - plr->dir.x * plr->plane.y);

	param->transform.x = param->inv_det * (plr->dir.y * param->coor.x - plr->dir.x * param->coor.y);
    param->transform.y = param->inv_det * (-plr->plane.y * param->coor.x + plr->plane.x * param->coor.y);
	// printf("%f %f\n", param->transform.x, param->transform.y);
	param->spr_screen = (int)((mlx->width / 2) * (1 + param->transform.x / param->transform.y));
	

}

void	ft_width_height_sprite(t_buf_spr *param, t_mlx *mlx)
{
	param->spr_height = abs((int)(mlx->height / (param->transform.y)));

	param->draw_start_y = -param->spr_height / 2 + mlx->height / 2;
	if(param->draw_start_y < 0)
		param->draw_start_y = 0;

	param->draw_end_y = param->spr_height / 2 + mlx->height / 2;
    if(param->draw_end_y >= mlx->height)
		param->draw_end_y = mlx->height - 1;


    param->spr_width = abs((int)(mlx->height / (param->transform.y)));

	param->draw_start_x = -param->spr_width / 2 + param->spr_screen;
	if(param->draw_start_x < 0)
		param->draw_start_x = 0;

	// printf("%d %f\n", param->spr_width, param->spr_screen);
	param->draw_end_x = param->spr_width / 2 + param->spr_screen;
	if(param->draw_end_x >= mlx->width)
		param->draw_end_x = mlx->width - 1;
}

void	ft_draw_sprite(t_buf_spr *param, t_texture *tex_spr, t_mlx *mlx, float *zbuffer)
{
	int	stripe;
	int	tex_x;
	int	tex_y;
	int color;
	int	y;

	stripe = param->draw_start_x;
	// ft_putnbr(param->draw_end_x);
	while (stripe < param->draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-param->spr_width / 2 + param->spr_screen)) * tex_spr->width / param->spr_width) / 256;
		if (param->transform.y > 0 && stripe > 0 && stripe < mlx->height && param->transform.y < zbuffer[stripe])
		{
			y = param->draw_start_y;
			while (y < param->draw_end_y)
			{
				tex_y = ((((y) * 256 - mlx->height * 128 + param->spr_height * 128) * tex_spr->height) / param->spr_height) / 256;
				color = tex_spr->image[tex_x + tex_y * tex_spr->width];
				if ((color & 0xFFFFFF) != 0)
					mlx->addr[y * mlx->width + stripe] = color;
				y++;
			}
		}
		stripe++;
	}
}

void	ft_sprite(t_wolf *wolf, float *zbuffer)
{
	t_buf_spr	param;
	t_coor_spr	*tmp;
	t_texture	*tex_spr;

	ft_dist_sprite(wolf->coor_spr, &wolf->plr);
	tmp = ft_sort_sprite(wolf->coor_spr);
	// tmp = wolf->coor_spr;
	while (tmp != NULL)
	{
		ft_param_sprite(&param, tmp, &wolf->plr, &wolf->mlx);
		ft_width_height_sprite(&param, &wolf->mlx);
		tex_spr = find_texture(wolf->spr, tmp->key);
		if (tex_spr == NULL)
			tex_spr = wolf->spr;
		ft_draw_sprite(&param, tex_spr, &wolf->mlx, zbuffer);
		tmp = tmp->next;
	}
}