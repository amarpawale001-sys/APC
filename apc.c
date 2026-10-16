#include "apc.h"

// Function definitions

int create_list(char *opr, node **head, node **tail)
{
    int i = 0;

    if(opr[0] == '+' || opr[0] == '-')
    {
        i = 1;
    }

    while(opr[i] != '\0')
    {
        if(insert_last(head, tail, opr[i] - '0') == FAILURE)
        {
            return FAILURE;
        }

        i++;
    }
    return SUCCESS;
}

int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    if(new == NULL)
    {
        return FAILURE;
    } 
    new->prev= NULL;
    new->data= data;
    new->next= NULL;
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        (*tail)->next = new;
        (new)->prev = *tail;
        *tail = new;
        return SUCCESS;
    }
}

int insert_first(node **head, node **tail, int data)
{
    node *new=malloc(sizeof(node));
    {
        if(new == NULL)
        {
            return FAILURE;
        }
        new->prev=NULL;
        new->data=data;
        new->next=NULL;
        if(*head == NULL)
        {
            *head = new;
            *tail = new;
            return SUCCESS;
        }
        new->next = *head;
        (*head)->prev = new;
        *head = new;
        return SUCCESS;
    }
}

int list_len(node *head)
{
    int count = 0;

    while(head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

int compare_list(node *head1, node *head2)
{
    int len1 = 0;
    int len2 = 0;

    node *temp1 = head1;
    node *temp2 = head2;

    while(temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }

    while(temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    if(len1 > len2)
    {
        return OPERAND1;
    }
    else if(len1 < len2)
    {
        return OPERAND2;
    }

    /* Same number of digits */
    while(head1 != NULL && head2 != NULL)
    {
        if(head1->data > head2->data)
        {
            return OPERAND1;
        }
        else if(head1->data < head2->data)
        {
            return OPERAND2;
        }

        head1 = head1->next;
        head2 = head2->next;
    }

    return SAME;
}

void remove_pre_zeros(node **head)
{
    node *temp;

    while(*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

void copy_list(node *head, node *tail, node **new_head, node **new_tail)
{
    (void)tail;

    node *temp = head;

    while(temp != NULL)
    {
        insert_last(new_head, new_tail, temp->data);
        temp = temp->next;
    }
}

void delete_list(node **head, node **tail)
{
    node *temp;

    while(*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}

void print_list(node *head)
{
    if(head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    while(head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}



