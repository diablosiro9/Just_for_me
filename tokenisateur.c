#include "../../include/include.h"


//write a function that takes a string and returns a list of tokens (t_type)

//t_token is an enum with the following values: PIPE, REDIR, WORD, SPACE, END

//the list should be a list of t_list, where each t_list contains a t_token and a char*

//the list should be terminated by a t_list with type END

//the list should be freed by the caller

t_token *init_type(int type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token) * 3);
    if (!token)
    {
        printf("malloc error\n");
        exit(-127);
    }
    token->t_type = type;
	if (type == 6)

    token->value = value;
    printf("token->t_type = %d\n", token->t_type);
    return (token);
}

t_token *tokenizateur(t_list *list)
{
    while(list != NULL && list->content != '\0')
    {
        if (ft_strchr(list->content, '|'))
        {
            printf("PIPE\n");
            init_type(PIPE, list->content);
        }
        if (ft_strchr(list->content, '$'))
        {
            printf("DOLLAR\n");
            init_type(DOLLAR, list->content);
        }
        else if (ft_strchr(list->content, '>'))
        {
            printf("REDIR\n");
            init_type(REDIR, list->content);
        }
        else if (ft_strchr(list->content, '<'))
        {
            printf("RREDIR\n");
            init_type(REDIR, list->content);
        }
        else if (ft_strchr(list->content, '"'))
        {
            printf("QUOTE\n");
            init_type(QUOTE, list->content);
        }
        else if (ft_strchr(list->content, '\''))
        {
            printf("SQUOTE\n");
            init_type(QUOTE, list->content);
        }
        else if (ft_strchr(list->content, '-'))
        {
            printf("OPTION\n");
            init_type(OPTION, list->content);
        }
        else
        {
            printf("WORD\n");
            init_type(WORD, list->content);
        }
        list = list->next;
    }
    return (NULL);
}
