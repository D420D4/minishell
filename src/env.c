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

char	**env_to_tab(t_list *env)
{
	int		size;
	int		i;
	char	**tab;

	size = ft_lstsize(env);
	tab = malloc((size + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while(env)
	{
		tab[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
