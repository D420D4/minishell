#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct s_cmd
{
	char *txt;
	struct s_cmd *cmd;
	struct s_cmd *success;
	struct s_cmd *failed;
} t_cmd;

t_cmd *new_cmd(char *s)
{
	t_cmd *cmd;
	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (0);
	cmd->cmd = 0;
	cmd->success = 0;
	cmd->failed = 0;
	cmd->txt = s;
}


int is_finish(char *txt)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (txt[i]==' ')
		i++;
	if (txt[i] == '(')
		return (0);
	while (txt[i])
	{
		if(!quote && txt[i] == '&'  && txt[i + 1] == '&')
			return (0);
		if(!quote && txt[i] == '|'  && txt[i + 1] == '|')
			return (0);
		if (txt[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (txt[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

char	*get_next(char *s, int *i)
{
	int j;
	int k;
	int	quote;
	int nb_par;

	j = 0;
	quote = 0;

	while (s[j]==' ')
		j++;
	if (s[j] == '(')
	{
		nb_par = 1;
		j++;
		while (s[j] && nb_par)
		{
			if (!quote && s[j] == '(')
				nb_par++;
			if (!quote && s[j] == ')')
				nb_par--;
			if (s[j] == '\'' && quote != 2)
				quote = (quote + 1) % 2;
			else if (s[j] == '\"' && quote != 1)
				quote = (quote + 2) % 4;
			j++;
		}
		k = j;
		while (s[j]==' ')
			j++;
		//TODO libft
		if (memcmp(s + j, "&&", 2) && memcmp(s + j, "||", 2) && s[j])
			return (0);
		*i = j;
		char *cp = malloc(k - 1);
		memcpy(cp, s + 1, k - 2);
		cp[k - 2] = 0;
		return cp;
	}

	int cmp = 0;
	while (s[j])
	{
		if (!quote && s[j] == ')')
			return (0);
		if (!memcmp(s + j, "&&", 2) || !memcmp(s + j, "||", 2))
		{
			*i = j;
			cmp++;
		}

		if (cmp == 2 || !s[j + 1])
		{
			if (cmp == 2)
				*i = j;
			else
				j = *i;
			char *cp = malloc(j + 1);
			memcpy(cp, s, j);
			cp[j] = 0;
			return cp;
		}
		if (s[j] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[j] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		j++;
	}
	return (0);
}

int progress(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (is_finish(cmd->txt))
		return 0;
	int	i = 0;
	char *ncmd = get_next(cmd->txt, &i);
	if (!ncmd)
		return (0);
	char *nncmd = strdup(cmd->txt + i + 2);

	if (cmd->txt[i] == '&')
		cmd->success = new_cmd(nncmd);
	if (cmd->txt[i] == '|')
		cmd->failed= new_cmd(nncmd);

	cmd->cmd = new_cmd(ncmd);
	progress(cmd->cmd);
	progress(cmd->success);
	progress(cmd->failed);

	return (1);
}

void printn(int n)
{
	while (n--)
		printf("_");
}

void print_cmd(t_cmd *cmd, int n)
{
	int	i;

	i = 0;
	if (!cmd)
	{
		printf("\n");
		return;
	}

	//printn(n);
	printf("%s\n", cmd->txt);
	printn(n);
	printf("c :");
	print_cmd(cmd->cmd, n + 2);
	printn(n);
	printf("1 :");
	print_cmd(cmd->success, n + 2);
	printn(n);
	printf("0 :");
	print_cmd(cmd->failed, n + 2);
}

int main()
{
	char *t= "(t1 't)' && t2 \"(wpeork)\") || t3 || t4";

	t_cmd *cmd = new_cmd(t);

	progress(cmd);

	print_cmd(cmd,0);


/*
	t1 't'
		1 : t2 "(wpeork)"
			0 : t3
				0 : t3
		0 : t3
			0 : t4
	return 0;*/
}
