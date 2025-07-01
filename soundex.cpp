/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <cctype>
#include <fstream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "SimpleTest.h"
#include "soundex.h"
using namespace std;

/* This function is intended to return a string which
 * includes only the letter characters from the original
 * (all non-letter characters are excluded)
 *
 * WARNING: The provided code is buggy!
 *
 * Add student test cases to identify which inputs to this function
 * are incorrectly handled. The origial function blindly assumes s[0] is a
 * valid letter and adds it to result without checking isalpha(s[0]).
 */
string lettersOnly(string s) {
//     string result = charToString(s[0]);
//     for (int i = 1; i < s.length(); i++) {
//         if (isalpha(s[i])) {
//             result += s[i];
//         }
//     }
//     return result;
// }
    string result;
    for (char c : s) {
        if (isalpha(c)) result += c;
    }
    return result;
}



string encodeToDigits(string s) {
    if (s.empty()) return "";
    string code;


    for (int i = 0; i < s.size(); i++) {
        char c = toupper(s[i]);
        if (c == 'B' || c == 'F' || c == 'P' || c == 'V') {
            code += '1';
        } else if (c == 'C' || c == 'G' || c == 'J' || c == 'K' ||
                   c == 'Q' || c == 'S' || c == 'X' || c == 'Z') {
            code += '2';
        } else if (c == 'D' || c == 'T') {
            code += '3';
        } else if (c == 'L') {
            code += '4';
        } else if (c == 'M' || c == 'N') {
            code += '5';
        } else if (c == 'R') {
            code += '6';
        } else { // A, E, I, O, U, H, W, Y
            code += '0';
        }
    }

    return code;
}
string removeDouble(string input) {
    string result = "";
    for (int i = 0;i < input.length()-1;i++) {
        if (input[i] != input[i + 1]) {
            result += input[i];
        }
    }
    if (!input.empty()) {
        result += input.back();
    }
    return result;
}

string removeZero(string s){
    string result ="";
    for(int i = 1;i < s.length();i++) {
        if(s[i] != '0'){
            result += s[i];
        }
    }
    return result;
}
/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string s) {
    if (s.empty()) return "";
    string letters = lettersOnly(s);
    if (letters.empty()) return "";
    char firstLetter = toupper(letters[0]);


    string encoded = encodeToDigits(letters);
    string deduped = removeDouble(encoded);
    deduped[0] = firstLetter;


    string finalCode;
    finalCode += deduped[0];
    for (int i = 1; i < deduped.size(); ++i) {
        if (deduped[i] != '0') {
            finalCode += deduped[i];
        }
    }
    while (finalCode.size() < 4) {
        finalCode += '0';
    }
    return finalCode.substr(0, 4);
}



/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    // The names read from file are now stored in Vector allNames

    /* TODO: Fill in the remainder of this function. */
    while (true){

        string surname = getLine("Enter a Surname (RETURN to quit): ");
        if (surname == ""){
            cout << "All done!" << endl;
            break;
        }
        Vector<string> listofName = {};
        string username = soundex(surname);
        for (string name: allNames){
            string soundexName = soundex(name);
            if (username == soundexName){
                listofName.add(name);
            }

        }
        listofName.sort();
        cout << "Soundex code is " << username << endl;
        cout << "Matches from database: " << listofName << endl;
    }

}


/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!

STUDENT_TEST("Test lettersOnly with non-letter first character") {
    string s = "123Apple";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "Apple");

}

STUDENT_TEST("Test lettersOnly with non-letter first character2"){
    string s2 = "";
    string result2 = lettersOnly(s2);
    EXPECT_EQUAL(result2, "");
}
STUDENT_TEST("Test lettersOnly with non-letter first character 3"){
    string s3 = "!@#XYZ";
    string result3 = lettersOnly(s3);
    EXPECT_EQUAL(result3,"XYZ");
}

STUDENT_TEST("encode text - Gong") {
    string Gong = "Gong";
    string result1 = encodeToDigits(Gong);
    string result2 = removeDouble(result1);
    EXPECT_EQUAL(result2, "2052");
}
STUDENT_TEST("test empty string encodeToDigits") {
    string s = "";
    string result = encodeToDigits(s);
    EXPECT_EQUAL(result, "");
}

STUDENT_TEST("encodeToDigits encode text - HAPPY") {
    string s = "HAPPY";
    string result = encodeToDigits(s);
    EXPECT_EQUAL(result, "00110");
}

STUDENT_TEST("remove double - 222025") {
    string s = "222025";
    string result = removeDouble(s);
    EXPECT_EQUAL(result, "2025");
}
STUDENT_TEST("All other soundex test"){
    EXPECT_EQUAL(soundex(""), "");
    EXPECT_EQUAL(soundex("123-''"), "");
    EXPECT_EQUAL(soundex("AEIOUY"), "A000");
    EXPECT_EQUAL(soundex("SMITH"), "S530");
    EXPECT_EQUAL(soundex("sMiTh"), "S530");
    }
/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("Test exclude of punctuation, digits, and spaces") {
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}
