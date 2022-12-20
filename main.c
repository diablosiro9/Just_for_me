#include "../include/include.h"

// Pourquoi refaire un ft_putchar alors que tu l'as déjà fait dans ton libft ?
void ft_putchar(char c)
{
    write(1, &c, 1);
}

unsigned int	starter_env(char *s)
{
	unsigned int	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

// Quasiment parfaitement propre (check malloccc)
t_env *get_env(char **env)
{
    int i = 0;
    t_env *list = NULL;
    
    list = malloc(sizeof(t_env)* 100);
    if (!list)
    {
        printf("malloc error\n");
        exit(-127);
    }
    while (env[i])
    {
        list[i].name = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
        list[i].content =  ft_strsub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i]));
        i++;
    }
    return (list);
}

// Dans le directory lexer de préférence
// t_list *lexer(t_list *str)
// {
//     t_list *list;
//     char **tab;
// 	char *tp = (char *)str->content;
//     int i = 0;
//     t_list *tmp = malloc(sizeof(t_list) * 100); // Check tes mallocs mon coeuuurrrrr
//     if (!tmp)
//     {
//         printf("malloc error\n");
//         exit(-127);
//     }
//     tab = ft_split(tp);
//     while (tab[i])
//     {
//         list = ft_lstnew(tab[i]);
//         list->next = tmp;
//         tmp = list;
//         i++;
//     }
// 	//printf("TAB VA SUIVRE---->\n");
// 	//afftab(tab);
//     afflist(list, "Lexer");
//     printf("je vois avant tokenizateur\n");
//     tokenizateur(list);
//     //printf("sortie\n");
//     return (list);
// }

/* by mathieu
Le soucis c'est que tu fais un list->next = tmp et apparament ca faisait un peu n'importe quoi
Donc vaut mieux utiliser une fonction que tu as faites comme ft_lstadd qui elle meme te rajoute une node a la fin
ensuite a chaque fois tu realloues list donc tu auras des leaks alors que tu peux directement donner en argument ft_lstnew 
a ton ft_lstadd, ensuite ton tab recupere les espaces. 
*/

int check_name(char *str, t_list *name)
{
    while (name)
    {
        if (ft_strcmp(str, (char *)name->content) == 0)
            return (1);
        name = name->content;
    }
    return (0);
}

t_list *lexer(t_list *str)
{
    t_list *list;
    int i;
    char **tab;

    i = 0;
    list = NULL;
    tab = ft_split((char *)str->content);
    while (tab[i])
    {
        ft_lstadd(&list, ft_lstnew(tab[i]));
        i++;
    }
    afflist(list, "Lexer");
    printf("je vois avant tokenizateur\n");
    tokenizateur(list);
    return (list);
} 

int main(int ac, char **av, char **env)
{
    t_env *list;
	t_list	*history = NULL;
    t_list *str = NULL;
	history = ft_lstnew(NULL);
    list = get_env(env);
    (void)ac;
    (void)av;
    //int i = 0;
	
    // BIBOUUUUUUUUUUUUUU
    //
	// while (list[i].name)
	// {
	// 	printf("NAME = %s && CONTENT = %s\n", list[i].name, list[i].content);
	// 	i++;
	// }
    while (42)
	{
        printf("0\n");
	 	ft_putstr("minishell>");
        str = ft_lstnew(get_next_line(0));
		printf("1\n");
		ft_lstadd(&history, str);
		//afflist(history, "History");
		// printf("history->content = %s\n", history->content);
		// *history = (*history)->next;
        //printf("La commande que tu tape = %s\n", str);
		//printf("je vois avant lexer\n");
        lexer(str);
	}
    return (0);
}