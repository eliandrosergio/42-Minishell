/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:18:22 by efaustin          #+#    #+#             */
/*   Updated: 2024/05/20 20:18:23 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_position;
	t_list	*last_lst;

	if (!lst)
		return (NULL);
	lst_position = lst;
	while (lst_position)
	{
		last_lst = lst_position;
		lst_position = lst_position -> next;
	}
	return (last_lst);
}
