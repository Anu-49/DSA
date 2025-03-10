#include "stack.h"

/* Fuction for inserting the element */
int Push(Stack_t *s, int element)
{
    if(s->top == ((s->capacity)-1)){
	    return FAILURE;
    }
    else{
	    s->top = s->top+1;
	    s->stack[s->top] = element;
	    return SUCCESS;
    }


}