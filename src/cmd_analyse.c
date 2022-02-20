//
// Created by plefevre on 2/14/22.
//
#include "../includes/minishell.h"

int is_in(char c, char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (c == s[i])
			return (1);
		else
			i++;
	return (0);
}

char *substring(char *s, char *c)
{
	int i;
	char *ss;

	i = 1;
	while (s[i] && !is_in(s[i], c))
		i++;
	ss = malloc(i + 1);
	if (!ss)
		return (0);
	i = 0;
	while (s[i] && ( i == 0 || !is_in(s[i], c)))
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = 0;
	return (ss);
}

void do_var(char **s, int *f, t_data *data)
{
	char *ss;
	char *var_name;
	char *var_value;

	var_name = substring((*s) + *f, " $\"");
	if (!var_name || ft_strlen(var_name) == 1)
	{
		free(var_name);
		return;
	}
	if (ft_memcmp(var_name, "$?", 3))
	{
		var_value = getvalue(var_name + 1, data);
	}
	else
		var_value = ft_itoa(g_exit_status);
	// si var_value = NULL (la var existe pas dans env), ft_strlen  et ft_memcpy sont secure donc pas de soucis
	int size = ft_strlen(*s) - ft_strlen(var_name) + ft_strlen(var_value) + 1;
	ss = malloc(size);
	if (!ss)
	{
		free(var_name);
		return ;
	}
	ft_memcpy(ss, *s, *f);
	ft_memcpy(ss + *f, var_value, ft_strlen(var_value));
	ft_memcpy(ss + *f + ft_strlen(var_value),
			  (*s) + *f + ft_strlen(var_name), ft_strlen((*s) + *f + ft_strlen(var_name)) + 1);
	free(*s);
	free(var_name);
	*f = *f + ft_strlen(var_value) - 1;
	*s = ss;
}

int inner_quote_1(char **s, int *i, t_data *data)
{
	char	*ss;
	int		f;

	f = *i + 1;
	while ((*s)[f] && (*s)[f] != '"')
	{
		if ((*s)[f] == '$')
			do_var(s, &f, data);
		f++;
	}
	if (!(*s)[f])
	{
		free(*s);
		return (1);
	}
	ss = malloc(ft_strlen(*s) - 1);
	ss[ft_strlen(*s)-2] = 0;
	ft_memcpy(ss, *s,*i);
	ft_memcpy(ss + *i, *s + *i + 1,f - *i - 1);
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
	ss[ft_strlen(*s)-2] = 0;
	ft_memcpy(ss, *s,*i);
	ft_memcpy(ss + *i, *s + *i + 1,f - *i - 1);
	ft_memcpy(ss + f - 1, *s + f + 1, ft_strlen(*s + f + 1));
	*i = f - 1;

	free(*s);
	*s = ss;
	return (0);
}

char	*transform(char *original, t_data *data)
{
	char	*ss;
	int		i;

	ss = ft_strdup(original);
	if (!ss)
		return (0);
	i = 0;
	while (ss[i])
	{
		if (ss[i] == '"')
			if (inner_quote_1(&ss, &i, data))
				return (0);
		if (ss[i] == '\'')
			if (inner_quote_2(&ss, &i))
				return (0);
		if (ss[i] == '$')
			do_var(&ss, &i, data);
		if (is_in('*', ss + i))
			do_wildcards(&ss, &i); // marche partiellement (faut encore split selon les espaces et trier par ordre ascii, en progress)
		i++;
	}
	return (ss);
}
