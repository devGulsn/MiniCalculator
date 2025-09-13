#include <iostream>
#include <string>
#include "calculator.h"

using namespace std;

int main() {
    Calculator calc;
    string input;

    cout << "Mini Calculator\nType 'exit' to quit\n\n";

    for (;;) {
        cout << "> ";
        getline(cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        try {
            double result = calc.evaluate(input);
            cout << "Result: " << result << "\n";
        } catch (const exception& ex) {
            cout << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}
