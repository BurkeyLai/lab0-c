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
    /* TODO: What if malloc returned NULL? */
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
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *tmp;

    if (q) {
        while (q->head) {
            if (q->head->value)
                free(q->head->value);
            tmp = q->head->next;
            free(q->head);
            q->head = tmp;
        }
        free(q);
    }
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
    if (!q)
        return false;

    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh)
        return false;

    newh->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }

    snprintf(newh->value, (strlen(s) + 1), "%s", s);

    newh->next = q->head;
    q->head = newh;
    if (!q->tail)  // When the first element inserted into queue...
        q->tail = q->head;
    (q->size)++;
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;

    newt->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (!newt->value) {
        free(newt);
        return false;
    }

    snprintf(newt->value, (strlen(s) + 1), "%s", s);

    if (!q->head)  // trace-16-perf
        q->head = newt;
    else
        q->tail->next = newt;
    newt->next = NULL;
    q->tail = newt;
    (q->size)++;
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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;
    // if (strlen(q->head->value) + 1 > bufsize) //trace-06-perf
    //     return false;

    list_ele_t *tmp = q->head;
    snprintf(sp, bufsize, "%s", tmp->value);

    q->head = q->head->next;
    (q->size)--;

    free(tmp->value);
    free(tmp);  // Must be free after q->head has assigned a new address

    if (!q->head)  // When there is only one element in the queue
        q->tail = q->head;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q)
        return q->size;
    return 0;
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *pre, *tmp, *nxt;

    if (q && q->head && q->tail) {
        q->tail = q->head;
        pre = NULL;
        tmp = q->head;
        nxt = q->head->next;
        while (nxt) {
            tmp->next = pre;
            pre = tmp;
            tmp = nxt;
            nxt = nxt->next;
        }
        tmp->next = pre;
        // pre = tmp;
        // tmp = nxt;
        q->head = tmp;
    }
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

    ////////////////////
    // Insertion Sort //
    ////////////////////
    list_ele_t *a, *b, *c, *d;
    list_ele_t dummy;
    if (q && q->head) {
        a = q->head;
        dummy.value = 0;
        dummy.next = q->head;
        while (a->next) {
            if (strcasecmp(a->next->value, a->value) < 0) {
                b = a->next;
                c = dummy.next;
                d = &dummy;
                while (strcasecmp(b->value, c->value) > 0) {
                    d = d->next;
                    c = c->next;
                }
                a->next = b->next;
                d->next = b;
                b->next = c;
            } else {
                a = a->next;
            }

            if (a)  // trace-05-perf
                q->tail = a;
        }
        q->head = dummy.next;
    }
}
