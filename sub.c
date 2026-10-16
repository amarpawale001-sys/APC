#include "apc.h"

int subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1;
    node *temp2;

    int digit1, digit2;
    int borrow = 0;
    int diff;
    int negative = 0;

    /* Get heads */
    node *head1 = tail1;
    node *head2 = tail2;

    while(head1->prev != NULL)
        head1 = head1->prev;

    while(head2->prev != NULL)
        head2 = head2->prev;

    int cmp = compare_list(head1, head2);

    if(cmp == SAME)
    {
        insert_first(headR, tailR, 0);
        return 0;
    }

    /* If operand1 < operand2, swap lists */
    if(cmp == OPERAND2)
    {
        negative = 1;

        node *temp;

        temp = head1;
        head1 = head2;
        head2 = temp;

        temp = tail1;
        tail1 = tail2;
        tail2 = temp;
    }

    temp1 = tail1;
    temp2 = tail2;

    while(temp1 != NULL || temp2 != NULL)
    {
        digit1 = 0;
        digit2 = 0;

        if(temp1 != NULL)
        {
            digit1 = temp1->data;
            temp1 = temp1->prev;
        }

        if(temp2 != NULL)
        {
            digit2 = temp2->data;
            temp2 = temp2->prev;
        }

        digit1 = digit1 - borrow;

        if(digit1 < digit2)
        {
            digit1 = digit1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        diff = digit1 - digit2;

        insert_first(headR, tailR, diff);
    }
    
    remove_pre_zeros(headR);

    return negative;
}