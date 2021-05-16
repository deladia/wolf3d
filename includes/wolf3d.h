#ifndef WOLF3D_H
# define WOLF3D_H
# include <mlx.h>
# include <math.h>
# include "libft.h"
# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_texture
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

typedef struct s_xy
{
	float		x;
	float		y;
}				t_xy;

typedef struct s_buf_spr
{
	t_xy		coor;
	t_xy		transform;
	float		inv_det;
	float		spr_screen;
	int			spr_width;
	int			spr_height;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_x;
	int			tex_y;
	int			stripe;
}				t_buf_spr;

typedef struct s_buf_tex
{
	float		step;
	float		tex_pos;
	int			tex_x;
	int			tex_y;
}				t_buf_tex;

typedef struct s_buf_floor
{
	t_xy		floor_wall;
	float		dist_cur;
	int			y;
	float		weight;
	t_xy		cur_floor;
	int			floor_tex_x;
	int			floor_tex_y;
}				t_buf_floor;

typedef struct s_ray
{
	int			x;
	float		camx;
	t_xy		ray_dir;
	int			mapx;
	int			mapy;
	t_xy		side_dist;
	t_xy		delta_dist;
	float		perp_wall_dist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			draw_start;
	int			draw_end;
	float		wall_x;
	int			line_h;
}				t_ray;

typedef struct s_plr
{
	t_xy		coor;
	t_xy		dir;
	t_xy		plane;
}				t_plr;

typedef struct s_mlx
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bit_per_pixel;
	int			line_len;
	int			endian;
}				t_mlx;

typedef struct s_coor_spr
{
	t_xy				coor;
	float				dist;
	int					key;
	struct s_coor_spr	*next;
}						t_coor_spr;

typedef struct s_key_flag
{
	int			move_w_s;
	int			move_a_d;
	int			rotate_l_r;
}				t_key_flag;

typedef struct s_wolf
{
	t_mlx		mlx;
	t_plr		plr;
	t_texture	*tex;
	t_texture	*spr;
	t_coor_spr	*coor_spr;
	char		**map;
	t_key_flag	flag;
	int			cnt_tex_spr;
}				t_wolf;

int				cnt_word(char **words);
size_t			cnt_digit(int nbr);
int				cnt_sep(char *str);
int				check_min_cnt_flags(int *valid);
int				read_map(char *flname, t_wolf *wolf);
void			ft_texadd_back(t_texture **lst, t_texture *new);
t_texture		*ft_texnew(int *tex, int w, int h, int key);
t_texture		*find_texture(t_texture *head, int key);
void			init_r(char **word, t_wolf *wolf);
void			init_tex(char **word, t_wolf *wolf, int key);
int				valid_map(t_wolf *wolf);
int				flood_fill(char **map, int i, int j);
int				raycast(t_wolf *wolf);
void			mlx_create(t_wolf *wolf);
void			ft_texture_wall(t_texture *tex_list,
					t_ray *ray, t_plr *plr, t_mlx *mlx);
void			ft_texture_cell_floor(t_ray *ray,
					t_mlx *mlx, t_plr *plr, t_texture *tex_list);
t_list			*ft_lstnew_cus(char const *content);
void			ft_exit(char *error_message);
void			ft_free_split(char **word);
void			ft_sprite(t_wolf *wolf, float *zbuffer);
void			ft_dist_sprite(t_coor_spr *spr_list, t_plr *plr);
void			parse_map(int fd, char *line, t_wolf *wolf);
void			ft_sort_sprite(t_coor_spr *head);
void			clear_arr(t_mlx *mlx, t_texture *head);
void			ft_perp_wall(t_ray *ray, t_plr *plr, int height);
int				ft_close(int param);
void			ft_move_w(t_plr *plr, char **map);
void			ft_move_a(t_plr *plr, char **map);
void			ft_move_s(t_plr *plr, char **map);
void			ft_move_d(t_plr *plr, char **map);

#endif