// simple_for_1.cpp
void foo() {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        int a = 1 + 2; // invariant
        sum += a + i;
    }
}
