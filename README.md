# Circular Doubly Linked List (CDLL)

This project provides an implementation of a circular doubly linked list (CDLL) in C. The CDLL is a data structure where each node points to its previous and next nodes, and the last node points back to the first node, making it circular.

## Features

- **Initialization**: Create and initialize an empty circular doubly linked list.
- **Appending Nodes**: Add nodes to the end of the list.
- **Sorting Insertion**: Insert nodes in sorted order based on their `value` field.
- **Removing Nodes**: Remove nodes from the list safely.

## Data Structures

### `cdll`

The `cdll` structure represents the circular doubly linked list.

```c
typedef volatile struct s_cdll cdll;

struct s_cdll {
    cdll_node* head;
};
```

### `cdll_node`

The `cdll_node` structure represents a node in the circular doubly linked list.

```c
typedef volatile struct s_cdll_node cdll_node;

struct s_cdll_node {
    cdll*       list;
    cdll_node*  next;
    cdll_node*  prev;
    void*       owner;
    uintmax_t   value;
};
```

## Functions

### `bool cdll_init(cdll* list)`

Initializes a circular doubly linked list.

**Parameters**:
- `list`: Pointer to the `cdll` structure to initialize.

**Returns**:
- `true` if initialization is successful.
- `false` if the list pointer is `NULL`.

### `bool cdll_append(cdll* list, cdll_node* node)`

Appends a node to the end of the circular doubly linked list.

**Parameters**:
- `list`: Pointer to the `cdll` structure.
- `node`: Pointer to the `cdll_node` to append.

**Returns**:
- `true` if the node is appended successfully.
- `false` if the node or list is `NULL`.

### `bool cdll_sort_insert_node(cdll* list, cdll_node* node)`

Inserts a node into the list in sorted order based on the node's `value`.

**Parameters**:
- `list`: Pointer to the `cdll` structure.
- `node`: Pointer to the `cdll_node` to insert.

**Returns**:
- `true` if the node is inserted successfully.
- `false` if the node or list is `NULL`.

### `bool cdll_remove_node(cdll* list, cdll_node* node)`

Removes a node from the circular doubly linked list.

**Parameters**:
- `list`: Pointer to the `cdll` structure.
- `node`: Pointer to the `cdll_node` to remove.

**Returns**:
- `true` if the node is removed successfully.
- `false` if the node or list is `NULL`, or the node is not part of the list.

## Usage

1. **Initialization**: Initialize a list using `cdll_init`.
2. **Adding Nodes**: Use `cdll_append` to add nodes or `cdll_sort_insert_node` to insert nodes in sorted order.
3. **Removing Nodes**: Use `cdll_remove_node` to remove nodes as needed.

## Example

```c
#include "cdll.h"

int main() {
    cdll my_list;
    cdll_node node1, node2;

    cdll_init(&my_list);

    node1.value = 10;
    node2.value = 20;

    cdll_append(&my_list, &node1);
    cdll_sort_insert_node(&my_list, &node2);

    cdll_remove_node(&my_list, &node1);

    return 0;
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to submit issues and pull requests. Contributions are welcome!

## Contact

For any questions or feedback, please open an issue on the GitHub repository or contact the author.
