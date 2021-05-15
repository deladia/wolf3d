/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:41:28 by deladia           #+#    #+#             */
/*   Updated: 2019/04/10 15:53:58 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int nb, int len)
{
	while (nb >= 10 || nb <= -10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		nb;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 1;
	if (n < 0)
		len = 2;
	nb = n;
	len = ft_len(nb, len);
	str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	if (n < 0)
		nb = n * (-1);
	while (len-- > 0)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
