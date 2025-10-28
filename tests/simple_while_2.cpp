void foo() {
    int total = 0;
    int i = 0;
    while (i < 10) {
        int a = 2 + 3;      // invariant
        int b = a * 4;      // invariant (zavisi od a)
        total += b + i;
        i++;
    }
}

