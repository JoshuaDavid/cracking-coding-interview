
bin/linked_list_test: test/linked_list_test.c src/linked_list.c
	gcc test/linked_list_test.c -Iinclude -Isrc -lcheck_pic -o bin/linked_list_test
