#include "wolf3d.h"

t_list	*ft_lstnew_cus(char const *content)
{
	t_list	*new;

	new = (t_list *)ft_memalloc(sizeof(t_list));
	new->content = ft_strdup(content);
	return (new);
}

void	ft_texadd_back(t_texture **lst, t_texture *new)
{
	t_texture	*last;

	last = *lst;
	if (new && *lst)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	else
		*lst = new;
}

t_texture	*ft_texnew(int *tex, int w, int h, int key)
{
	t_texture	*list;

	list = (t_texture *)ft_memalloc(sizeof(t_texture));
	list->image = tex;
	list->width = w;
	list->height = h;
	list->key = key;
	list->next = NULL;
	return (list);
}

void	ft_exit(char *error_message)
{
	ft_putendl(error_message);
	exit (-1);
}
