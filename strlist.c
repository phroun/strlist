#include "strlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// TODO: get length
// TODO: method to iterate

StrList *ListItem_create() {
  StrList *node = malloc(sizeof(StrList));
  assert(node != NULL);
  node->key = NULL;
  node->reserved = NULL;
  node->data = "";
  node->next = NULL;
  return node;
}

StrList *List_create() {
  return NULL;
}

void ListItem_destroy(StrList **item) {
  assert(*item != NULL);
  if ((*item)->data != NULL) {
    free((*item)->data);
  }
  if ((*item)->key != NULL) {
    free((*item)->key);
  }
  free(*item);
}

void List_destroy(StrList **root) {
  if (*root == NULL) {
    return;
  }
  StrList *node = *root;
  while (node != NULL) {
    printf("tres\r\n");
    StrList *next = node->next;
    ListItem_destroy(&node);
    node = next;
  }
  printf("done\r\n");
  *root = NULL;
  return;
}

char *List_strdup(const char* str) {
  int x = strlen(str) + 1;
  char *dup = malloc(x);
  strncpy(dup, str, x);
  return dup;
}

void List_append(StrList **root, const char *val) {
  assert(root != NULL);
  assert(val != NULL);
  char *newval = List_strdup(val);
  if (*root == NULL) {
    StrList *item = ListItem_create();
    item->key = NULL;
    item->data = newval;
    *root = item;
  } else {
    StrList *node = *root;
    while (node->next != NULL) {
      node = node->next;
    }
    node->next = ListItem_create();
    node = node->next;
    node->key = NULL;
    node->data = newval;
  }
}

int List_foreach(StrList **root, StrList **iterator) {
  if (*iterator == NULL) {
    *iterator = *root;
  } else {
    *iterator = (*iterator)->next;
  }
  return (*iterator != NULL);
}

StrList *List_set(StrList **root, const char *key, const char *val) {
  assert(root != NULL);
  assert(key != NULL);
  assert(val != NULL);
  if (*root == NULL) {
    StrList *item = ListItem_create();
    char *newkey = List_strdup(key);
    item->key = newkey;
    char *newval = List_strdup(val);
    item->data = newval;
    *root = item;
    return item;
  } else {
    StrList *node = *root;
    while (node != NULL) {

      if (node->key != NULL) {
        if (strncmp(node->key, key, strlen(key)) == 0) {
          char *newval = List_strdup(val);
          node->data = newval;
          return node;
        }
      }

      if (node->next != NULL) {
        node = node->next;
      } else { // give up, add new item
        node->next = ListItem_create();
        node = node->next;
        char *newkey = List_strdup(key);
        node->key = newkey;
        char *newval = List_strdup(val);
        node->data = newval;
        return node;
      }

    }
  }
  return *root;
}

StrList *List_get(StrList *root, int index) {
  int x = 0;
  StrList *node = root;
  while (node != NULL) {
    if (x == index) {
      return node;
    }
    *node = *node->next;
    x++;
  }
  return NULL;
}

StrList *List_find(StrList *root, const char *key, int index_found) {
  int x = 0;
  StrList *node = root;
  while (node != NULL) {
    if (node->key != NULL) {
      if (strncmp(node->key, key, strlen(key)) == 0) {
        index_found = x;
        return node;
      }
    }
    node = node->next;
    x++;
  }
  index_found = -1;
  return NULL;
}

StrList *List_search(StrList *root, const char *val, int index_found) {
  int x = 0;
  StrList *node = root;
  while (node != NULL) {
    if (strncmp(node->data, val, strlen(val)) == 0) {
      index_found = x;
      return node;
    }
    node = node->next;
    x++;
  }
  index_found = -1;
  return NULL;
}

void List_remove(StrList **root, int index) {
  int x = 0;
  StrList *lastnode = *root;
  StrList *node = *root;
  while (node != NULL) {
//    if (strncmp(node->data, val, strlen(val)) == 0) {
    if (x == index) {
      lastnode->next = node->next;
      if (node == *root) {
        *root = node->next;
      }
      ListItem_destroy(&node);
      return;
    }
    lastnode = node;
    node = node->next;
    x++;
  }
  return;
}

int List_unset(StrList **root, const char* val) {
  int x = 0;
  StrList *lastnode = *root;
  StrList *node = *root;
  while (node != NULL) {
    if (node->key != NULL) {
      if (strncmp(node->key, val, strlen(val)) == 0) {
        lastnode->next = node->next;
        if (node == *root) {
          *root = node->next;
        }
        ListItem_destroy(&node);
        return x;
      }
    }
    lastnode = node;
    node = node->next;
    x++;
  }
  return -1;
}

/*
void List_remove(StrList *root, int index);
char *List_pop(StrList *root, int index);
int List_length(StrList *root);
*/
void List_print(StrList *root) {
  printf("[");
  if (root == NULL) {
    printf("%s", "]");
    return;
  }
  StrList *node = root;
  int x = 0;
  while (node != NULL) {
    if (node->key == NULL) {
      printf("%d", x);
    } else {
      printf("%s", node->key);
    }
    printf(":");
    printf("%s", node->data);
    node = node->next;
    if (node != NULL) {
      printf("%s", ", ");
    }
    x++;
  }
  printf("%s", "]\n");
}
