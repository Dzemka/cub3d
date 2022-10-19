/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:50:38 by olugash           #+#    #+#             */
/*   Updated: 2022/09/27 13:11:49 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>

# include <unistd.h>

# include "libft.h"

typedef struct s_gnl
{
	char	*new_line;
	char	*end_line;
}	t_gnl;

typedef struct s_list_gnl
{
	int					fd;
	char				*remaining_str;
	struct s_list_gnl	*next;
}	t_list_gnl;

char		*get_next_line(int fd);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_build_line(char *str1, char *str2, char *end_line);
t_list_gnl	*ft_lst_new(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
