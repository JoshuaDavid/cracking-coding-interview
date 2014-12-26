#include "AVLTree.cpp"
// check.h defines fail as a macro, so it should be included last.
#include <check.h>

START_TEST(test_AVLTree_balanced_on_insertion) {
    AVLTree<int,int> *tree = new AVLTree<int,int>();
    for(int i = 1; i < 1024; i++) {
        tree->insert(i, 0);
    }
    ck_assert(tree->root->depth <= 12);
    delete tree;
} END_TEST;

Suite *AVLTree_suite(void) {
    Suite *s;
    s = suite_create("AVL Tree");

    TCase *tc_class_AVLTree = tcase_create("class_AVLTree");
    tcase_add_test(tc_class_AVLTree, test_AVLTree_balanced_on_insertion);
    suite_add_tcase(s, tc_class_AVLTree);

    return s;
}

int main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s = AVLTree_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
