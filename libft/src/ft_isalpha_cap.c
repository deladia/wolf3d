#include "libft.h"

int	ft_isalpha_cap(int ch)
{
	if ('A' <= ch && ch <= 'Z')
	{
		return (1);
	}
	return (0);
}
