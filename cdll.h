#ifndef INC_CDLL_H__
#define INC_CDLL_H__

#include <stdbool.h>
#include <stdint.h>

typedef volatile struct s_cdll_node cdll_node;
typedef volatile struct s_cdll		cdll;

typedef volatile struct s_cdll {
	cdll_node* head;
} cdll;

typedef volatile struct s_cdll_node {
	cdll*	   list;
	cdll_node* next;
	cdll_node* prev;
	void*	   owner;
	uintmax_t  value;
} cdll_node;

bool cdll_init(cdll* list);
bool cdll_append(cdll* list, cdll_node* node);
bool cdll_sort_insert_node(cdll* list, cdll_node* node);
bool cdll_remove_node(cdll* list, cdll_node* node);

#endif	//INC_CDLL_H__