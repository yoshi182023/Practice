// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "SimpleTest.h"

using namespace std;


/* Iterates through each character in the input string
    - Checks if character is alphabetic (converting to lowercase) or numeric
    - Appends valid characters to result string
    - Returns "cleaned" version or empty string if no valid characters found */
string cleanToken(string s) {
    string result;
    for (char c : s) {
        if (isalpha(c)) result += tolower(c);
        else if (isdigit(c)) result += c;
    }
    return result;
}

/* Uses stringSplit() from for initial word splitting
 * Applies cleanToken() to each raw token
 * Only adds non-empty cleaned tokens to result set,
 * Extracts and returns a set of unique, cleaned tokens from the given text.
*/
Set<string> gatherTokens(string text) {
    Set<string> tokens;
    Vector<string> longText = stringSplit(text, " ");
    for (string word : longText) {
        string cleaned = cleanToken(word);
        if (!cleaned.empty()) {
            tokens.add(cleaned);
        }
    }
    cout << tokens << endl;

    return tokens;
}

//Constructs an inverted index mapping keywords to the URLs of web pages
// where those keywords appear.
int buildIndex(string dbfile, Map<string, Set<string>>& index) {
    ifstream in;
    if (!openFile(in,dbfile ))
        error("Cannot open file named " + dbfile);
    Vector<string> lines = readLines(in);
    int pageCount = lines.size() / 2;  // Each page = 2 lines (URL + content)
    for (int i = 0; i < lines.size(); i += 2) {
        string url = lines[i]; // www.shoppinglist.com
        string content = lines[i+1]; // milk, fish, bread, 5lb_m&ms
        // Extract unique tokens
        Set<string> tokens = gatherTokens(content);
        // Update inverted index
        for (string token : tokens) {
            index[token].add(url);
            // auto inserts token as a new key, even if it's not already in map
        }
    }
    return pageCount;
}

/**Finds all web pages that match the given query string by processing search terms and modifiers.
 * This function parses a query string containing one or more search terms, optionally prefixed with
 * '+' (AND) or '-' (NOT) modifiers. It returns a set of URLs that satisfy all query conditions.
 * @param index The inverted index mapping keywords to sets of URLs
 * @param query The search query string (e.g., "apple +banana -cherry")
 * @return Set<string> URLs matching all query conditions
 * @example
 *   Index: {"apple": {"url1"}, "banana": {"url1","url2"}}
 *   findQueryMatches(index, "apple +banana") → {"url1"}
 *   findQueryMatches(index, "banana -apple") → {"url2"}
 */
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query) {
    Set<string> result;

    Vector<string> terms = stringSplit(query, " ");
    cout <<"terms" << terms  << endl;
    //if (terms.isEmpty()) return result;
    string firstTerm = cleanToken(terms[0]);
    if (index.containsKey(firstTerm)) {
        cout <<"index" << index  << endl;
        cout <<"firstTerm : " << firstTerm  << endl;
        result = index[firstTerm];
    }
    for (int i = 1; i < terms.size(); i++) {
        string term = terms[i];
        char modifier = (term[0] == '+' || term[0] == '-') ? term[0] : '\0';
        string word = cleanToken(modifier ? term.substr(1) : term);

        if (!index.containsKey(word)) {
            if (modifier == '+') result.clear(); // not exsit -> no reuslt
            continue;
        }
        const Set<string>& matches = index[word];
        if (modifier == '+') {
            result.intersect(matches); // AND
        } else if (modifier == '-') {
            result.difference(matches); // NOT
        } else {
            result.unionWith(matches); // OR
        }
    }
    return result;
}

/*
 * Implements a search engine that builds and queries an inverted index from a database file.
 * - Reads webpage data from the specified file (alternating URL/content lines)
 * - Constructs an inverted index mapping tokens to URLs
 * - Processes user queries to find matching pages
 * - Displays search results with relevant URLs
 */
void searchEngine(string dbfile) {
    // TODO: your code here
    cout << "Stand by while building index..." << endl;
    //  Build the inverted index
    Map<string, Set<string>> index;
    int pageNum = buildIndex(dbfile, index);
    cout << "Indexed " << pageNum <<  " pages containing " << index.size() << " unique terms" << endl << endl;

    while (true) {
        cout << endl << "Enter query sentence (RETURN/ENTER to quit):" << endl;
        string query = getLine();  // Proper input handling


        if (query.empty()) {
            cout << "Goodbye!" << endl;
            break;
        }
        // Process query and print results
        Set<string> results;
        results = findQueryMatches(index, query);
        if (results.isEmpty()) {
            cout << "No matches found." << endl;
        } else {
            cout << "Found " << results.size() << " matching pages" << endl;
            cout << results << endl;
        }
    }
}

/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!
STUDENT_TEST("Last test") {
    TIME_OPERATION("website.txt", searchEngine("res/website.txt"));

}
STUDENT_TEST("buildIndex test") {
    Map<string, Set<string>> index;
    TIME_OPERATION("website.txt", buildIndex("res/website.txt", index));
    EXPECT(index.containsKey("cs106b"));
    EXPECT(index["computer"].size() > 5);
}

STUDENT_TEST("cleanToken test1") {
    EXPECT_EQUAL(cleanToken("U.S.A"), "usa");
    EXPECT_EQUAL(cleanToken("$100%"), "100");
    EXPECT_EQUAL(cleanToken("C++"), "c");
    EXPECT_EQUAL(cleanToken("Python3.9"), "python39");
}

STUDENT_TEST("cleanToken test2") {
    EXPECT_EQUAL(cleanToken(""), "");
    EXPECT_EQUAL(cleanToken("!@#$"), "");
    EXPECT_EQUAL(cleanToken("1234"), "1234");
    EXPECT_EQUAL(cleanToken("   "), "");
}
STUDENT_TEST("gatherTokens test1") {
    Set<string> expected = {"hello", "world"};
    EXPECT_EQUAL(gatherTokens("Hello world!"), expected);
}
STUDENT_TEST("gatherTokens test2") {
    Set<string> expected = {"apple"};
    EXPECT_EQUAL(gatherTokens("apple Apple APPLE!"), expected);

    expected = {"a", "b"};
    EXPECT_EQUAL(gatherTokens("a b a b a b"), expected);
}

STUDENT_TEST("gatherTokens test3") {
    EXPECT_EQUAL(gatherTokens("").isEmpty(), true);
    EXPECT_EQUAL(gatherTokens("!@#$ %^&*()").isEmpty(), true);
    EXPECT_EQUAL(gatherTokens("12345").size(), 1);
    EXPECT_EQUAL(gatherTokens("    ").isEmpty(), true);
}

/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("cleanToken on strings of letters and digits") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS106B"), "cs106b");
}

PROVIDED_TEST("cleanToken on strings containing punctuation") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
    EXPECT_EQUAL(cleanToken("they're"), "theyre");
}

PROVIDED_TEST("cleanToken on string of only punctuation") {
    EXPECT_EQUAL(cleanToken("+#$^@@.;"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("+go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 6 unique tokens, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 6);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 12 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 12);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}
