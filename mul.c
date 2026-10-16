#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *p1;
    node *p2;

    int carry;
    int product;
    int position = 0;

    /* Result starts as 0 */
    insert_first(headR, tailR, 0);

    p2 = tail2;

    while(p2 != NULL)
    {
        p1 = tail1;
        carry = 0;

        node *tempHead = NULL;
        node *tempTail = NULL;

        /* Multiply one digit of operand2 with operand1 */
        while(p1 != NULL)
        {
            product = (p1->data * p2->data) + carry;

            insert_first(&tempHead, &tempTail, product % 10);

            carry = product / 10;

            p1 = p1->prev;
        }

        /* Remaining carry */
        if(carry != 0)
        {
            insert_first(&tempHead, &tempTail, carry);
        }

        /* Add zeros according to position */
        for(int i = 0; i < position; i++)
        {
            insert_last(&tempHead, &tempTail, 0);
        }

        /* Add partial result with final result */
        node *r1 = *tailR;
        node *r2 = tempTail;

        int sum;
        int resultCarry = 0;

        node *newHead = NULL;
        node *newTail = NULL;

        while(r1 != NULL || r2 != NULL || resultCarry != 0)
        {
            sum = resultCarry;

            if(r1 != NULL)
            {
                sum = sum + r1->data;
                r1 = r1->prev;
            }

            if(r2 != NULL)
            {
                sum = sum + r2->data;
                r2 = r2->prev;
            }

            resultCarry = sum / 10;
            sum = sum % 10;

            insert_first(&newHead, &newTail, sum);
        }

        delete_list(headR, tailR);
        delete_list(&tempHead, &tempTail);

        *headR = newHead;
        *tailR = newTail;

        p2 = p2->prev;
        position++;
    }

    remove_pre_zeros(headR);
}
