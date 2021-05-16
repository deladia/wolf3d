#include "wolf3d.h"

void	init_r(char **word, t_wolf *wolf)
{
	if (cnt_word(word) != 3)
		ft_exit("Wrong count param arg R");
	wolf->mlx.width = ft_atoi(word[1]);
	wolf->mlx.height = ft_atoi(word[2]);
	if (ft_strlen(word[1]) != cnt_digit(wolf->mlx.width)
		|| ft_strlen(word[2]) != cnt_digit(wolf->mlx.width))
		ft_exit("Wrong format number arg R");
	if (wolf->mlx.width > WIDTH || wolf->mlx.width < 1)
		wolf->mlx.width = WIDTH;
	if (wolf->mlx.height > HEIGHT || wolf->mlx.height < 1)
		wolf->mlx.height = HEIGHT;
}

void	parse_texture(char *flname, t_wolf *wolf, int key)
{
	void		*ptr;
	int			bpp;
	int			line_len;
	int			endian;
	t_texture	*texture;

	texture = (t_texture *)ft_memalloc(sizeof(t_texture));
	texture->key = key;
	ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr,
			flname, &texture->width, &texture->height);
	if (ptr == NULL)
		ft_exit("Texture not .xpm format");
	texture->image = (int *)mlx_get_data_addr(ptr, &bpp, &line_len, &endian);
	if (key == s)
	{
		texture->key = wolf->cnt_tex_spr++;
		ft_texadd_back(&wolf->spr, texture);
	}
	else
		ft_texadd_back(&wolf->tex, texture);
}

void	parse_color(char *word, t_wolf *wolf, int key)

{
	int		i;
	int		tmp_color;
	char	**color;
	int		clr;

	i = 0;
	clr = 0;
	color = ft_strsplit(word, ',');
	if (cnt_word(color) != 3 || cnt_sep(word) != 2)
		ft_exit("Wrong count arg F || C");
	while (i < 3)
	{
		tmp_color = ft_atoi(color[i]);
		if (cnt_digit(tmp_color) == ft_strlen(color[i])
			&& tmp_color >= 0 && tmp_color <= 255)
			clr |= tmp_color << ((2 - i) * 8);
		else
			ft_exit("Wrong color range arg F || C");
		i++;
	}
	ft_texadd_back(&wolf->tex, ft_texnew(NULL, clr, 0, key));
	ft_free_split(color);
}

void	init_tex(char **word, t_wolf *wolf, int key)
{
	if (cnt_word(word) != 2)
		ft_exit("Wrong count param arg");
	if (ft_strncmp(&(word[1][ft_strlen(word[1]) - 4]), ".xpm", 4) == 0)
		parse_texture(word[1], wolf, key);
	else if (key == f || key == c)
		parse_color(word[1], wolf, key);
}
