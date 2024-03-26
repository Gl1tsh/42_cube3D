/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:13:40 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/26 19:13:52 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*copy;
	size_t	len;

	len = 0;
	while (len < n && str[len])
		len++;
	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, str, len);
	copy[len] = '\0';
	return (copy);
}
