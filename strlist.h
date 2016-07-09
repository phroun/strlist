#ifndef STR_LIST
#define STR_LIST

typedef struct StrListItemT {
  char *key;
  char *data;
  void *reserved;
  struct StrListItemT *next;
} StrList;

StrList *ListItem_create();
void ListItem_destroy(StrList **item);

char *List_strdup(const char* str);
StrList *List_create();
void List_destroy(StrList **root);
void List_append(StrList **root, const char *val);
int List_foreach(StrList **root, StrList **iterator);
StrList *List_set(StrList **root, const char *key, const char *val);
StrList *List_get(StrList *root, int index);
StrList *List_find(StrList *root, const char *key, int index_found);
StrList *List_search(StrList *root, const char *val, int index_found);
void List_remove(StrList **root, int index);
int List_unset(StrList **root, const char* val);
char *List_pop(StrList *root, int index);
int List_length(StrList *root);
void List_print(StrList *root);

#endif