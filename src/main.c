#include "wolf3d.h"

int	main(int argc, char **argv)
{
	t_wolf	*wolf;

	wolf = (t_wolf *)ft_memalloc(sizeof(t_wolf));
	wolf->cnt_tex_spr = 0;
	wolf->mlx.mlx_ptr = mlx_init();
	if (argc != 2)
		ft_exit("Wrong number of parameters");
	read_map(argv[1], wolf);
	mlx_create(wolf);
	ft_exit("OK");
	return (0);
}