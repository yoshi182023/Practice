/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "SimpleTest.h"
#include "perfect.h"
#include <cmath>
// Required for sqrt()
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0; //test total =1;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}


long smarterSum(long n) {
    //edge case: smarterSum(0) --> 0
    if (n <= 1) return 0;
    long sum = 1;
    long sqrt_n = sqrt(n);

    for (long d = 2; d <= sqrt_n; d++) {
        if (n % d == 0) {
            sum += d;
            long complement = n / d;
            if (complement != d) {
                sum += complement;
            }
        }
    }
    return sum;
}

/* Simply replace divisorSum with smarterSum in the original isPerfect
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
     if (n <= 0) return false; // Explicitly handle non-positive inputs
    return (n != 0) && (n == smarterSum(n));

}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "#" << flush; // Progress indicator
    }
    cout << endl << "Done searching up to " << stop << endl;
}

bool isPrime(long m) {
    if (m <= 1) return false;
    return smarterSum(m) == 1;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    int k = 1;
    int numberFound = 0;
    while (true){
        long m = pow(2,k) -1;//  2^k - 1
        if (isPrime(m)){
            long perfectresult = pow(2,k-1)*(pow(2,k)-1);
            numberFound ++;
            if( n == numberFound){
                return perfectresult;
            }
        }
        k ++;
    }

}



/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!
STUDENT_TEST("Verify findNthPerfectEuclid generates correct perfect numbers") {
    EXPECT(isPerfect(findNthPerfectEuclid(2))); // 28
    EXPECT(isPerfect(findNthPerfectEuclid(3))); // 496
    EXPECT(isPerfect(findNthPerfectEuclid(4))); // 8128
     EXPECT(isPerfect(findNthPerfectEuclid(5)));
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
         EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT(isPrime(7));    // 2³-1 (prime)
    EXPECT(!isPrime(15));  // 2⁴-1 (not prime)
}
/*
 * Here is sample test demonstrating how to use a loop to set the input sizes
 * for a sequence of time trials.
 */
STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {
   int smallest = 1000, largest = 8000;
   for (int size = smallest; size <= largest; size *= 2) {
       TIME_OPERATION(size, findPerfects(size));
   }
}
STUDENT_TEST("Added student test : Multiple time trials of findPerfects on increasing sizes") {
    int startSize = 10000;
    for (int size = startSize; size <= 4 * startSize; size *= 2) {
        TIME_OPERATION(size, findPerfects(size));
    }
}
//comment out to save time
// STUDENT_TEST("# Added student test :Time trials of findPerfectsSmarter") {
//     int startSize = 8000000;
//     for (int size = startSize; size <= 4 * startSize; size *= 2) {
//         TIME_OPERATION(size,  findPerfectsSmarter(size));
//     }
// }
STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
    //comment out to save running time
    //TIME_OPERATION(80000, findPerfects(80000));
   // TIME_OPERATION(160000, findPerfects(160000));
   // TIME_OPERATION(320000, findPerfects(320000));
  //  TIME_OPERATION(640000, findPerfects(640000));
   // TIME_OPERATION(10240000, findPerfects(10240000));
}
/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */
STUDENT_TEST("Debug negative input") {
    long n = -36;
    long sum = divisorSum(n);
    cout << "divisorSum(" << n << ") = " << sum << endl;
    EXPECT_EQUAL(sum, 0);
}

STUDENT_TEST("Time trials of findPerfects on 10 and 1000") {
    TIME_OPERATION(10, findPerfects(10));
    TIME_OPERATION(1000, findPerfects(1000));
}
STUDENT_TEST("Time trials of findPerfects on 10 and 1000") {
    TIME_OPERATION(10, findPerfects(10));
    TIME_OPERATION(1000, findPerfects(1000));
}

STUDENT_TEST("Confirm -3 and -36 are perfect") {
    EXPECT(isPerfect(-3));
    EXPECT(isPerfect(-36));
}
STUDENT_TEST("Verify isPerfect returns false for negative inputs") {
    EXPECT(!isPerfect(-1));
    EXPECT(!isPerfect(-6));    // -6 is negative of first perfect number
    EXPECT(!isPerfect(-28));
    EXPECT(!isPerfect(-496));
}
//test cases for smarterSum:
//Verify the loop stops correctly at √n and avoids double-counting the square root.
STUDENT_TEST("test cases for smarterSum 0 : Test perfect square (n=25)") {
    EXPECT_EQUAL(smarterSum(25), divisorSum(25)); // 6
}
STUDENT_TEST("test cases for smarterSum 1：Test large number (n=33550336)") {
    EXPECT_EQUAL(smarterSum(33550336), divisorSum(33550336));
}
STUDENT_TEST("test cases for smarterSum 2:Test prime number (n=13)") {
    EXPECT_EQUAL(smarterSum(13), divisorSum(13)); // 1
}
STUDENT_TEST("test cases for smarterSum 3：Test real perfect number(n=28)") {
    EXPECT_EQUAL(smarterSum(28), divisorSum(28));
}
STUDENT_TEST("test cases for smarterSum 4:Test negative number(n=-3)") {
    EXPECT_EQUAL(smarterSum(-3), divisorSum(-3));
}
STUDENT_TEST("test cases for smarterSum: Test non-positive inputs") {
    EXPECT_EQUAL(smarterSum(-3), 0);
    EXPECT_EQUAL(smarterSum(0), 0);
    EXPECT_EQUAL(smarterSum(1), 0);
}

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfects(1000));
}
