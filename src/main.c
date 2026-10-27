#include "push_swap.h"

static void	init_stack(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	init_stack(&a);
	init_stack(&b);
	parse_args(&a, argc, argv);
	if (is_sorted(&a))
	{
		ft_free_stack_nodes(&a);
		return (0);
	}
	/* Здесь дальше будет вызов основного алгоритма 
	*/
	ft_free_stack_nodes(&a);
	return (0);
}