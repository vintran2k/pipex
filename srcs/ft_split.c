#include "pipex.h"

void	ft_free_tab(char **tab)
{
	//ft_putstr_fd("passage free_tab\n", STDERR_FILENO);
	int	i;

	i = 0;
	if (tab)
	{
		//ft_putstr_fd("passage free_tab boucle\n", STDERR_FILENO);
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j)
			nb_words++;
		i += j;
	}
	return (nb_words);
}

void	ft_fill_tab(char **tab, const char *s, char c, size_t nb_words)
{
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	tab[nb_words] = NULL;
	while (i < nb_words)
	{
		while (s[j] && s[j] == c)
			j++;
		word_len = 0;
		while (s[j + word_len] && s[j + word_len] != c)
			word_len++;
		tab[i] = ft_strndup((char *)&s[j], word_len);
		if (!tab[i])
		{
			ft_free_tab(tab);
			break ;
		}
		j += word_len;
		i++;
	}
}

char	**ft_split(const char *s, char c)
{
	size_t	nb_words;
	char	**tab;

	if (!s)
		return (NULL);
	nb_words = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	ft_fill_tab(tab, s, c, nb_words);
	return (tab);
}
