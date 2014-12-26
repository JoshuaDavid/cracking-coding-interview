#include "doubly_linked_list.cpp"
// check.h defines fail as a macro, so it should be included last.
#include <check.h>

START_TEST(test_LinkedList_constructor) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *list = new LinkedList<int>(array, 10);
    delete list;
} END_TEST

START_TEST(test_LinkedList_push_to_empty) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *before = new LinkedList<int>(array, 0);
    LinkedList<int> *after  = new LinkedList<int>(array, 1);
    ck_assert(!before->equals(after));
    before->push(10);
    ck_assert(before->equals(after, 1));
    delete before;
    delete after;
} END_TEST

START_TEST(test_LinkedList_push_to_nonempty) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *before = new LinkedList<int>(array, 3);
    LinkedList<int> *after  = new LinkedList<int>(array, 4);
    ck_assert(!before->equals(after));
    before->push(7);
    ck_assert(before->equals(after));
    delete before;
    delete after;
} END_TEST

START_TEST(test_LinkedList_unshift_to_empty) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *before = new LinkedList<int>(array, 0);
    LinkedList<int> *after  = new LinkedList<int>(array, 1);
    ck_assert(!before->equals(after));
    before->unshift(10);
    ck_assert(before->equals(after));
    delete before;
    delete after;
} END_TEST

START_TEST(test_LinkedList_unshift_to_nonempty) {
    int barray[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    int aarray[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *before = new LinkedList<int>(barray, 3);
    LinkedList<int> *after  = new LinkedList<int>(aarray, 4);
    ck_assert(!before->equals(after));
    before->unshift(10);
    ck_assert(before->equals(after));
    delete before;
    delete after;
} END_TEST

START_TEST(test_LinkedList_prevnext_is_self) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *list = new LinkedList<int>(array, 10);
    ck_assert(list->nth(6)->next == list->nth(7));
    ck_assert(list->nth(7)->prev == list->nth(6));
    delete list;
} END_TEST

START_TEST(test_LinkedList_equals) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *lista = new LinkedList<int>(array, 10);
    LinkedList<int> *listb = new LinkedList<int>(array, 10);
    // Not the same list
    ck_assert(lista != listb);
    // But they are equal
    ck_assert(lista->equals(listb));
    ck_assert(listb->equals(lista));
    delete lista;
    delete listb;
} END_TEST

START_TEST(test_LinkedList_clone) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *lista = new LinkedList<int>(array, 10);
    LinkedList<int> *listb = lista->clone();
    // Not the same list
    ck_assert(lista != listb);
    // But they are equal
    ck_assert(listb->equals(lista));
    delete lista;
    delete listb;
} END_TEST

START_TEST(test_LinkedList_concat) {
    int left[5]  = {1, 2, 3, 4, 5};
    int right[5] = {6, 7, 8, 9, 10};
    int full[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> *list_left  = new LinkedList<int>(left,  5);
    LinkedList<int> *list_right = new LinkedList<int>(right, 5);
    LinkedList<int> *list_full  = new LinkedList<int>(full, 10);
    LinkedList<int> *copy_right = list_right->clone();
    list_left->concat(list_right);
    // Concat does not affect the added list
    ck_assert(list_right->equals(copy_right));
    ck_assert(list_left->length == 10);
    delete list_left;
    delete list_right;
    delete list_full;
    delete copy_right;
} END_TEST

START_TEST(test_LinkedList_nth) {
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; 
    LinkedList<int> *list = new LinkedList<int>(array, 10);
    ck_assert_int_eq(list->nth(0)->value, 10);
    ck_assert_int_eq(list->nth(5)->value, 5);
    delete list;
} END_TEST

START_TEST(test_LinkedList_midpoint_empty) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    LinkedList<int> *list = new LinkedList<int>(array, 0);
    ck_assert(list->midpoint() == NULL);
    delete list;
} END_TEST

START_TEST(test_LinkedList_midpoint_oddlen) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    LinkedList<int> *list = new LinkedList<int>(array, 9);
    ck_assert_int_eq(list->midpoint()->value, 5);
    delete list;
} END_TEST

START_TEST(test_LinkedList_midpoint_evenlen) {
    int array[10] = {1, 2}; 
    LinkedList<int> *list = new LinkedList<int>(array, 2);
    ck_assert_int_eq(list->midpoint()->value, 2);
    delete list;
} END_TEST

START_TEST(test_LinkedList_sort) {
    int array[10] = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6}; 
    int sarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> *list = new LinkedList<int>(array, 10);
    LinkedList<int> *slist = new LinkedList<int>(sarray, 10);
    ck_assert(list->equals(slist));
    delete list;
} END_TEST

START_TEST(test_LinkedList_hasCycle) {
    int array[10] = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6}; 
    LinkedList<int> *list = new LinkedList<int>(array, 10);
    ck_assert(!list->hasCycle());
    list->last->next = list->nth(4);
    ck_assert(list->hasCycle());
    delete list;
} END_TEST

START_TEST(test_LinkedList_cycleStart) {
    int array[10] = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6}; 
    LinkedList<int> *list = new LinkedList<int>(array, 10);
    list->last->next = list->nth(4);
    ck_assert(list->cycleStart() == list->nth(4));
    delete list;
} END_TEST

Suite *linked_list_suite(void) {
    Suite *s;
    s = suite_create("Doubly Linked List");

    TCase *tc_class_Linked_List = tcase_create("class_Linked_List");
    tcase_add_test(tc_class_Linked_List, test_LinkedList_constructor);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_prevnext_is_self);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_equals);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_clone);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_concat);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_nth);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_midpoint_empty);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_midpoint_oddlen);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_midpoint_evenlen);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_hasCycle);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_cycleStart);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_push_to_empty);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_push_to_nonempty);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_unshift_to_empty);
    tcase_add_test(tc_class_Linked_List, test_LinkedList_unshift_to_nonempty);
    suite_add_tcase(s, tc_class_Linked_List);

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
