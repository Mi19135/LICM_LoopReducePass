void foo() {
    int sum = 0;
    int i = 0;
    while (i < 5) {
        int a = 1 + 2; // invariant
        sum += a + i;
        i++;
    }
}

