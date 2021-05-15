#include "wolf3d.h"

void	ft_swap_list(t_coor_spr *current, t_coor_spr *index)
{
	float	tmp_dist;
	t_xy	tmp_coor;
	int		tmp_key;

	tmp_dist = current->dist;
	tmp_coor = current->coor;
	tmp_key = current->key;
	current->dist = index->dist;
	current->key = index->key;
	current->coor = index->coor;
	index->dist = tmp_dist;
	index->coor = tmp_coor;
	index->key = tmp_key;
}

void	ft_sort_sprite(t_coor_spr *head)
{
	t_coor_spr	*current;
	t_coor_spr	*index;

	index = NULL;
	current = head;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (current->dist < index->dist)
				ft_swap_list(current, index);
			index = index->next;
		}
		current = current->next;
	}
}

void	ft_dist_sprite(t_coor_spr *spr_list, t_plr *plr)
{
	t_coor_spr	*tmp;

	tmp = spr_list;
	while (tmp != NULL)
	{
		tmp->dist = ((plr->coor.x - tmp->coor.x) * (plr->coor.x - tmp->coor.x)
				+ (plr->coor.y - tmp->coor.y) * (plr->coor.y - tmp->coor.y));
		tmp = tmp->next;
	}
}
