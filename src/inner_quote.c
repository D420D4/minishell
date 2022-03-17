/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefevre <plefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:31:58 by plefevre          #+#    #+#             */
/*   Updated: 2022/03/16 16:31:59 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*substring(char *s, char *c)
{
	int		i;
	char	*ss;

	i = 1;
	while (s[i] && !is_in(s[i], c))
		i++;
	if (i == 1 && (s[i] == '\0' || s[i] == ' '))
		return (NULL);
	ss = malloc(i + 1);
	if (!ss)
		return (0);
	i = 0;
	while (s[i] && (i == 0 || !is_in(s[i], c)))
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = 0;
	return (ss);
}

static int	do_var_init(char **var_name, char **var_value, int *f, t_data *data)
{
	if (!*var_name)
	{
		(*f)++;
		free(*var_name);
		return (1);
	}
	if (ft_memcmp(*var_name, "$?", 2))
		*var_value = strdup(getvalue(*var_name + 1, data));
	else
		*var_value = ft_itoa(g_exit_status);
	return (0);
}

void	do_var(char **s, int *f, t_data *data)
{
	char	*ss;
	char	*var_name;
	char	*var_value;

	var_name = substring((*s) + *f, "' $\"");
	if (do_var_init(&var_name, &var_value, f, data))
		return ;
	ss = malloc(ft_strlen(*s) - ft_strlen(var_name) + ft_strlen(var_value) + 1);
	if (!ss || !var_value)
	{
		free(var_name);
		if (var_value)
			free(var_value);
		return ;
	}
	ft_memcpy(ss, *s, *f);
	ft_memcpy(ss + *f, var_value, ft_strlen(var_value));
	ft_memcpy(ss + *f + ft_strlen(var_value),
		(*s) + *f + ft_strlen(var_name), ft_strlen((*s)
			+ *f + ft_strlen(var_name)) + 1);
	free(*s);
	*f = *f + ft_strlen(var_value);
	*s = ss;
	free(var_value);
	free(var_name);
}

int	inner_quote_1(char **s, int *i, t_data *data)
{
	char	*ss;
	int		f;

	f = *i + 1;
	while ((*s)[f] && (*s)[f] != '"')
	{
		if ((*s)[f] == '$')
			do_var(s, &f, data);
		else
			f++;
	}
	if (!(*s)[f])
	{
		free(*s);
		return (1);
	}
	ss = malloc(ft_strlen(*s) - 1);
	ss[ft_strlen(*s) - 2] = 0;
	ft_memcpy(ss, *s,*i);
	ft_memcpy(ss + *i, *s + *i + 1, f - *i - 1);
	ft_memcpy(ss + f - 1, *s + f + 1, ft_strlen(*s + f + 1));
	*i = f - 1;
	free(*s);
	*s = ss;
	return (0);
}

int	inner_quote_2(char **s, int *i)
{
	char	*ss;
	int		f;

	f = *i + 1;
	while ((*s)[f] && (*s)[f] != '\'')
		f++;
	if (!(*s)[f])
	{
		free(*s);
		return (1);
	}
	ss = malloc(ft_strlen(*s) - 1);
	ss[ft_strlen(*s) - 2] = 0;
	ft_memcpy(ss, *s,*i);
	ft_memcpy(ss + *i, *s + *i + 1, f - *i - 1);
	ft_memcpy(ss + f - 1, *s + f + 1, ft_strlen(*s + f + 1));
	*i = f - 1;
	free(*s);
	*s = ss;
	return (0);
}
