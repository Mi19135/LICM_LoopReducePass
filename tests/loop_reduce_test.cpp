#include <iostream>

int main() {
    int sum = 0;
    int N = 100;

    for (int i = 0; i < N; ++i) {
        sum += i;
    }

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
