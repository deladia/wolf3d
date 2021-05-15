#include "wolf3d.h"


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

int	cnt_sep(char *str)
{
	int	cnt_sep;
	int	i;

	cnt_sep = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			cnt_sep++;
		i++;
	}
	return (cnt_sep);
}

int	check_min_cnt_flags(int *valid)
{
	int	i;

	i = 0;
	while(i < 8)
	{
		if (valid[i] != 1)
			return (-5);
		i++;
	}
	return (0);
}

int	cnt_word(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	ft_free_split(char **word)
{
	int	i;

	i = 0;
	while (word[i] != NULL)
	{
		free(word[i]);
		word[i] = NULL;
		i++;
	}
	free(word);
}

size_t	cnt_digit(int nbr)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

t_list	*ft_lstnew_cus(char const *content)
{
	t_list *new;

	new = (t_list *)ft_memalloc(sizeof(t_list));
	new->content = ft_strdup(content);
	return (new);
}

void	ft_exit(char *error_message)
{
	ft_putendl(error_message);
	exit (-1);
}