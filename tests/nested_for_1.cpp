// nested_for_1.cpp
void foo_nested() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        int outer_invariant = 5 + 10; // invariant (spoljašnja)
        for (int j = 0; j < 2; j++) {
            int inner_invariant = 7 * 2; // invariant (unutrašnja)
            sum += outer_invariant + inner_invariant + i + j;
        }
    }
}
