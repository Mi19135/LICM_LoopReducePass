// nested_for_2.cpp
void foo_nested2() {
    int total = 0;
    for (int i = 0; i < 4; i++) {
        int outer = 10 + 1;  // invariant
        for (int j = 0; j < 3; j++) {
            int inner = outer * 2; // invariant (zavisi od outer)
            total += inner + i + j;
        }
    }
}
