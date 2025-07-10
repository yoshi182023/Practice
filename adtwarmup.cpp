#include "queue.h"
#include "stack.h"
#include "SimpleTest.h"
using namespace std;

/* This function correctly reverses the elements of a queue.*/
void reverse(Queue<int>& q) {
    Stack<int> s;
    int num;

    while (!q.isEmpty()) {
        num = q.dequeue();
        s.push(num);
    }
    while (!s.isEmpty()) {
        num = s.pop();
        q.enqueue(num);
    }
}

/* This function is intended to modify a queue of integers to duplicate
 * any negative numbers.*
 * WARNING: the given code is buggy. See exercise writeup for more
 * information on how to test and diagnose.
 */
void duplicateNegatives(Queue<int>& q) {
    int size = q.size();
    for (int i = 0; i < size; i++) {
        int val = q.dequeue();
        q.enqueue(val);
        if (val < 0) {
            q.enqueue(val);   // double up on negative numbers
        }
    }
}

/* This function is intended to return the sum of all values in
 * the stack
 *
 * WARNING: the given code is buggy. See exercise writeup for more
 * information on how to test and diagnose.
 */
int sumStack(Stack<int> s) {
//   int total = s.pop();
//     while (s.peek()) {

//         total += s.pop();
//     }
//     return total;
// }
int sum = 0;
while (!s.isEmpty()) {
    sum += s.pop();
}
return sum;
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("reverse queue") {
    Queue<int> q = {1, 2, 3, 4, 5};
    Queue<int> expected = {5, 4, 3, 2, 1};

    reverse(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("duplicateNegatives, input has no negatives") {
    Queue<int> q = {2, 10};
    Queue<int> expected = q;

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("duplicateNegatives, input has one negative, one positive") {
    Queue<int> q = {-7, 9};
    Queue<int> expected = {-7, -7, 9};

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}
STUDENT_TEST("Test duplicateNegatives with single negative number") {
    Queue<int> q = {-3}; // Minimal test case: queue with one negative number
    duplicateNegatives(q);

    Queue<int> expected = {-3, -3}; // After duplication
    EXPECT_EQUAL(q, expected);
}
STUDENT_TEST("Test duplicateNegatives with more negative numbers than positve numbers") {
    Queue<int> q = {-3,1,-3};
    duplicateNegatives(q);

    Queue<int> expected = {-3, -3,1,-3,-3}; // After duplication

    EXPECT_EQUAL(q, expected);
}
PROVIDED_TEST("duplicateNegatives, input has negatives interspersed with positives") {
    Queue<int> q = {-3, 4, -5, 10};
    Queue<int> expected = {-3, -3, 4, -5, -5, 10};

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("sumStack, 3 elements") {
    Stack<int> s = {1, 8, -5};

    EXPECT_EQUAL(sumStack(s), 4);
}

PROVIDED_TEST("sumStack, empty stack") {
    Stack<int> empty;

    EXPECT_EQUAL(sumStack(empty), 0);
}
