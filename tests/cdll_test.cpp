#include <gtest/gtest.h>

extern "C" {
#include "cdll.h"
}

GTEST_TEST(cdll_tests, test_init) {
	cdll l = {.head = (cdll_node*)0xDEADBEEFU};
	EXPECT_TRUE(cdll_init(&l) == true);
	EXPECT_TRUE(cdll_init(NULL) == false);

	EXPECT_EQ(nullptr, l.head);
}

GTEST_TEST(cdll_tests, test_append_empty) {
	cdll	  l;
	cdll_node node;
	node.value = 5;

	EXPECT_TRUE(cdll_init(&l) == true);

	cdll_append(&l, &node);

	EXPECT_EQ(&node, node.prev);
	EXPECT_EQ(&node, node.next);
	EXPECT_EQ(&l, node.list);

	EXPECT_EQ(&node, l.head);
}

GTEST_TEST(cdll_tests, test_append) {
	cdll	  l;
	cdll_node n1;
	cdll_node n2;
	cdll_node n3;
	n1.value = 5;
	n2.value = 6;
	n3.value = 7;

	EXPECT_TRUE(cdll_init(&l) == true);

	EXPECT_TRUE(cdll_append(&l, &n1) == true);
	EXPECT_TRUE(cdll_append(&l, &n2) == true);
	EXPECT_TRUE(cdll_append(&l, &n3) == true);

	EXPECT_EQ(&l, n1.list);
	EXPECT_EQ(&l, n2.list);
	EXPECT_EQ(&l, n3.list);

	EXPECT_EQ(&n1, l.head);

	EXPECT_EQ(&n3, n1.prev);
	EXPECT_EQ(&n2, n1.next);
	EXPECT_EQ(n1.value, 5);

	EXPECT_EQ(&n1, n2.prev);
	EXPECT_EQ(&n3, n2.next);
	EXPECT_EQ(n2.value, 6);

	EXPECT_EQ(&n2, n3.prev);
	EXPECT_EQ(&n1, n3.next);
	EXPECT_EQ(n3.value, 7);
}

GTEST_TEST(cdll_tests, test_sort_insert) {
	cdll	  l;
	cdll_node nodes[5];

	unsigned int values[5] = {510, 106, 1000000, 0, (unsigned int)-1};
	unsigned int values_sorted[5] = {0, 106, 510, 1000000, (unsigned int)-1};
	unsigned int iter_head_val[5] = {510, 106, 106, 0, 0};

	EXPECT_TRUE(cdll_init(&l) == true);

	for (unsigned int i = 0; i < 5; i++) {
		nodes[i].value = values[i];
		EXPECT_TRUE(cdll_sort_insert_node(&l, &nodes[i]) == true);
		EXPECT_EQ(l.head->value, iter_head_val[i]);
	}

	unsigned int cnt = 0;
	for (cdll_node* it_node = (cdll_node*)l.head;;
		 it_node = (cdll_node*)it_node->next) {
		EXPECT_EQ(it_node->value, values_sorted[cnt]);
		cnt++;
		if ((it_node->next == l.head))
			break;
	}
	EXPECT_EQ(cnt, 5);
}

GTEST_TEST(cdll_tests, test_remove_node) {
	cdll	  l;
	cdll_node nodes[5];

	EXPECT_TRUE(cdll_init(&l) == true);

	for (unsigned int i = 0; i < 5; i++) {
		EXPECT_TRUE(cdll_sort_insert_node(&l, &nodes[i]) == true);
	}

	for (unsigned int i = 0; i < 5; i++) {
		cdll_remove_node(&l, &nodes[i]);

		if (l.head != NULL) {
			/* Make sure node is not present in the list */
			ASSERT_EQ(nodes[i].list, nullptr);
			volatile cdll_node* it = l.head;
			do {
				EXPECT_FALSE(it == &nodes[i]);
				it = it->next;
			} while (it != l.head);
		}
	}
}

GTEST_TEST(cdll_tests, test_remove_node_different_list) {
	cdll	  l, k;
	cdll_node node;

	EXPECT_TRUE(cdll_init(&l) == true);
	EXPECT_TRUE(cdll_init(&k) == true);
	EXPECT_TRUE(cdll_append(&l, &node) == true);
	EXPECT_FALSE(cdll_remove_node(&k, &node) == true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
