#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_token	t_token;
typedef struct s_cms	t_cms;
typedef struct s_data	t_data;

struct s_token{
	char	*token;
	t_token	*next;
};

struct s_cms {
	char	**commands;
	t_cms	*next;
};

struct s_data {
	char	*comando[20][20];
	t_token	*input;
	t_cms	*start;
};

/*
echo
teste*/

/*echo
tess*/

/*<<
ls
-la*/

void	ft_make_command(t_cms **aux, t_token **temp)
{
	int	i;

	i = 0;
	if (!strcmp("<", (*temp)->token) || !strcmp("<<", (*temp)->token)
		|| !strcmp(">", (*temp)->token) || !strcmp(">>", (*temp)->token))
	{
		(*aux)->commands[i++] = (*temp)->token;
		(*temp) = (*temp)->next;
	}
	while ((*temp))
	{
		if (!strcmp("<", (*temp)->token) || !strcmp("<<", (*temp)->token)
			|| !strcmp(">", (*temp)->token) || !strcmp(">>", (*temp)->token))
			break ;
		if (!strcmp("|", (*temp)->token))
		{
			(*temp) = (*temp)->next;
			break ;
		}
		(*aux)->commands[i++] = (*temp)->token;
		(*temp) = (*temp)->next;
	}
}

int	ft_count_param(t_token *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (!strcmp("|", temp->token) || !strcmp("<", temp->token)
			|| !strcmp("<<", temp->token) || !strcmp(">", temp->token)
			|| !strcmp(">>", temp->token))
			break ;
		i++;
		temp = temp->next;
	}
	return (i);
}

t_cms	*ft_parameters(t_token *tokens, t_cms *start, t_cms *end)
{
	t_cms	*aux;
	t_token	*temp;
	int		i;

	temp = tokens;
	if (!tokens)
		return (NULL);
	i = ft_count_param(temp);
	aux = malloc(sizeof(t_cms));
	aux->next = NULL;
	if (start == NULL)
		start = aux;
	else
		end->next = aux;
	end = aux;
	aux->commands = malloc(sizeof(char *) * (i + 1));
	aux->commands[i] = NULL;
	temp = tokens;
	ft_make_command(&aux, &temp);
	if (temp)
		start = ft_parameters(temp, start, end);
	return (start);
}

//Função que separa todo o conteudo da line retornando *out que é o comando flag ou pipe
char	*ft_get_command(const char *line, int *i)
{
	char	*out;
	int		len;
	int		new_i;
	int		ignore;

	ignore = 0;
	len = 0;
	while ((line[*i + len]) && (line[*i + len] != ' ' || ignore))
	{
		if (line[*i + len] == '\"' || line[*i + len] == '\'')
			ignore = !ignore;
		if (line[*i + len] == ignore && len++)
			break ;
		len++;
	}
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	new_i = len;
	while (--len >= 0 && line[*i + len])
		out[len] = line[*i + len];
	*i = new_i + *i;
	return (out);
}

//Função de inicio, percorre um input recebido da função readline, ou seja vai percorrer a line até chegar ao fim e ierá armaznar todos os objetos num **array...
t_token	*ft_split_line(const char *line, int i, t_token	*start, t_token	*end)
{
	t_token	*aux;

	while (line[i] != '\0')
	{
		if (line[i] != '\t' && line[i] != ' ')
		{
			aux = malloc(sizeof(t_token));
			aux->next = NULL;
			aux->token = ft_get_command(line, &i);
			if (start == NULL)
				start = aux;
			else
				end->next = aux;
			end = aux;
		}
		if (!line[i])
			break ;
		i++;
	}
	return (start);
}
//This function will make all parser functions and store them in the *comando[][] array
void	get_comando(char *line, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->input = ft_split_line(line, 0, NULL, NULL);
	data->start = ft_parameters(data->input, NULL, NULL);
	while (data->start)
	{
		//printf("=======		Commands	 ===========\n");
		while (data->start->commands && data->start->commands[i])
		{
			data->comando[j][i] = data->start->commands[i];
			//printf("%s\n", data->comando[j][i++]);
			i++;
		}
		data->start = data->start->next;
		i = 0;
		j++;
		//printf("\n\n");
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_data	*data;

	(void) argv;
	(void) argc;
	(void) env;
	while (1)
	{
		line = readline("MyShell$ ");
		get_comando(line, data);
		//execve -> data->comando[X]	;
		//free -> tokens... line...Limpar o array comando[0][0]//
		//printf("%s\n", data->comando[0][0]); // <- Neste exemplo será mostrado o primeiro comando digitado...
	}
}
