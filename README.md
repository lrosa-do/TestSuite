# TestSuite

TestSuite is a C++ testing framework designed to make unit testing easier and more organized.

## Features

- Support for testing integer, float, boolean, string, and time-based functions.
- Asynchronous test execution.


2. Include the `TestSuite.hpp` header file in your project.

3. Add your test cases using the provided `addTest` methods for different data types.

4. Run the tests synchronously with `runTests()` or asynchronously with `runTestsAsync()`.

5. Check the test results in the console output.

## Example

```cpp
#include "TestSuite.h"

// Define your test cases
void testAddition() {
    TestSuite testSuite;

    // Add integer test case
    testSuite.addTest("Integer Addition Test", []() { return 2 + 2; }, 4);

    // Add floating-point test case
    testSuite.addTest("Float Addition Test", []() { return 3.14f + 2.71f; }, 5.85f);

    // Add boolean test case
    testSuite.addTest("Boolean Test", []() { return true; }, true);

    // Add string test case
    testSuite.addTest("String Test", []() { return "hello"; }, "hello");

    // Run the tests
    testSuite.runTests();
}

int main() {
    testAddition();

    return 0;
}
```

Example Output
🚀 ------ Running 5 tests ------ 🚀

** RUN: Integer Test progress (20%)   ---------------------
            ✅ [OK] Expected [4] got [4]
** RUN: Float Test progress (40%)   ---------------------
            ✅ [OK] Expected [6.28] got [6.28]
** RUN: Boolean Test progress (60%)   ---------------------
            ❌ [KO] Expected [0] got [1]
** RUN: String Test progress (80%)   ---------------------
            ✅ [OK] Expected [hello] got [hello]
** RUN: Time Test progress (100%)   ---------------------
            ✅ [OK] is faster by -0.001 seconds  -1 ms

        ***  All tests completed ***

🏆           All tests passed :)          🏆
