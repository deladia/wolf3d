#include "wolf3d.h"

void	move_map(t_list *list, t_wolf *wolf)
{
	t_list	*tmp;
	t_list	*ff;
	int		i;

	wolf->map = (char **)ft_memalloc((sizeof(char *) + 1) * ft_lstsize(list));
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		wolf->map[i] = (char *)tmp->content;
		ff = tmp;
		tmp = tmp->next;
		free(ff);
		i++;
	}
	wolf->map[i] = NULL;
}

void	parse_map(int fd, char *line, t_wolf *wolf)
{
	t_list	*list;

	list = ft_lstnew_cus(line);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
			ft_exit("Map broken");
		ft_lstadd_back(&list, ft_lstnew_cus(line));
		free(line);
	}
	move_map(list, wolf);
	valid_map(wolf);
}
