void    op_push(t_stack *dst, t_stack *src)
{
    t_node  *node;

    if (!src || src->size == 0)
        return ;

    node = src->top;
    src->top = node->next;
    if (src->top)
        src->top->prev = NULL;
    else
        src->bottom = NULL;
    src->size--;

    node->prev = NULL;
    node->next = dst->top;
    if (dst->top)
        dst->top->prev = node;
    else
        dst->bottom = node;
    dst->top = node;
    dst->size++;
}
