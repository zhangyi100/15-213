/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
      return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(q == NULL) {
      return;
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t* current = q->head;
    while(current != NULL) {
      list_ele_t* ele = current;
      current = current->next;
      free(ele->value);
      free(ele);
    }
    free(q);
    q = NULL;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if(q == NULL) {
      return false;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(newh == NULL) {
      // free(newh);
      return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    char* value = malloc(strlen(s) + 1);
    if(value == NULL) {
      free(newh);
      return false;
    }
    strcpy(value, s);
    newh->value = value;

    newh->next = q->head;
    if(q->tail == NULL) {
      q->tail = newh;
    }
    q->head = newh;
    q->count += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if(q == NULL) {
      return false;
    }
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t* newtail = malloc(sizeof(list_ele_t));
    if(newtail == NULL) {
      return false;
    }

    char* value = malloc(strlen(s) + 1);
    if(value == NULL) {
      free(newtail);
      return false;
    }
    strcpy(value, s);
    newtail->value = value;

    q->tail->next = newtail;
    q->tail = newtail;
    newtail->next = NULL;
    q->count += 1;

    if(q->head == NULL) {
      q->head = newtail;
    }
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  if(q == NULL || q->head == NULL) {
    return false;
  }

  list_ele_t* head = q->head;
  char* value = head->value;
  if(sp != NULL) {
    int len = strlen(head->value);
    if(len < bufsize - 1) {
      strcpy(sp, head->value);
    } else {
      strncpy(sp, head->value, bufsize-1);
      sp[bufsize-1] = '\0';
    }
  }

  q->head = q->head->next;
  free(value);
  free(head);

  q->count -= 1;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q == NULL || q->head == NULL) {
      return 0;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->count;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(q == NULL || q->head == NULL) {
      return;
    }

    list_ele_t* node = q->head;
    list_ele_t* next = NULL;
    while(node != NULL) {
      list_ele_t* advanceNode = node->next;
      node->next = next;
      next = node;
      node = advanceNode;
    }

    list_ele_t* swapTemp = q->head;
    q->head = q->tail;
    q->tail = swapTemp;
}
