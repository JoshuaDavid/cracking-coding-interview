bin/linked_list_test: test/linked_list_test.cpp src/linked_list.cpp
	g++ test/linked_list_test.cpp -Iinclude -Isrc -lcheck_pic -o bin/linked_list_test

clean:
	rm bin/*
