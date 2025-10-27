// nested_while_do_1.cpp
void foo_nested_while() {
    int sum = 0;
    int i = 0;

    while (i < 3) {
        int outer_invariant = 5 + 10; // invariant (spoljašnja while)

        int j = 0;
        do {
            int inner_invariant = 7 * 2; // invariant (unutrašnja do-while)
            sum += outer_invariant + inner_invariant + i + j;
            j++;
        } while (j < 2);

        i++;
    }
}
