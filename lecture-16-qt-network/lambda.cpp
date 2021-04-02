#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Printer {
    ostream& stream;

    Printer(ostream& stream) : stream(stream) { }

    void operator()(int v) {
        stream << v << endl;
    }
};

int main() {
    vector<int> data = { 1, 2, 3, 4, 5 };

    stringstream stream1;
    Printer printer(stream1);
    for_each(data.begin(), data.end(), printer);
    cout << stream1.str() << endl;

    stringstream stream2;
    for_each(data.begin(), data.end(), [&stream2](int v) {
        stream2 << v << endl;
    });
    cout << stream2.str() << endl;
}
