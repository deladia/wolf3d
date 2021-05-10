#ifndef WOLF3D_H
# define WOLF3D_H
# include <mlx.h>
# include <math.h>
# include "libft.h"
# define WIDTH 1920
# define HEIGHT 1080


typedef struct 			s_texture
{
	int					*image;
	int					width;
	int					height;
	int					key;
	struct s_texture	*next;
}						t_texture;

enum	e_name
{
	r,
	no,
	so,
	ea,
	we,
	s,
	f,
	c
};

typedef struct	s_xy
{
	float		x;
	float		y;
}				t_xy;

typedef struct	s_plr
{
	t_xy		coor;
	t_xy		dir;
	t_xy		plane;
}				t_plr;

typedef struct	s_mlx
{
	int			width;
	int			height;
	void		*mlx_ptr;
}				t_mlx;

//key заглавная буква - коэф  и будет индекс спрайта в t_texture *spr
typedef struct	s_coor_spr
{
	t_xy				coor;
	int					key;
	struct s_coor_spr	*next;
}				t_coor_spr;

typedef struct	s_wolf
{
	t_mlx		mlx;
	t_plr		plr;
	t_texture	*tex;
	t_texture	*spr;
	t_coor_spr	*coor_spr;
	char		**map;
}				t_wolf;

int				cnt_word(char **words);
size_t			cnt_digit(int nbr);
int				cnt_sep(char *str);
int				check_min_cnt_flags(int *valid);
int				read_map(char *flname, t_wolf *wolf);

void			ft_texadd_back(t_texture **lst, t_texture *new);
t_texture		*ft_texnew(int *tex, int w, int h, int key);

void			init_r(char **word, t_wolf *wolf);
void			init_tex(char **word, t_wolf *wolf, int key);
int				valid_map(t_wolf *wolf);
int				flood_fill(char **map, int i, int j);

t_list			*ft_lstnew_cus(char const *content);
void			ft_exit(char *error_message);
void			ft_free_split(char **word);

#endif