/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:19:10 by efaustin          #+#    #+#             */
/*   Updated: 2024/05/20 20:19:11 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_holder;
	t_list	*element;

	if (!*lst)
		return ;
	element = *lst;
	while (element)
	{
		lst_holder = element->next;
		ft_lstdelone(element, del);
		element = lst_holder;
	}
	*lst = NULL;
}
