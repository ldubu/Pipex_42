/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:02 by ldubuche          #+#    #+#             */
/*   Updated: 2022/04/20 13:53:22 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "list.h"
# include "ft_printf.h"

# ifndef FD_MAX
#  define FD_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/*==============PRINT================*/

//print une string + un \n, une string, un  charactere et un entier
//Dans un fichier donne
void	__putendl_fd(char *s, int fd);	
void	__putstr_fd(char *s, int fd);
void	__putchar_fd(char c, int fd);
void	__putnbr_fd(int n, int fd);
//Sur la sortie standard	
void	__putendl(char *s);
void	__putchar(char c);
void	__putstr(char *s);
void	__putnbr(int n);

/*========GET NEXT LINE (GNL)========*/

//Fonction principale
char	*__get_next_line(int fd);
//Fonction qui lit le fichier et stocke dans le buffer
char	*__fill_buffer(char *current_read, char *buffer, int fd);
//Fonction qui definit la ligne a retourner
char	*__r_value(char **buffer, char *current_value);
//Fonction rentre la ligne sur la chaine que l'on retourne
void	__fill_retour(char **buffer, int len, char *retour);
//Fonction qui fait un strjoin et libere l'une des strings
char	*__buffjoin(char *buffer, char *str, char *to_free);
//Fonction qui libere une string si elle existe
char	*__free_str(char *str);

/*==========MEMORY==========*/

//Fonction sur n'importe quel type et qui donc ne s'arrete pas a \0
//fonction pour comparer, deplacer, copier, chercher et initier
int		__memcmp(const void *s1, const void *s2, size_t n);
void	*__memmove(void *dst, const void *src, size_t len);
void	*__memcpy(void *dst, const void *src, size_t n);
void	*__memchr(const void *s, int c, size_t n);
void	*__memset(void *b, int c, size_t len);
//Fonction qui alloue un espace en memoire et l'initialise avec
//bzero avec des 0
void	*__calloc(size_t count, size_t size);
void	__bzero(void *s, size_t n);

/*==============STR=============*/

//Fonction pour savoir quel type de caractere on a
int		__isalnum(int c);
int		__isalpha(int c);
int		__isdigit(int c);
int		__isascii(int c);
int		__isprint(int c);
//Fonction pour changer la casse d'une chaine de charactere
int		__tolower(int c);
int		__toupper(int c);
//Fonction qui trnaforme un entier en chaine de charactere et
//inversement
int		__atoi(const char *str);
char	*__itoa(int n);
//Fonction pour comparer, copier, concatener
int		__strncmp(const char *s1, const char *s2, size_t n);
size_t	__strlcpy(char *dst, const char *src, size_t dstsize);
size_t	__strlcat(char *dst, const char *src, size_t dstsize);
//Split une string en fonction d'un chara, join deux string
char	*__strjoin(char const *s1, char const*s2);
char	**__split(char *s, char c);
//Retourne la taille d'une string
size_t	__strlen(const char *s);

//chercher (premiere ou derniere occurrence) un char ou une str
char	*__strnstr(const char *haystack, const char *needle, size_t len);
char	*__strchr(const char *s, int c);
char	*__strrchr(const char *s, int c);
//Copier en allouant un espace en memoire
char	*__strdup(const char *s1);
//Iterer chaque charctere avec une fonction
void	__striteri(char *s, void (*f)(unsigned int, char*));
char	*__strmapi(char const *s, char (*f)(unsigned int, char));
//Retourne un estring alloue qui correspond a s1 sans le set
char	*__strtrim(char const *s1, char const *set);
//Extraire une string d'une autre
char	*__substr(char const *s, unsigned int start, size_t len);

#endif
