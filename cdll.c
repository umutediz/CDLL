#include "cdll.h"

#include <limits.h>
#include <stddef.h>

bool cdll_init(cdll* list) {
	if (list == NULL) {
		return false;
	} else {
		list->head = (cdll_node*)0;
		return true;
	}
}

bool cdll_append(cdll* list, cdll_node* node) {
	// Check if list is empty
	if (list->head == NULL) {
		list->head = node;
		node->next = node;
		node->prev = node;
	} else {
		node->prev = list->head->prev;
		node->next = list->head;
		list->head->prev->next = node;
		list->head->prev = node;
	}

	node->list = list;
	return true;
}

bool cdll_remove_node(cdll* list, cdll_node* node) {
	if (!node || node->list != list || !node->next || !node->prev) {
		return false;
	}

	node->next->prev = node->prev;
	node->prev->next = node->next;

	if (list->head == node) {
		//Check if more than one node is present
		if (node->next != node) {
			list->head = list->head->next;
		} else {
			list->head = NULL;
		}
	}
	node->list = NULL;
	node->next = NULL;
	node->prev = NULL;
	return true;
}

bool cdll_sort_insert_node(cdll* list, cdll_node* node) {
	volatile cdll_node* it_node;

	if (list->head == NULL) {
		return cdll_append(list, node);
	}

	if (list->head->value > node->value) {
		it_node = list->head->prev;
		list->head = node;
	} else {
		for (it_node = list->head; (it_node->next != list->head) && (node->value > it_node->next->value); it_node = it_node->next) {
			;
		}
	}

	node->next = it_node->next;
	node->next->prev = node;
	it_node->next = node;
	node->prev = it_node;

	node->list = list;
	return true;
}