/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:04:18 by sgil--de          #+#    #+#             */
/*   Updated: 2025/11/17 12:57:44 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE
# define FT_GET_NEXT_LINE

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif