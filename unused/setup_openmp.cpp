#include <iostream>
#include <omp.h>
#include <sstream>
using namespace std;

string atomic_message(const string &message) {
    stringstream s;
    s << message << omp_get_thread_num();
    string se;
    s >> se;
    return se;
}

int main() {
#pragma omp parallel
    {
        cout << atomic_message("Hello");
        cout << atomic_message("World");
    }
    return 0;
}