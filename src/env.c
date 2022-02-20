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
		ft_lstadd_back(&lst, ft_lstnew(strdup(*env)));
		env++;
	}
	return (lst);
}

int cmd_env(t_cmd *cmd, t_data *data)
{
	t_list *env = data->env;

	if (cmd->cmd[1])
		ft_putstr_fd("No options or arguments needed\n",2);
	while (env)
	{
		ft_putstr_fd((char *) env->content, cmd->fd_out);
		ft_putstr_fd("\n", cmd->fd_out);
		env = env->next;
	}
	return (0);
}

//Do not free!!
char *getvalue(char *s, t_data *data)
{
	int j;
	t_list *lst;

	j = ft_strlen(s);
	lst = data->env;
	while (lst)
		if (!ft_strncmp(s, (char *) lst->content, j)
				&& ft_strlen((char *) lst->content) >= j
				&& ((char *) lst->content)[j] == '=')
			return (lst->content + ft_strlen(s) + 1);
		else
			lst = lst->next;
	return (NULL); // plus logique de return NULL ici et pas le malloc(1) car sinon faut free dans des cas particuliers c relou
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
