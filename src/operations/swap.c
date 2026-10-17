#include "push_swap.h"

void	op_swap(t_stack *stack)
{
	t_node *first;
	t_node *second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;

	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		stack->bottom = first; //if there was only two elements

		second->prev = NULL;
		second->next = first;
		first->prev = second;

		stack->top = second;
}
