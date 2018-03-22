/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_stack.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:42:06 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:21:30 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_STACK_H
# define STATE_STACK_H

typedef struct s_state_stack	t_state_stack;
struct				s_state_stack
{
	t_state_stack	*next;
	int				state;
};

void	state_push(t_state_stack *stack, int state);
int		state_pop(t_state_stack *stack);

#endif
