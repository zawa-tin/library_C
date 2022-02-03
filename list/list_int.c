#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_entity *node;
struct node_entity
{
    int key;
    node next;
    node prev;
};

struct list_entity
{
    node head;
    node tail;
    int size;
};
typedef struct list_entity *list;

list list_constructor(list self)
{
    self = (list)malloc(sizeof(struct list_entity));
    self->size = 0;
    return self;
}

void list_destructor(list self)
{
    free(self->head);
    free(self->tail);
    free(self);
}

int list_get_size(list self)
{
    return self->size;
}

node list_make_node()
{
    node new_node = (node)malloc(sizeof(struct node_entity));
    return new_node;
}

node list_assign_value(node new_node, int value)
{
    new_node->key = value;
    return new_node;
}

void list_insert_head(list self, int value)
{
    node new_node = list_assign_value(list_make_node(), value);
    // when list has no nodes
    if (self->head == NULL)
    {
        self->head = new_node;
        self->tail = new_node;
    }
    // when list has nodes
    else
    {
        self->head->prev = new_node;
        new_node->next = self->head;
        self->head = new_node;
    }

    self->size++;
}

void list_insert_tail(list self, int value)
{
    node new_node = list_assign_value(list_make_node(), value);
    // when list has no nodes
    if (self->tail == NULL)
    {
        self->tail = new_node;
        self->head = new_node;
    }
    // when list has nodes
    else
    {
        self->tail->next = new_node;
        new_node->prev = self->tail;
        self->tail = new_node;
    }

    self->size++;
}

// insert node in front of iterator
void list_insert(list self, node iterator, int value)
{
    if (iterator == NULL)
    {
        // exception
        return;
    }

    // when iterator is head
    if (self->head == iterator)
    {
        list_insert_head(self, value);
        return;
    }
    // when iterator is not head
    else
    {
        node new_node = list_assign_value(list_make_node(), value);
        new_node->next = iterator;
        new_node->prev = iterator->prev;
        iterator->prev->next = new_node;
        iterator->prev = new_node;
        self->size++;
        return;
    }
}

void list_delete_head(list self)
{
    // when list has no nodes
    if (self->head == NULL)
    {
        // underflow!
        return;
    }

    node delete_node = self->head;
    // when list has only one node
    if (delete_node->next == NULL)
    {
        self->head = NULL;
        self->tail = NULL;
    }
    // else
    else
    {
        self->head = delete_node->next;
        delete_node->next->prev = NULL;
    }

    self->size--;
    free(delete_node);
}

void list_delete_tail(list self)
{
    // when list has no nodes
    if (self->tail == NULL)
    {
        // underflow!
        return;
    }

    node delete_node = self->tail;
    // when list has only one node
    if (delete_node->prev == NULL)
    {
        self->head = NULL;
        self->tail = NULL;
    }
    // else
    else
    {
        self->tail = delete_node->prev;
        delete_node->prev->next = NULL;
    }

    self->size--;
    free(delete_node);
}

void list_delete(list self, node iterator)
{
    if (iterator == NULL)
    {
        // exception
        return;
    }

    // when iterator is head
    if (iterator->prev == NULL)
    {
        list_delete_head(self);
        return;
    }
    // when iterator is tail
    if (iterator->next == NULL)
    {
        list_delete_tail(self);
        return;
    }

    iterator->prev->next = iterator->next;
    iterator->next->prev = iterator->prev;
    self->size--;
    free(iterator);
}

void list_clear(list self)
{
    node search_node = self->head;
    self->head = NULL;
    self->tail = NULL;
    while (search_node != NULL)
    {
        node delete_node = search_node;
        search_node = search_node->next;
        free(delete_node);
    }
    self->size = 0;
}

bool list_find(list self, int value)
{
    for (node check_node = self->head; check_node != NULL; check_node = check_node->next)
    {
        if (check_node->key == value)
            return true;
    }

    return false;
}

int list_count(list self, int value)
{
    int count = 0;
    for (node check_node = self->head; check_node != NULL; check_node = check_node->next)
    {
        if (check_node->key == value)
            count++;
    }
    return count;
}