//
// Created by plefevre on 2/9/22.
//

#include "../includes/debug.h"
#include "../includes/minishell.h"

t_list	*parse_env(char **env)
{
	t_list	*lst;

	lst = 0;
	while (*env)
	{
		ft_lstadd_back(&lst, ft_lstnew(*env));
		env++;
	}
	return (lst);
}