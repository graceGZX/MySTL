#include "MyTest/vector_test.h"
#include "MyTest/list_test.h"
#include "MyTest/deque_test.h"
#include "MyTest/set_test.h"
#include "MyTest/map_test.h"
#include "MyTest/unordered_map_test.h"
#include "MyTest/unordered_set_test.h"
#include "MyTest/stack_test.h"
#include "MyTest/queue_test.h"


int main() {
    using namespace mystl::test;
    vector_test::vector_test();
    list_test::list_test();
    deque_test::deque_test();
    set_test::set_test();
    map_test::map_test();
    unordered_map_test::unordered_map_test();
    unordered_map_test::unordered_multimap_test();
    unordered_set_test::unordered_set_test();
    unordered_set_test::unordered_multiset_test();
    stack_test::stack_test();
    queue_test::queue_test();
    queue_test::priority_test();
    getchar();

    return 0;
}

