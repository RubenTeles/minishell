#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "../../includes/minishell.h"
#include "../../includes/ft_string.h"

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
	char	***comando;
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
	while ((*temp) && (*temp)->token)
	{
		if (!strcmp("<", (*temp)->token) || !strcmp("<<", (*temp)->token)
			|| !strcmp(">", (*temp)->token) || !strcmp(">>", (*temp)->token))
			break ;
		if (!strcmp("|", (*temp)->token))
		{
			free ((*temp)->token);
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
		if ((i) && (!strcmp("|", temp->token) || !strcmp("<", temp->token)
				|| !strcmp("<<", temp->token) || !strcmp(">", temp->token)
				|| !strcmp(">>", temp->token)))
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
	aux->commands = malloc((sizeof(char *) * (i + 1)));
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
		if (!line[*i + len])
			break ;
		if (ignore == '"' && line[*i + len] == '\\' && ++len && line[*i + len]
			&& line[*i + len] == '"')
			len++;
		if (!ignore && (line[*i + len] == '\"' || line[*i + len] == '\''))
			ignore = line[*i + len];
		len++;
		if (ignore && line[*i + len] == ignore && len++)
			ignore = 0;
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

void	ft_malloc_comando(t_data **data, t_data temp)
{
	int i;

	i = 0;
	while (temp.start)
	{
		temp.start = temp.start->next;
		i++;
	}
	(*data)->comando = malloc(sizeof(char **) * (i + 1));
	(*data)->comando[i] = NULL;
}

int	ft_get_size_command(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}

t_cms	*ft_free_start(t_cms	*start)
{
	t_cms	*temp;

	temp = start->next;
	free(start->commands);
	free(start);
	return (temp);
}

//This function will make all parser functions and store them in the *comando[][] array
void	get_comando(char *line, t_data *data)
{
	t_data	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->input = ft_split_line(line, 0, NULL, NULL);
	data->start = ft_parameters(data->input, NULL, NULL);
	temp = data;
	ft_malloc_comando(&data, *temp);
	while (data->start)
	{
		if (data->start->commands && data->start->commands[0])
			data->comando[j] = malloc(sizeof(char *)
					* (ft_get_size_command(data->start->commands) + 1));
		while (data->comando && data->comando[j]
			&& data->start->commands && data->start->commands[i])
			data->comando[j][i++] = data->start->commands[i];//Aqui o array*** recebe os tokens consoante o numero do comando...
		data->comando[j][i] = NULL;
		data->start = ft_free_start(data->start);
		i = 0;
		j++;
	}
	data->comando[j] = NULL;
}

void	ft_free_input(t_token *input)
{
	if (input)
	{
		ft_free_input(input->next);
		free(input);
	}
}

void	ft_free_data(t_data *data, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->comando[j])
	{
		while (data->comando[j][i])
			free(data->comando[j][i++]);
		free(data->comando[j]);
		i = 0;
		j++;
	}
	if (data->input)
		ft_free_input(data->input);
	if (data->comando)
		free(data->comando);
	if (data->start)
		printf("Falta limpar o start...\n");
	if (line)
		free(line);
}

char	*ft_new_aux(char *aux, char index)
{
	char	*temp;
	int		i;

	i = 0;
	temp = aux;
	while (aux && aux[i])
		i++;
	aux = malloc(sizeof(char) * i + 1 + 1);
	i = 0;
	if (!aux)
		return (temp);
	while (temp && temp[i])
	{
		aux[i] = temp[i];
		i++;
	}
	if (temp)
		free (temp);
	if (aux)
		aux[i] = index;
	aux[i + 1] = '\0';
	return (aux);
}

char	*ft_formattoken(char *token)
{
	char	*aux;
	int		i;
	int		j;
	int		cote;

	i = 0;
	j = 0;
	cote = 0;
	aux = NULL;
	while (token && token[i])
	{
		if (!cote && (token[i] == '\'' || token[i] == '"'))
			cote = token[i++];
		if (cote == '"' && token[i] == '\\' && token[i + 1] && token[i + 1] == '"' && ++i && ++j)
			aux = ft_new_aux(aux, token[i++]);
		if (!token[i])
			break ;
		if (cote != '\'' && token[i] == '$' && ++i)
		{
			while (isalnum(token[i]))
				i++;
			aux = ft_putvar(token, i, aux);
			//qualquervar = (terminal())->variable_env(user);
			//(string())->join(algo, qualquervar);
			//free(qualquervar);
		}
		if (!cote && token[i] && (token[i] != '\'' || token[i] != '"') && ++j)
		{
			aux = ft_new_aux(aux, token[i++]);
			continue ;
		}
		if (cote && token[i] && token[i] == cote && i++)
			cote = 0;
		else if (token[i] && ++j)
			aux = ft_new_aux(aux, token[i++]);
	}
	if (aux)
		aux[j] = 0;
	free (token);
	return (aux);
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_data	data;
	int		i;
	int		j;

	(void) argv;
	(void) argc;
	(void) env;
	while (1)
	{
		i = 0;
		j = 0;
		line = readline("MyShell$ ");
		get_comando(line, &data);
		//teste de comandos//........
		while (data.comando[i])
		{
			printf("Command		->>>>>>>>>	");
			while (data.comando[i][j])
			{
				data.comando[i][j] = ft_formattoken(data.comando[i][j]);
				printf("-%s-\n",data.comando[i][j++]);
			}
			i++;
			j = 0;
			printf("\n\n");
		}
		//execve -> data->comando[X]	;
		//free -> tokens... line...Limpar o array comando[0][0]//
		//printf("%s\n", data.comando[0][0]); // <- Neste exemplo será mostrado o primeiro comando digitado...
		ft_free_data(&data, line);
		break ;
	}
}
