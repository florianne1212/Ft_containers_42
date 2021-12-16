#include <iostream>
#include <stack>
// #include "vector.hpp"
// #include "stack.hpp"
#include "map.hpp"
#include <deque>

#include <vector>
#include <list>
#include <map>

#include "test/test_vector.cpp"
#include "test/test_stack.cpp"
#include "test/test_map.cpp"

void next()
{
	std::string	buf;
	std::cout << "\033[1;36m \npress enter for continue ... \033[0m\n";
	std::getline (std::cin, buf);
}

#define T1 int
#define T2 int
typedef ft::pair<const T1, T2> T3;

int main ()
{
	//vector
	test_construct();
	test_operator();
	test_iterators();

	next();

	test_size();

	next();

	test_capacity();

	next();

	test_element_access();
	test_back_front();

	next();

	test_modifiers_add();
	test_modifiers_insert();
	test_modifiers_delete();

	std::cout << "\033[1;33m \nEntering Stack Test ... \033[0m\n";
	next();
	

	//stack
	test_stack_empty();
	test_stack_size();
	test_stack_top();
	test_stack_push_pop();

	//map
	std::cout << "\033[1;33m \nEntering Map Test ... \033[0m\n";
	next();
	test_map_construct();
	test_map_operator();

	next();

	test_map_iterator();

	next();

	test_map_capacity();

	next();

	test_map_operator_access();

	next();

	test_map_modifiers_insert_erase_std();
	test_map_modifiers_insert_erase_ft();

	next();

	test_map_modifiers();

	next();

	test_map_observers();

	next();

	test_map_operation();
	test_map_lower_upper_equal();

	next();
	
	test_map_allocator();
	

	return 0;

}