#include "libft.h"

// Basic operations
void  op_swap(t_stack *s);
void  op_push(t_stack *dst, t_stack *src);
void  op_rotate(t_stack *s);
void  op_rev_rotate(t_stack *s);

// one executor for all operations
void  exec_op(char *cmd, t_stack *a, t_stack *b)
{
    if (!ft_strncmp(cmd, "sa", 3))
		op_swap(a);
    else if (!ft_strncmp(cmd, "sb", 3))
		op_swap(b);
    else if (!ft_strncmp(cmd, "ss", 3))
		{ op_swap(a); op_swap(b); }
    else if (!ft_strncmp(cmd, "pa", 3))
		op_push(a, b);
    else if (!ft_strncmp(cmd, "pb", 3))
		op_push(b, a);
    else if (!ft_strncmp(cmd, "ra", 3))
		op_rotate(a);
    else if (!ft_strncmp(cmd, "rb", 3))
		op_rotate(b);
    else if (!ft_strncmp(cmd, "rr", 3))
		{ op_rotate(a); op_rotate(b); }
    else if (!ft_strncmp(cmd, "rra", 4))
		op_rev_rotate(a);
    else if (!ft_strncmp(cmd, "rrb", 4))
		op_rev_rotate(b);
    else if (!ft_strncmp(cmd, "rrr", 4))
		{ op_rev_rotate(a); op_rev_rotate(b); }
    ft_putendl_fd(cmd, 1);
}
