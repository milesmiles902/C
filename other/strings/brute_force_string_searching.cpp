/*
 * @file .cpp
 * @brief String pattern search
 */

#include <iostream>
#ifdef _MSC_VER
#include <string>
#else
#include <cstring>
#endif
#include <vector>

namespace string_search{
  /*
   * Find a pattern in a string by comparing the pattern to every substring.
   * @param text Any string that might contain the pattern.
   * @param pattern String that we are searching for
   * @return Index where the pattern starts in the text
   * @return -1 if the pattern was not found
   */
  int brute_force(const std::string &text, const std::string &pattern){
    size_t pat_l = pattern.length();
    size_t txt_l = text.length();
    int index = -1;
    if (pat_l <= txt_l){
      for (size_t i = 0; i < txt_l - pat_l + 1; i++){
        std::string s = text.substr(i,pat_l);
        if (s==pattern){
          index = i;
          break;
        }
      }
    }
    return index;
  }
}

const std::vector<std::vector<std::string>> test_set = {
  {"a", "aa", "-1"}, {"a","a","0"}};

int main(){
  for (const auto &i : test_set){
    int output = string_search::brute_force(i[0],i[1]);
    if (std::to_string(output) == i[2]){
      std::cout << "success\n";
    } else {
      std::cout << "failure\n";
    }
  }
  return 0;
}
