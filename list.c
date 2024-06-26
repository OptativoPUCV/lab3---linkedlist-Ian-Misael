#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
  void * data;
  Node * next;
  Node * prev;
};

struct List {
  Node * head;
  Node * tail;
  Node * current;
};

typedef List List;

Node * createNode(void * data) {
  Node * new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List * createList() { 
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  if (list->head == NULL || list->head == NULL) {
    return NULL;
  }
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if (list->current == NULL || 
    list->current->next == NULL) {
    return NULL;
  }
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list->tail == NULL) {
    return NULL;
  }
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if (list->current == NULL || 
    list->current->prev == NULL) {
    return NULL;
  }
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * nuevo = createNode(data);
  if (list->head == NULL) {
    list->head = nuevo;
    list->tail = nuevo;
  }
  else {
    nuevo->next = list->head;
    list->head->prev = nuevo;
    list->head = nuevo; 
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list->current == NULL) {
    pushFront(list, data);
  }
  else {
    Node * nuevo = createNode(data);
    nuevo->next = list->current->next;
    nuevo->prev = list->current;
    if (list->current->next == NULL) {
      list->tail = nuevo; 
    }
    else {
      list->current->next->prev = nuevo;
    }
    list->current->next = nuevo; 
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->current == NULL) {
    return NULL;
  }
  Node *temp = list->current;
  void *data = temp->data;

  if (temp == list->head) {
    list->head = temp->next;
    if (list->head != NULL) {
      list->head->prev = NULL;
    }
  } else {
    temp->prev->next = temp->next;
  }

  if (temp == list->tail) {
    list->tail = temp->prev;
    if (list->tail != NULL) {
      list->tail->next = NULL;
    }
  } else {
    temp->next->prev = temp->prev;
  }

  free(temp);
  list->current = NULL;
  return data;
}


void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}