/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:44:28 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/29 20:15:26 by gcoelho-         ###   ########.fr       */
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
	int				is_complete;
}	t_message;

#endif
