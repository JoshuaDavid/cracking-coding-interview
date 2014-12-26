bin/doubly_linked_list_test: test/doubly_linked_list_test.cpp src/doubly_linked_list.cpp src/doubly_linked_node.cpp
	g++ test/doubly_linked_list_test.cpp -Iinclude -Isrc -lcheck_pic -o bin/doubly_linked_list_test

bin/linked_list_test: test/linked_list_test.cpp src/linked_list.cpp src/singly_linked_node.cpp
	g++ test/linked_list_test.cpp -Iinclude -Isrc -lcheck_pic -o bin/linked_list_test

clean:
	rm bin/*
