/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/20 12:28:38 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **array, int i, int j)
{
	char	*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

int	env_cmp(const char *str1, const char *str2)
{
	int		i;

	i = 0;
	while ((str1[i] && str2[i]) && str1[i] == str2[i]
		&& str1[i] != '=' && str2[i] != '=')
		i++;
	if (!str1[i] && !str2[i])
		return (0);
	if (str1[i] == '=' && str2[i] != '=')
		return (0 - str2[i]);
	else if (str2[i] == '=' && str1[i] != '=')
		return (str1[i] - 0);
	return (str1[i] - str2[i]);
}

void	quicksort(char **array, int start, int end)
{
	int		i;
	int		j;
	char	*pivot;

	i = start;
	j = end;
	if (j - i < 1)
		return ;
	pivot = array[i];
	while (j > i)
	{
		while (env_cmp(array[i], pivot) <= 0 && i < end && j > i)
			i++;
		while (env_cmp(array[j], pivot) >= 0 && j > start && j >= i)
			j--;
		if (j > i)
			swap(array, i, j);
	}
	swap(array, start, j);
	quicksort(array, start, j - 1);
	quicksort(array, j + 1, end);
}

void	sort_env(char **array, int start, int length)
{
	if (length <= 1 || start >= length)
		return ;
	quicksort(array, start, length - 1);
	return ;
}
