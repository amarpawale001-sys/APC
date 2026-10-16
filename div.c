#include "apc.h"

int division(node *head1, node *tail1, node *head2, node *tail2, node **headR, node **tailR)
{

    (void)tail1;

     remove_pre_zeros(&head2);

    /* Division by zero */
    if(head2 == NULL)
    {
        return FAILURE;
    }

    if(head2->data == 0 && head2->next == NULL)
    {
        return FAILURE;
    }

    node *currentHead = NULL;
    node *currentTail = NULL;

    node *temp = head1;

    /* Long division */
    while(temp != NULL)
    {
        /* Bring down one digit */
        insert_last(&currentHead, &currentTail, temp->data);

        remove_pre_zeros(&currentHead);

        int count = 0;

        /* Subtract divisor until current value is smaller */
        while(compare_list(currentHead, head2) != OPERAND2)
        {
            node *subHead = NULL;
            node *subTail = NULL;

            subtraction(currentTail, tail2,&subHead, &subTail);

            delete_list(&currentHead, &currentTail);

            currentHead = subHead;
            currentTail = subTail;

            count++;
        }

        /* Store quotient digit */
        insert_last(headR, tailR, count);

        temp = temp->next;
    }

    /* Remove leading zeros from quotient */
    remove_pre_zeros(headR);

    /* If quotient is empty, result is 0 */
    if(*headR == NULL)
    {
        insert_first(headR, tailR, 0);
    }

    /* Remainder is not required */
    delete_list(&currentHead, &currentTail);

    return SUCCESS;
}