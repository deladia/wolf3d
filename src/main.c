#include "wolf3d.h"

int	main(int argc, char **argv)
{
	t_wolf	*wolf;

	wolf = (t_wolf *)ft_memalloc(sizeof(t_wolf));
	wolf->mlx.mlx_ptr = mlx_init();
	if (argc != 2)
		ft_exit("Wrong number of parameters");
	if (read_map(argv[1], wolf) != 0)
		ft_putendl("Error");
	ft_exit("OK");
	return (0);
}