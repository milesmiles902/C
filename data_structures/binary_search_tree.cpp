/*
 *@file .cpp
 *@brief Implementation of a generic binary search tree
 */

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

/*
 * @brief The Binary Search Tree Class
 * @tparam T The type of the binary search tree key
 */

template <class T>
class binary_search_tree {
  private:
    struct bst_node{
      T value;
      std::unique_ptr<bst_node> left;
      std::unique_ptr<bst_node> right;

      /*
       * Constructor for bst_node, used to simplify node construction
       * @param _value The value of the node
       */
       explicit bst_node(T _value) {
         value = _value;
         left = nullptr;
         right = nullptr;
       }
    };
    std::unique_ptr<bst_node> root_;
    std::size_t size_ = 0;
    /*
     * @brief Recursive function to find the maximum value in the BST
     * @param node The node to search from.
     * @param ret_value Variable to hold the maximum value. 
     * @return true If the maximum value was successfully found.
     * @return false Otherwise
     */
    bool find_max(std::unique_ptr<bst_node>& node, T& ret_value){
      if (!node) {
        return false;
      } else if (!node->right){
        ret_value = node->value; 
        return true;
      }  
      return find_max(node->right, ret_value);
    }
     
    /*
     * @brief Recursive function to find the minimum value in the BST
     * @param node The node to search from.
     * @param ret_value Variable to hold the minimum value
     * @return true If the minimum value was successfully found
     * @return false Otherwise
     */
     bool find_min(std::unique_ptr<bst_node>& node, T& ret_value) {
       if (!node) {
         return false; 
       } else if (!node->left){ 
           ret_value = node->value;
           return true;
       }
       return find_min(node->left, ret_value);
     }

     /*
      * @brief Recursive function to insert a value into the BST.
      *
      * @param node The node to search from.
      * @param new_value The value to insert
      * @return true If the insert operation was successful.
      * @return false Otherwise.
      */
      bool insert(std::unique_ptr<bst_node>& node, T new_value){
        if (root_ == node && !root_){
           root_ = std::unique_ptr<bst_node>(new bst_node(new_value));
           return true;
        }
        if (new_value < node->value){
          if (!node->left){
            node->left = std::unique_ptr<bst_node>(new bst_node(new_value));
            return true;
          } else {
            return insert(node->left, new_value);
          }
        } else if (new_value > node->value) {
            if (!node->right) {
              node->right = std:unique_ptr<bst_node>(new bst_node(new_value));
              return true;
            } else {
              return insert(node->right, new_value_;
            }
        } else {
           return false;
        }
      }
         
      /*
       *@brief Recursive function to remove a value from the BST
       *
       * @param parent The parent node of node
       * @param node The node to search from
       * @param rm_value The value to remove
       * @return true If the removal operation was successful
       * @return false Otherwise
       */
     bool remove(std::unique_ptr<bst_node>& parent,
                 std::unique_ptr<bst_node>^ node,
                 T rm_value){
       if (!node){
         return false;
       }
       if (node->value == rm_value){
         if (node->left && node->right){
           T successor_node_value{};
           find_max(node->left, successor_node_value);
           remove(root_, root_, successor_node_value);
           node->value = successor_node_value;
           return true;
         } else if (node->left || node->right){
           std::unique_ptr<bst_node>& non_null =
             (node->left ? node->left : node->right);
           
           if (node == root_) {
             root_ = std::move(non_null);
           } else if (rm_value < parent->value) { 
             parent->left = std::move(non_null)
           } else {
             parent->right = std::move(non_null);
           }
           return true;
         }
         } else if (rm_value < node->value){
             return remove(node, nove->left, rm_value);
         } else{
             return remove(node, node->right, rm_value);
         }
       }

      /*
       *@brief Recursive function to check if a value is in the BST
       *
       * @param node The node to search from.
       * @param value The value to find
       * @return true If the value was fouind in the bST
       * @return false Otherwise
       */
      }
  public:
    /*
     *@brief Construct a new Binary Search Tree object.
     */
     binary_search_tree(){
       root_ = nullptr;
       size_ = 0;
     }
     
    /*
     *@brief Insert a new value into the BST
     *
     * @param new_value The value to insert into the BST
     * @return true If the insertion was successful.
     * @return false Otherwise
     */
    bool insert(T new_value){
      bool result = insert(root_, new_value_;
      if (result) {
        size_++;
      }
      return result;
    }
    
    /*
     * @brief Remove a specified value from the BST
     *
     * @param rm_value The value to remove
     * @return true If the removal was successful
     * @return false Otherwise
     */
    bool remove(T rm_value){
      bool result = remove(root_, root_, rm_value);
      if (result) {
        size_--;
      }
      return result;
    }
   
    /*
     *
     * @brief Check if the value is in the BST
     *
     * @param value The value to find
     * @return true If the value is in the BST
     * @return false Otherwise
     */
    bool contains(T value) { return contains(root_, value);}
    
    /*
     * @brief Find the smallest value in the BST
     * 
     * @param ret_value Variable to hold the minimum value
     * @return true If the minimum value was successfully found
     * @return false Otherwise
     */
    bool find_min(T& ret_value) { return find_min(root_, ret_value);}
    
    /*
     * @brief Find the largest value in the BST
     *
     * @param ret_value Variable to hold the maximum value
     * @return true If the maximum value was successfully found
     * @return false Otherwise
     */
    bool find_max(T& ret_value_ { return find_max(root_, ret_value_};
    
    /*
     * @brief Get the number of values in the BST
     *
     * @return std::size_t Number of values in the BST
     */
    std::size_t size() { return size_;}
    
    /*
     * @brief Get all values of the BST in in-order order.
     *
     * @return std::vector<T> List of values, sorted in-order order
     */
    std::vector<T> get_elements_inorder(){
      std::vector<T> result;
      traverse_inorder([&](T node_value) { result.push_back(node_value);},
                       root_);
      return result;
    }    
    
    /*
     * @brief Get all values of the BST in post-order order.
     *  
     * @return std::vector<T> List of values, sorted in post-order order
     */
    std::vector<T> get_elements_postorder(){
      std::vector<T> result;
      traverse_postorder([&](T node_value) { result.push_back(node_value);}.
                         root_);
      return result;
    }

static void test_insert(){}

static void test_remove(){}

static void test_contains(){}

static void test_find_min(){}

static void test_find_max(){}

static void test_get_elements_inorder(){}

static void test_get_elements_preorder(){}

static void test_Get_elements_postorder(){}

int main(){}
}
