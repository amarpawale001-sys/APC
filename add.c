#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry=0;
    while(tail1 != NULL && tail2 != NULL)
    {
    int sum = tail1->data + tail2->data + carry;
    int data = sum%10;
    carry = sum/10;

    insert_first(headR,tailR,data);

    tail1=tail1->prev;
    tail2=tail2->prev;
    }
    while(tail1 != NULL)
    {
        int sum = (tail1->data)+carry;
        int data = sum%10;
        carry=sum/10;

        insert_first(headR,tailR,data);

        tail1=tail1->prev;

    }
    while(tail2 != NULL)
    {
        int sum = (tail2->data)+carry;
        int data = sum%10;
        carry=sum/10;

        insert_first(headR,tailR,data);

        tail2=tail2->prev;

    }
    if(carry != 0)
    {
        insert_first(headR,tailR,carry);
    }
     remove_pre_zeros(headR);
}

