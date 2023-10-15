/**
 * @file .cpp
 * @brief [Word Break Problem]
 * @details
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, determine if s can be segmented into a space-separated
 * sequence of one or more dictionary words.
 *
 * Note:
 * The same word in the dictionary may be reused mulktiple times in the 
 * segmentation. You may assume the dictionary does not contain duplicate words.
 *
 * Example 1:
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 *
 * Example 2:
 * Input: s = "applepenapple", wordDict = ["apple", "pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
 * 
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output: false
 *
 */

#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

/*
 * @namespace Dynamic Programming
 * @brief Dynamic Programming Algorithms
 */

namespace dynamic_programming {
  /*
   * @namespace word_break
   * @brief Functions for [Word Break]
   */
  namespace word_break {
    /*
     * @brief Function that checks if the string is passed in param is present and the unordered_set passed
     *
     * @param str the string to be searched
     * @param strSet unordered set of string, that is to be looked into
     * @returns 'true' if str is present in strSet
     * @returns 'false' if str is not present in strSet
     */
    bool exists(const std::string &str,
                const std::unordered_set<std::string> &strSet) {
      return strSet.find(str) != strSet.end();
    }
   
    /*
     * @brief Function that checks if the string passed in the param can be
     * segmented from position 'pos', and then correctly go on to segment the
     * rest of the string correctly as well to reach a solution
     *
     * @param s the complete string to be segmented
     * @param strSet unordered set of string, that is to be used at the end of the refrence dictionary
     * @param pos the index value at which we will segment the string and test if correctly segmented
     * @param dp the vector to memoize solution for each position
     * @return 'true' if a value solution/segmentation is possible by segmentation
     * @return 'false' otherwise
     */
    bool check(const std::string &s, 
               const std::unordered_set<std::string> &strSet,
               int pos,
               std::vector<int> *dp){
      if (pos == s.length()) {
        // If we have reached till the end of the string, means we 
        // have segmeted throughout correctly hence we have a solution, thus return true.
        return true;
      }
      if (dp->at(pos) != INT_MAX) {
        // if dp[pos] is not INT_MAX, means we must have a saved solution for the position pos
        // then return if the solution at pos is true or not
        return dp->at(pos) == 1;
      }
      std::string wordTillNow = ""; // string to save the prefixes of word till different positions

      for (int i = pos; i < s.length(); i++) {
        // Loop starting pos to end, to check valid set of segmentations if any
        wordTillNow += std::string(1, s[i]);
        
        // if the prefix till current position is present in the dictionary
        // and the remaining substring can also be segmented legally, then
        // set solution at position pos in the memor, and return true
        if (exists(wordTillNow, strSet) and check(s, strSet, i + 1, dp)) {
          dp->at(pos) = 1;
          return true;
        }
      }
      // if function has still not returned, then there must be no legal segmentation
      // possible after segmenting at pos
      dp->at(pos) = 0;
      return false;
   }
   /*
    * @brief Function that checks if the string passed in param can be segmented
    * into the strings present in the vector.
    * In orther words, it checks if any permutation of strings in
    * the vector can be concatenated to form the final string.
    *
    * @param s the complete string to be segmented
    * @param wordDict a vector of words to be used as dictionary to look into
    * @return 'true' if s can be formed by a combination of strings present in WordDict
    * @return 'false' otherwise
    */
   bool wordBreak(const std::string &s,
                  const std::vector<std::string> &wordDict) {
     // unordered set to store words in the dictionary for constant time
     // search
     std::unordered_set<std::string> strSet;
     for (const auto &s : wordDict) {
       strSet.insert(s);
     }
     // a vector to be used for memoization, whose value at index i will
     // tell if the string s can be segmented (correctly) at position i.
     // Initializing it with INT_MAX (which will denoted no solutiion)
     std::vector<int> dp(s.length(), INT_MAX);
     
     // calling check method with position = 0, to check from left
     // from where can be start segmenting the complete string in correct manner
     return check(s, strSet, 0, &dp);
   }
 }
}

static void test(){
  const std::string s = "applepenapple";
  const std::vector<std::string> wordDict = {"apple", "pen"};
  assert(dynamic_programming::word_break::wordBreak(s, wordDict));

  std::cout << dynamic_programming::word_break::wordBreak(s, wordDict) << std::endl;
  std::cout << "Test implementation passed" << std::endl;
}

int main(){
  test();
  const std::string s = "applepenapple";
  const std::vector<std::string> wordDict = {"apple", "pen"};

  std::cout << dynamic_programming::word_break::wordBreak(s, wordDict) << std::endl;
}
