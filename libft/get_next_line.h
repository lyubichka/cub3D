/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlyubick <vlyubick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:44:13 by vlyubick          #+#    #+#             */
/*   Updated: 2022/03/21 20:44:32 by vlyubick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*ft_read(char *st_str, int fd);
char	*ft_anl(char *st_str);
char	*ft_savestr(char *st_str);

int		findn(char *s);
char	*gnl_strjoin(char *s1, char *s2);

#endif
