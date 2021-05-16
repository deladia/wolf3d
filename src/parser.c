#include "wolf3d.h"

void	check_flag_1(char **word, t_wolf *wolf, int *valid)
{
	if (ft_strcmp_len(word[0], "WE") == 0 && valid[we] == 0)
	{
		valid[we] = 1;
		init_tex(word, wolf, we);
	}
	else if (ft_strcmp_len(word[0], "S") == 0)
	{
		valid[s] = 1;
		init_tex(word, wolf, s);
	}
	else if (ft_strcmp_len(word[0], "F") == 0 && valid[f] == 0)
	{
		valid[f] = 1;
		init_tex(word, wolf, f);
	}
	else if (ft_strcmp_len(word[0], "C") == 0 && valid[c] == 0)
	{
		valid[c] = 1;
		init_tex(word, wolf, c);
	}
	else
		ft_exit("Flag not found");
}

void	check_flag(char **word, t_wolf *wolf, int *valid)
{
	if (ft_strcmp_len(word[0], "R") == 0 && valid[r] == 0)
	{
		valid[r] = 1;
		init_r(word, wolf);
	}
	else if (ft_strcmp_len(word[0], "NO") == 0 && valid[no] == 0)
	{
		valid[no] = 1;
		init_tex(word, wolf, no);
	}
	else if (ft_strcmp_len(word[0], "SO") == 0 && valid[so] == 0)
	{
		valid[so] = 1;
		init_tex(word, wolf, so);
	}
	else if (ft_strcmp_len(word[0], "EA") == 0 && valid[ea] == 0)
	{
		valid[ea] = 1;
		init_tex(word, wolf, ea);
	}
	else
		check_flag_1(word, wolf, valid);
}

void	parse_flag(char *line, t_wolf *wolf, int *valid)
{
	char	**word;

	word = ft_strsplit(line, ' ');
	check_flag(word, wolf, valid);
	ft_free_split(word);
}

int	read_map(char *flname, t_wolf *wolf)
{
	int		fd;
	char	*line;
	int		*valid;

	fd = open(flname, O_RDONLY);
	if (fd < 0)
		ft_exit("Can't open file");
	valid = (int *)ft_memalloc(sizeof(int) * 8);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_isalpha(line[0]) == 1)
			parse_flag(line, wolf, valid);
		else if (ft_isdigit((int)line[0]) == 1)
			parse_map(fd, line, wolf);
		free(line);
	}
	close(fd);
	if (check_min_cnt_flags(valid) != 0)
		ft_exit("Not found one of flag");
	free(valid);
	return (0);
}
