// simple_for_2.cpp
void foo() {
    int total = 0;
    for (int i = 0; i < 10; i++) {
        int a = 2 + 3;      // invariant
        int b = a * 4;      // invariant (zavisi od a)
        total += b + i;
    }
}
