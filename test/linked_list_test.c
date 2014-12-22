#include <check.h>
#include "linked_list.c"

START_TEST(test_empty_array_gives_null) {
    int *array = NULL;
    sl_node *list = sl_list_from_array(array, 0);
    ck_assert(list == NULL);
} END_TEST

START_TEST(test_nonempty_array_gives_node) {
    int array[2] = {1, 2};
    sl_node *list = sl_list_from_array(array, 2);
    ck_assert(list != NULL);
} END_TEST

START_TEST(test_empty_linked_list_has_length_0) {
    int *array = NULL;
    sl_node *list = sl_list_from_array(array, 0);
    ck_assert_int_eq(sl_list_length(list), 0);
} END_TEST

START_TEST(test_linked_list_has_correct_length) {
    int array[2] = {1, 2};
    sl_node *list = sl_list_from_array(array, 2);
    ck_assert_int_eq(sl_list_length(list), 2);
} END_TEST

START_TEST(test_null_list_ne_non_null_list) {
    int *array_a = NULL;
    int array_b[2] = {1, 2};
    sl_node *first_a = sl_list_from_array(array_a, 0);
    sl_node *first_b = sl_list_from_array(array_b, 2);
    ck_assert(!sl_lists_equal(first_a, first_b));
} END_TEST

START_TEST(test_null_lists_are_equal) {
    int *array_a = NULL;
    int *array_b = NULL;
    sl_node *first_a = sl_list_from_array(array_a, 0);
    sl_node *first_b = sl_list_from_array(array_b, 0);
    ck_assert(sl_lists_equal(first_a, first_b));
} END_TEST

START_TEST(test_unequal_lists_are_unequal) {
    int array_a[2] = {1, 2};
    int array_b[2] = {1, 3};
    sl_node *first_a = sl_list_from_array(array_a, 2);
    sl_node *first_b = sl_list_from_array(array_b, 2);
    ck_assert(!sl_lists_equal(first_a, first_b));
} END_TEST

START_TEST(test_equal_lists_are_equal) {
    int array_a[2] = {1, 2};
    int array_b[2] = {1, 2};
    sl_node *first_a = sl_list_from_array(array_a, 2);
    sl_node *first_b = sl_list_from_array(array_b, 2);
    ck_assert(sl_lists_equal(first_a, first_b));
} END_TEST

START_TEST(test_0th_node_is_self) {
    int array[5] = {1, 2, 3, 4, 5};
    sl_node *first = sl_list_from_array(array, 5);
    ck_assert(sl_nth_node(first, 0) == first);
} END_TEST

START_TEST(test_nth_past_end_is_null) {
    int array[5] = {1, 2, 3, 4, 5};
    sl_node *first = sl_list_from_array(array, 5);
    ck_assert(sl_nth_node(first, 7) == NULL);
} END_TEST

START_TEST(test_3rd_gives_3rd) {
    int array[5] = {1, 2, 3, 4, 5};
    sl_node *first = sl_list_from_array(array, 5);
    ck_assert(sl_nth_node(first, 3) == first->next->next->next);
} END_TEST

START_TEST(test_empty_list_midpoint_is_null) {
    int *array = NULL;
    sl_node *list = sl_list_from_array(array, 0);
    ck_assert(sl_list_midpoint(list) == NULL);
} END_TEST

START_TEST(test_evenlength_list_midpoint_is_len_over_2) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *list = sl_list_from_array(array, 10);
    sl_node *sixth = sl_nth_node(list, 5);
    sl_node *mid = sl_list_midpoint(list);
    ck_assert(sixth == mid);
} END_TEST

START_TEST(test_oddlength_list_midpoint_is_len_over_2) {
    int array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    sl_node *list = sl_list_from_array(array, 9);
    sl_node *fifth = sl_nth_node(list, 4);
    sl_node *mid = sl_list_midpoint(list);
    ck_assert(fifth == mid);
} END_TEST

START_TEST(test_empty_list_concat_is_null) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 0);
    sl_node *first_b = sl_list_from_array(array_b, 0);
    sl_node *catted = sl_concat(first_a, first_b);
    ck_assert(catted == NULL);
} END_TEST

START_TEST(test_cat_with_empty_is_self) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 5);
    sl_node *first_b = sl_list_from_array(array_b, 0);
    sl_node *catted = sl_concat(first_a, first_b);
    ck_assert(catted == first_a);
} END_TEST

START_TEST(test_empty_catted_with_other_is_other) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 0);
    sl_node *first_b = sl_list_from_array(array_b, 5);
    sl_node *catted = sl_concat(first_a, first_b);
    ck_assert(catted == first_b);
} END_TEST

START_TEST(test_catted_lists_have_correct_combined_length) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 5);
    sl_node *first_b = sl_list_from_array(array_b, 5);
    sl_node *catted = sl_concat(first_a, first_b);
    ck_assert(sl_list_length(catted) == 10);
} END_TEST

START_TEST(test_compare) {
    ck_assert_int_eq(-1, compare(1, 2));
    ck_assert_int_eq( 1, compare(2, 1));
    ck_assert_int_eq( 0, compare(1, 1));
} END_TEST

START_TEST(test_sl_merge_two_empty) {
    ck_assert(NULL == sl_merge(NULL, NULL, compare));
} END_TEST

START_TEST(test_sl_merge_list_and_empty) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 5);
    sl_node *first_b = sl_list_from_array(array_b, 0);
    ck_assert(first_a == sl_merge(first_a, first_b, compare));
} END_TEST

START_TEST(test_sl_merge_empty_and_list) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 0);
    sl_node *first_b = sl_list_from_array(array_b, 5);
    ck_assert(first_b == sl_merge(first_a, first_b, compare));
} END_TEST

START_TEST(test_sl_merge_lists_ordered) {
    int array_a[5] = {1, 2, 3, 4, 5};
    int array_b[5] = {6, 7, 8, 9, 10};
    int array_all[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 5);
    sl_node *first_b = sl_list_from_array(array_b, 5);
    sl_node *merged = sl_merge(first_a, first_b, compare);
    sl_node *first_all = sl_list_from_array(array_all, 10);
    ck_assert(sl_lists_equal(first_all, merged));
} END_TEST

START_TEST(test_sl_merge_lists_descending) {
    int array_a[5] = {10, 9, 8, 7, 6};
    int array_b[5] = {5, 4, 3, 2, 1};
    int array_all[10] = {5, 4, 3, 2, 1, 10, 9, 8, 7, 6};
    sl_node *first_a = sl_list_from_array(array_a, 5);
    sl_node *first_b = sl_list_from_array(array_b, 5);
    sl_node *merged = sl_merge(first_a, first_b, compare);
    sl_node *first_all = sl_list_from_array(array_all, 10);
    ck_assert(sl_lists_equal(first_all, merged));
} END_TEST

START_TEST(test_sl_merge_lists_ascending) {
    int array_a[5] = {1, 3, 5, 7, 9};
    int array_b[5] = {2, 4, 6, 8, 10};
    int array_all[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first_a = sl_list_from_array(array_a, 5);
    sl_node *first_b = sl_list_from_array(array_b, 5);
    sl_node *merged = sl_merge(first_a, first_b, compare);
    sl_node *first_all = sl_list_from_array(array_all, 10);
    ck_assert(sl_lists_equal(first_all, merged));
} END_TEST

START_TEST(test_sl_split_at_midpoint_of_empty) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 0);
    ck_assert(NULL == sl_split_at_midpoint(first));
} END_TEST

START_TEST(test_sl_split_at_midpoint_of_single) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 1);
    ck_assert(first == sl_split_at_midpoint(first));
    ck_assert(first->next == NULL);
} END_TEST

START_TEST(test_sl_split_at_midpoint_of_pair) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 2);
    sl_node *second = first->next;
    ck_assert(second == sl_split_at_midpoint(first));
    ck_assert(first->next == NULL);
} END_TEST

START_TEST(test_sl_split_at_midpoint_of_9_el) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 9);
    sl_node *fourth = sl_nth_node(first, 3);
    sl_node *fifth = sl_nth_node(first, 4);
    ck_assert(fifth == sl_split_at_midpoint(first));
    ck_assert_int_eq(sl_list_length(first), 4);
    ck_assert_int_eq(sl_list_length(fifth), 5);
    ck_assert(fourth->next == NULL);
} END_TEST

START_TEST(test_sl_split_at_midpoint_of_10_el) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *fifth = sl_nth_node(first, 4);
    sl_node *sixth = sl_nth_node(first, 5);
    ck_assert(sixth == sl_split_at_midpoint(first));
    ck_assert_int_eq(sl_list_length(first), 5);
    ck_assert_int_eq(sl_list_length(sixth), 5);
    ck_assert(fifth->next == NULL);
} END_TEST

START_TEST(test_sl_merge_sort_empty) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 0);
    ck_assert(NULL == sl_merge_sort(first, compare));
} END_TEST

START_TEST(test_sl_merge_sort_single) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 1);
    ck_assert(sl_lists_equal(first, sl_merge_sort(first, compare)));
} END_TEST

START_TEST(test_sl_merge_sort_forward) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *expected_first = sl_list_from_array(expected, 10);
    ck_assert(sl_lists_equal(expected_first, sl_merge_sort(first, compare)));
} END_TEST

START_TEST(test_sl_merge_sort_reversed) { 
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    int expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *expected_first = sl_list_from_array(expected, 10);
    ck_assert(sl_lists_equal(expected_first, sl_merge_sort(first, compare)));
} END_TEST

START_TEST(test_has_cycle_empty) {
    ck_assert(0 == sl_list_has_cycle(NULL));
} END_TEST

START_TEST(test_has_cycle_non_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    ck_assert(0 == sl_list_has_cycle(first));
} END_TEST

START_TEST(test_has_cycle_1_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    tenth->next = tenth;
    ck_assert(1 == sl_list_has_cycle(first));
} END_TEST

START_TEST(test_has_cycle_2_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    sl_node *ninth = sl_nth_node(first, 8);
    tenth->next = ninth;
    ck_assert(1 == sl_list_has_cycle(first));
} END_TEST

START_TEST(test_has_cycle_5_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    sl_node *fifth = sl_nth_node(first, 4);
    tenth->next = fifth;
    ck_assert(1 == sl_list_has_cycle(first));
} END_TEST

START_TEST(test_has_cycle_full_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    tenth->next = first;
    ck_assert(1 == sl_list_has_cycle(first));
} END_TEST

START_TEST(test_cycle_start_empty) {
    ck_assert(NULL == sl_list_cycle_start(NULL));
} END_TEST

START_TEST(test_cycle_start_non_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    ck_assert(NULL == sl_list_cycle_start(first));
} END_TEST

START_TEST(test_cycle_start_1_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    tenth->next = tenth;
    ck_assert(tenth == sl_list_cycle_start(first));
} END_TEST

START_TEST(test_cycle_start_2_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    sl_node *ninth = sl_nth_node(first, 8);
    tenth->next = ninth;
    ck_assert(ninth == sl_list_cycle_start(first));
} END_TEST

START_TEST(test_cycle_start_5_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    sl_node *fifth = sl_nth_node(first, 4);
    tenth->next = fifth;
    ck_assert(fifth == sl_list_cycle_start(first));
} END_TEST

START_TEST(test_cycle_start_full_cycle) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    sl_node *first = sl_list_from_array(array, 10);
    sl_node *tenth = sl_nth_node(first, 9);
    tenth->next = first;
    ck_assert(first == sl_list_cycle_start(first));
} END_TEST

Suite *linked_list_suite(void) {
    Suite *s;
    s = suite_create("Singly Linked List");

    TCase *tc_sl_list_from_array;
    tc_sl_list_from_array = tcase_create("sl_list_from_array");
    tcase_add_test(tc_sl_list_from_array, test_empty_array_gives_null);
    tcase_add_test(tc_sl_list_from_array, test_nonempty_array_gives_node);
    suite_add_tcase(s, tc_sl_list_from_array);

    TCase *tc_sl_list_length = tcase_create("sl_list_length");
    tcase_add_test(tc_sl_list_length, test_empty_linked_list_has_length_0);
    tcase_add_test(tc_sl_list_length, test_linked_list_has_correct_length);
    suite_add_tcase(s, tc_sl_list_length);

    TCase *tc_sl_lists_equal = tcase_create("sl_lists_equal");
    tcase_add_test(tc_sl_lists_equal, test_equal_lists_are_equal);
    tcase_add_test(tc_sl_lists_equal, test_null_lists_are_equal);
    tcase_add_test(tc_sl_lists_equal, test_unequal_lists_are_unequal);
    tcase_add_test(tc_sl_lists_equal, test_null_list_ne_non_null_list);
    suite_add_tcase(s, tc_sl_lists_equal);
    
    TCase *tc_sl_nth_node = tcase_create("sl_nth_node");
    tcase_add_test(tc_sl_nth_node, test_0th_node_is_self); 
    tcase_add_test(tc_sl_nth_node, test_nth_past_end_is_null); 
    tcase_add_test(tc_sl_nth_node, test_3rd_gives_3rd); 
    suite_add_tcase(s, tc_sl_nth_node);

    TCase *tc_sl_midpoint = tcase_create("sl_midpoint");
    tcase_add_test(tc_sl_midpoint, test_empty_list_midpoint_is_null);
    tcase_add_test(tc_sl_midpoint, test_evenlength_list_midpoint_is_len_over_2);
    tcase_add_test(tc_sl_midpoint, test_oddlength_list_midpoint_is_len_over_2);
    suite_add_tcase(s, tc_sl_midpoint);

    TCase *tc_compare = tcase_create("compare");
    tcase_add_test(tc_compare, test_compare);
    suite_add_tcase(s, tc_compare);

    TCase *tc_sl_concat = tcase_create("sl_concat");
    tcase_add_test(tc_sl_concat, test_empty_list_concat_is_null);
    tcase_add_test(tc_sl_concat, test_cat_with_empty_is_self);
    tcase_add_test(tc_sl_concat, test_empty_catted_with_other_is_other);
    tcase_add_test(tc_sl_concat, test_catted_lists_have_correct_combined_length);
    suite_add_tcase(s, tc_sl_concat);

    TCase *tc_sl_merge = tcase_create("sl_merge");
    tcase_add_test(tc_sl_merge, test_sl_merge_two_empty);
    tcase_add_test(tc_sl_merge, test_sl_merge_list_and_empty);
    tcase_add_test(tc_sl_merge, test_sl_merge_empty_and_list);
    tcase_add_test(tc_sl_merge, test_sl_merge_lists_ascending);
    tcase_add_test(tc_sl_merge, test_sl_merge_lists_descending);
    tcase_add_test(tc_sl_merge, test_sl_merge_lists_ordered);
    suite_add_tcase(s, tc_sl_merge);

    TCase *tc_sl_split_at_midpoint = tcase_create("sl_split_at_midpoint");
    tcase_add_test(tc_sl_split_at_midpoint, test_sl_split_at_midpoint_of_empty);
    tcase_add_test(tc_sl_split_at_midpoint, test_sl_split_at_midpoint_of_single);
    tcase_add_test(tc_sl_split_at_midpoint, test_sl_split_at_midpoint_of_pair);
    tcase_add_test(tc_sl_split_at_midpoint, test_sl_split_at_midpoint_of_9_el);
    tcase_add_test(tc_sl_split_at_midpoint, test_sl_split_at_midpoint_of_10_el);
    suite_add_tcase(s, tc_sl_split_at_midpoint);

    TCase *tc_sl_merge_sort = tcase_create("sl_merge_sort");
    tcase_add_test(tc_sl_merge_sort, test_sl_merge_sort_empty);
    tcase_add_test(tc_sl_merge_sort, test_sl_merge_sort_single);
    tcase_add_test(tc_sl_merge_sort, test_sl_merge_sort_forward);
    tcase_add_test(tc_sl_merge_sort, test_sl_merge_sort_reversed);
    suite_add_tcase(s, tc_sl_merge_sort);

    TCase *tc_sl_list_has_cycle = tcase_create("sl_list_has_cycle");
    tcase_add_test(tc_sl_list_has_cycle, test_has_cycle_empty);
    tcase_add_test(tc_sl_list_has_cycle, test_has_cycle_non_cycle);
    tcase_add_test(tc_sl_list_has_cycle, test_has_cycle_1_cycle);
    tcase_add_test(tc_sl_list_has_cycle, test_has_cycle_2_cycle);
    tcase_add_test(tc_sl_list_has_cycle, test_has_cycle_5_cycle);
    tcase_add_test(tc_sl_list_has_cycle, test_has_cycle_full_cycle);
    suite_add_tcase(s, tc_sl_list_has_cycle);

    TCase *tc_sl_list_cycle_start = tcase_create("sl_list_cycle_start");
    tcase_add_test(tc_sl_list_cycle_start, test_cycle_start_empty);
    tcase_add_test(tc_sl_list_cycle_start, test_cycle_start_non_cycle);
    tcase_add_test(tc_sl_list_cycle_start, test_cycle_start_1_cycle);
    tcase_add_test(tc_sl_list_cycle_start, test_cycle_start_2_cycle);
    tcase_add_test(tc_sl_list_cycle_start, test_cycle_start_5_cycle);
    tcase_add_test(tc_sl_list_cycle_start, test_cycle_start_full_cycle);
    suite_add_tcase(s, tc_sl_list_cycle_start);

    /*
    TCase *tc_xxxxx = tcase_create("xxxxx");
    tcase_add_test(tc_xxxxx, test_xxxxx);
    suite_add_tcase(s, tc_xxxxx);
    */

    return s;
}

int main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s = linked_list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
