#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *tmp;

    if (!q)
        return;

    while ((tmp = q->head)) {
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->next = q->head;
    newh->value = strdup(s);

    if (!newh->value) {
        free(newh);
        return false;
    }

    q->head = newh;

    if (!q->size)
        q->tail = newh;
    q->size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->next = NULL;
    newh->value = strdup(s);
    if (!newh->value) {
        free(newh);
        return false;
    }

    if (!q->size)
        q->head = newh;
    else
        q->tail->next = newh;

    q->tail = newh;
    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *tmp;

    if (!q || !q->head)
        return false;

    if (sp) {
        int len = strlen(q->head->value);
        len = len < (bufsize - 1) ? len : bufsize - 1;
        memcpy(sp, q->head->value, len);
        sp[len] = 0;
    }

    tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    if (!q->size)
        q->tail = q->head;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *tmp;

    if (!q || !q->head)
        return;
    if (q->size == 1)
        return;

    q->tail->next = q->head;
    tmp = q->head->next;
    q->tail->next->next = q->head;

    while (tmp != q->tail) {
        q->head = tmp;
        tmp = tmp->next;
        q->head->next = q->tail->next->next;
        q->tail->next->next = q->head;
    }

    q->head = q->tail;
    q->tail = tmp->next;
    q->head->next = q->tail->next;
    q->tail->next = NULL;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
