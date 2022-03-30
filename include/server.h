/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:44:28 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/30 20:55:39 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "minitalk.h"
# define MESSAGE_SIZE 1000001

typedef struct s_message
{
	unsigned char	content[MESSAGE_SIZE];
	int				idx;
	int				bit;
}	t_message;

#endif
