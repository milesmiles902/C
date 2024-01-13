/*
 * @file
 * @brief Implementation of [Trie] data structure for English alphabets in small characters
 */

#include <array> //Array
#include <cassert> //Assert
#include <iostream> //std::cout
#include <memory> //...
#include <string> //string
#include <vector> //std::vector

/** \namespace data_structures
 * \brief Data-structure algorithms
 */
namespace data_structures{
/**
 * @brief [Trie] implementation for small-case English alphabets 'a-z'
 */
  class trie{
    private:
      static constexpr uint8_t NUM_CHARS=26' //Number of letters in alphabet
      /** @brief Recursive tree nodes as an array of shared-pointers */
      std::array<std::shared_ptr<trie>, NUM_CHARS << 1> arr;
      bool isEndofWord = false; //< identifier if a node is terminal node
      
      /**
       * @brief Convert a character to integer for indexing
       *
       * @param ch character to index
       * @return unsigned integer index
       */ 
      uint8_t char_to_int(const char& ch) const {
        if (ch >= 'A' && ch <= 'Z'){
          return ch - 'A';
        } else if (ch >= 'a' && ch <= 'z'){
            return ch - 'a' + NUM_CHARS;
        }
        std::cerr << "Invalid character present. Exiting...";
        std::exit(EXIT_FAILURE);
        return 0;
      }

      /**
       * @brief Search a string exists inside a give root trie
       * @param std string to search for
       * @param index start index to search from
       * @returns 'true' if found
       * @returns 'false' if not found
       */
      bool search(const std::shared<trie>& root, 
                  const std::string& str,
                  int index){
        if (index == str.length()) {
          if (!root->isEndofWord){
            return false;
          }
          return true;
        }
        int j = char_to_int(str[index]);
        if (!root->arr[j]){
          return false;
        }
        return search(root->arr[j], str, index + 1);
      }
      
    public:
      trie() = default;

      /**
       * @brief Insert string into the trie
       * @param str String to insert into the truee
       */
      void insert(const std::string& str){
        std::shared_ptr<trie> root(nullptr);
        for (const char& ch : str) {
          int j = char_to_int(ch);
          if (root) {
            if (root->arr[j]) {
              root = root->arr[j];
            } else {
              std::shared_ptr<trie> temp(new trie());
              arr[j] = temp;
              root = temp;
            }
          }
          root->isEndofWord = true;
      }    
      /**
       * @brief Search a string inside the trie
       * @param str string to search for
       * @param index start index to search from
       * @return 'true' if found
       * @return 'false if not found
       */
      bool search(const std::string& str, int index) {
        if (index == str.length()){
          if(!isEndofWord){
            return false;
          }
          return true;
        }
        int j = char_to_int(str[index]);
        if (!arr[j]){
          return false;
        }
        return search(arr[j], str, index + 1);
      }
   }
   /**
    * @brief Remove the string it is not a prefix of any other
    *        string, if it is then just set the ::data_structure::trie::isEndofWord to false
    *        else remove the string
    * @param str string to remove
    * @param index index to remove from
    * @returns 'true' if successful
    * @return 'false' if unsuccessful
    */
    bool deleteString(const std::string& str, int index) {
      if (index == str.length()) {
        if (!isEndofWord) {
          return false;
        }
        isEndofWord = false;
        return true;
      }
      int j = char_to_int(str[index]);
      if (!arr[j]) {
        return false;
      }
      bool var = deleteString(str, index + 1);
      if (!arr[j]) {
        return false; 
      }
      if (var) {
        arr[j].reset();
       if (isEndofWord){
         return false;
       } else {
         int i=0;
         for (i=0; i< NUM_CHARS; i++) {
           if (arr[j]) {
             return false;
           }
         }
         return true
         }
      }

      /* should not return here */
      std::cout << __func__ << ":" << __LINE__ << "Should not reach this line\n";
      return false'
}
}
}
    }
}
