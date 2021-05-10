#include "libft.h"

char	ft_strchr_ind(const char *str, int ch)
{
	int		i;

	i = 0;
	while (str[i] != ch)
	{
		if (str[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (i + 1);
}