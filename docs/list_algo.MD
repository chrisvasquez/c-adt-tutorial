# List Data Structure

```
   list is an abstract list data type.  It can contain any number of
   objects ('void *' or 'const void *' pointers) in any given order.
   Duplicates are allowed, but can optionally be forbidden.
   There are several implementations of this list datatype, optimized for
   different operations or for memory.  You can start using the simplest list
   implementation, ARRAY_LIST, and switch to a different implementation
   later, when you realize which operations are performed the most frequently.
   The API of the different implementations is exactly the same; when
   switching to a different implementation, you only have to change the
   list_create call.
   The implementations are:
     ARRAY_LIST        a growable array
     CARRAY_LIST       a growable circular array
     LINKED_LIST       a linked list
     AVLTREE_LIST      a binary tree (AVL tree)
     RBTREE_LIST       a binary tree (red-black tree)
     LINKEDHASH_LIST   a hash table with a linked list
     AVLTREEHASH_LIST  a hash table with a binary tree (AVL tree)
     RBTREEHASH_LIST   a hash table with a binary tree (red-black tree)
   The memory consumption is asymptotically the same: O(1) for every object
   in the list.  When looking more closely at the average memory consumed
   for an object, ARRAY_LIST is the most compact representation, and
   LINKEDHASH_LIST and TREEHASH_LIST need more memory.

   It is required to also implement the creation of the list.

   The guaranteed average performance of the operations is, for a list of
   n elements:
   Operation                  ARRAY    LINKED    TREE    LINKEDHASH   TREEHASH
                              CARRAY                   with|without with|without
                                                         duplicates  duplicates
   list_size                O(1)     O(1)     O(1)      O(1)         O(1)
   list_node_value          O(1)     O(1)     O(1)      O(1)         O(1)
   list_node_set_value      O(1)     O(1)     O(1)      O(1)    O((log n)²)/O(1)
   list_next_node           O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_previous_node       O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_first_node          O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_last_node           O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_get_at              O(1)     O(n)   O(log n)    O(n)       O(log n)
   list_get_first           O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_get_last            O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_set_at              O(1)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   list_set_first           O(1)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_set_last            O(1)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_search              O(n)     O(n)     O(n)    O(n)/O(1)    O(log n)/O(1)
   list_search_from         O(n)     O(n)     O(n)    O(n)/O(1) O((log n)²)/O(log n)
   list_search_from_to      O(n)     O(n)     O(n)    O(n)/O(1) O((log n)²)/O(log n)
   list_indexof             O(n)     O(n)     O(n)      O(n)       O(log n)
   list_indexof_from        O(n)     O(n)     O(n)      O(n)    O((log n)²)/O(log n)
   list_indexof_from_to     O(n)     O(n)     O(n)      O(n)    O((log n)²)/O(log n)
   list_add_first         O(n)/O(1)  O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_last            O(1)     O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_before          O(n)     O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_after           O(n)     O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_at              O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   list_remove_node         O(n)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_remove_at           O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   list_remove_first      O(n)/O(1)  O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_remove_last         O(1)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_remove              O(n)     O(n)     O(n)    O(n)/O(1) O((log n)²)/O(log n)
   list_iterator            O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_iterator_from_to    O(1)     O(n)   O(log n)    O(n)       O(log n)
   list_iterator_next       O(1)     O(1)   O(log n)    O(1)       O(log n)
   sortedlist_search      O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_search_from O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_indexof     O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_indexof_fro O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_add           O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   sortedlist_remove        O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)

```

Explanations: Algorithms

```c
   The guaranteed average performance of the operations is, for a list of
   n elements:
   Operation                  ARRAY    LINKED    TREE    LINKEDHASH   TREEHASH
                              CARRAY                   with|without with|without
                                                         duplicates  duplicates
   list_size                O(1)     O(1)     O(1)      O(1)         O(1)
   list_node_value          O(1)     O(1)     O(1)      O(1)         O(1)
   list_node_set_value      O(1)     O(1)     O(1)      O(1)    O((log n)²)/O(1)
   list_next_node           O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_previous_node       O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_first_node          O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_last_node           O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_get_at              O(1)     O(n)   O(log n)    O(n)       O(log n)
   list_get_first           O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_get_last            O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_set_at              O(1)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   list_set_first           O(1)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_set_last            O(1)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_search              O(n)     O(n)     O(n)    O(n)/O(1)    O(log n)/O(1)
   list_search_from         O(n)     O(n)     O(n)    O(n)/O(1) O((log n)²)/O(log n)
   list_search_from_to      O(n)     O(n)     O(n)    O(n)/O(1) O((log n)²)/O(log n)
   list_indexof             O(n)     O(n)     O(n)      O(n)       O(log n)
   list_indexof_from        O(n)     O(n)     O(n)      O(n)    O((log n)²)/O(log n)
   list_indexof_from_to     O(n)     O(n)     O(n)      O(n)    O((log n)²)/O(log n)
   list_add_first         O(n)/O(1)  O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_last            O(1)     O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_before          O(n)     O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_after           O(n)     O(1)   O(log n)    O(1)    O((log n)²)/O(log n)
   list_add_at              O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   list_remove_node         O(n)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_remove_at           O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   list_remove_first      O(n)/O(1)  O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_remove_last         O(1)     O(1)   O(log n)  O(n)/O(1) O((log n)²)/O(log n)
   list_remove              O(n)     O(n)     O(n)    O(n)/O(1) O((log n)²)/O(log n)
   list_iterator            O(1)     O(1)   O(log n)    O(1)       O(log n)
   list_iterator_from_to    O(1)     O(n)   O(log n)    O(n)       O(log n)
   list_iterator_next       O(1)     O(1)   O(log n)    O(1)       O(log n)
   sortedlist_search      O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_search_from O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_indexof     O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_indexof_fro O(log n)   O(n)   O(log n)    O(n)       O(log n)
   sortedlist_add           O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
   sortedlist_remove        O(n)     O(n)   O(log n)    O(n)    O((log n)²)/O(log n)
```