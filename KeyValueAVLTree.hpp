//=================================================================================================================
/**
 *  Example of implementation of a class that defines an AVL tree for key-value pairs.
 */
 //=================================================================================================================

#ifndef KEY_VALUE_AVL_TREE_HPP
#define KEY_VALUE_AVL_TREE_HPP

// Includes
#include <stdexcept>    // For std::out_of_range
#include <iostream>     // For std::cout
#include <vector>       // For std::vector

/**
 *  Structure that defines a node of a key-value AVL tree.
 * 
 *  @tparam Key     The type of key stored in the node.
 *  @tparam Value   The type of value stored in the node.
 */
template <typename Key, typename Value>
struct KeyValueAVLNode {

    Key key;            /**< The key of the node. */

    Value value;        /**< The value of the node. */

    int height;         /**< The height of the node. */

    KeyValueAVLNode* left;      /**< Pointer to the child node on the left side. */

    KeyValueAVLNode* right;     /**< Pointer to the child node on the right side. */


    /**
     *  Constructs a new KeyValueAVLNode object with the given value.
     *
     *  @param[in]  k   The key to be stored in the node.
     *  @param[in]  v   The value to be stored in the node.
     */
    KeyValueAVLNode(const Key& k, const Value& v)
    {
        key = k;
        value = v;
        height = 1;
        left = nullptr;
        right = nullptr;
    }

    /**
     *  Constructs a new KeyValueAVLNode object by moving the given value.
     *
     *  @param[in]  k   The key to be stored in the node.
     *  @param[in]  v   The value to be stored in the node.
     */
    KeyValueAVLNode(Key&& k, Value&& v)
    {
        key = std::move(k);
        value = std::move(v);
        left = nullptr;
        right = nullptr;
    }
};

/**
 *  Class that defines an AVL tree.
 *
 *  @tparam Key     The type of key stored in the node.
 *  @tparam Value   The type of value stored in the node.
 */
template <typename Key, typename Value>
class KeyValueAVLTree {

public:

    /**
     *  Constructs an empty search tree.
     */
    KeyValueAVLTree() = default;

    /**
     *  Constructs an AVL tree with the given root node.
     *
     *  @param[in]  r   Pointer to the root node of the AVL tree.
     */
    KeyValueAVLTree(KeyValueAVLNode<Key, Value>* r) 
    {
        root_ = r;
    }

    /**
     *  Class destructor.
     */
    ~KeyValueAVLTree() 
    {
        clear();
    }

    /**
     *  Returns the root node of the AVL tree.
     *
     *  @return Pointer to the root node of the AVL tree.
     */
    const KeyValueAVLNode<Key, Value>* root() const 
    {
        return root_;
    }

    /**
     *  Returns the number of elements in the AVL tree.
     *
     *  @return The number of elements in the AVL tree.
     */
    unsigned long long size() const
    {
        return size(root_);
    }

    /**
     *  Returns the node with the minimum key in the AVL tree.
     *
     *  @return The node with the minimum key in the AVL tree.
     */
    const KeyValueAVLNode<Key, Value>* find_min() const
    {
        return find_min(root_);
    }

    /**
     *  Returns the node with the maximum key in the AVL tree.
     *
     *  @return The node with the maximum key in the AVL tree.
     */
    const KeyValueAVLNode<Key, Value>* find_max() const
    {
        return find_max(root_);
    }

    /**
     *  Clears the AVL tree.
     */
    void clear() 
    {
        clear(root_);
        root_ = nullptr;
    }

    /**
     *  Finds the node with the specified key.
     *
     *  @param[in]  key The key to search for.
     * 
     *  @return Pointer to the node with the specified key, or nullptr if not found.
     */
    KeyValueAVLNode<Key, Value>* find(const Key& key) const {

    return find(root_, key);

    }

    /**
     *  Inserts a new node with the given key-value pair into the AVL tree.
     *
     *  @param[in]  key     The key of the element to insert.
     *  @param[in]  value   The value of the element to insert.
     */
    void insert(const Key& key, const Value& value) 
    {
        root_ = insert(root_, key, value);
    }

    /**
     *  Erases the node with the specified key from the AVL tree.
     *
     *  @param[in]  key The key to delete.
     */
    void erase(const Key& key)
    {
        root_ = erase(root_, key);
    }

    /**
     *  Prints the contents of the AVL tree in preorder.
     */
    void print_preorder() const
    {
        print_preorder(root_);
    }

    /**
     *  Prints the contents of the AVL tree in inorder.
     */
    void print_inorder() const
    {
        print_inorder(root_);
    }

    /**
     *  Prints the contents of the AVL tree in postorder.
     */
    void print_postorder() const
    {
        print_postorder(root_);
    }

    /**
     *  Prints the AVL tree in a graphical way.
     */
    void print_tree() const
    {
        print_tree(root_);
    }

    /**
     *  Returns a vector with the elements of the tree in preorder.
     * 
     *  @return A vector with the elements of the tree in preorder.
     */
    std::vector<std::pair<Key,Value>> preorder_traversal() const
    {
        std::vector<std::pair<Key, Value>> res;
        preorder_traversal(root_, res);
        return res;
    }

    /**
     *  Returns a vector with the elements of the tree in inorder.
     * 
     *  @return A vector with the elements of the tree in inorder.
     */
    std::vector<std::pair<Key, Value>> inorder_traversal() const
    {
        std::vector<std::pair<Key, Value>> res;
        inorder_traversal(root_, res);
        return res;
    }

    /**
     *  Returns a vector with the elements of the tree in preorder.
     * 
     *  @return A vector with the elements of the tree in postorder.
     */
    std::vector<std::pair<Key, Value>> postorder_traversal() const
    {
        std::vector<std::pair<Key, Value>> res;
        postorder_traversal(root_, res);
        return res;
    }      

    KeyValueAVLNode<Key, Value>* findClosest(const Key& key) const {
    KeyValueAVLNode<Key, Value>* current = root_;
    KeyValueAVLNode<Key, Value>* closest = nullptr;

    while (current) {
        // Actualiza el nodo más cercano si es el primero encontrado o si está más cerca
        if (!closest || abs(key.compare(current->key)) < abs(key.compare(closest->key))) {
            closest = current;
        }

        // Decide hacia dónde moverse en el árbol
        if (key < current->key) {
            current = current->left;  // Mover a la izquierda
        } else if (key > current->key) {
            current = current->right; // Mover a la derecha
        } else {
            break; // Nodo exacto encontrado
        }
    }

    return closest;
    }
 

private:

    /**
     *  Returns the number of elements in the AVL tree from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start counting.
     * 
     *  @return The number of elements in the AVL tree from the given node.
     */
    unsigned long long size(KeyValueAVLNode<Key, Value>* node) const
    {
        if (node == nullptr)
            return 0;

        return 1 + size(node->left) + size(node->right);
    }

    /**
     *  Clears the AVL tree starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start clearing.
     */
    void clear(KeyValueAVLNode<Key, Value>* node) 
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);
        delete node;        
    }    

    /**
     *  Calculates the height of a node.
     *
     *  @param[in] node Pointer to the node to calculate the height.
     * 
     *  @return The height of the node.
     */
    int height(KeyValueAVLNode<Key, Value>* node) const
    {
        return node ? node->height : 0;
    }

    /**
     *  Updates the height of a node.
     *
     *  @param[in] node Pointer to the node to update.
     */
    void update_height(KeyValueAVLNode<Key, Value>* node)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    /**
     *  Calculates the balance factor of a node.
     *
     *  @param[in] node Pointer to the node whose balance factor is to be calculated.
     * 
     *  @return The balance factor of the node.
     */
    int calculate_balance_factor(KeyValueAVLNode<Key, Value>* node) const
    {
        return node ? height(node->right) - height(node->left) : 0;
    }

    /**
     *  Returns the node with the minimum key in the AVL tree
     *  starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start searching.
     *
     *  @return The node with the minimum key starting from the given node.
     */
    KeyValueAVLNode<Key, Value>* find_min(KeyValueAVLNode<Key, Value>* node) const
    {
        if (node == nullptr)
            throw std::out_of_range("The tree is empty.");

        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    /**
     *  Returns the node with the maximum key in the AVL tree
     *  starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start searching.
     *
     *  @return The node with the maximum key starting from the given node.
     */
    KeyValueAVLNode<Key, Value>* find_max(KeyValueAVLNode<Key, Value>* node) const
    {
        if (node == nullptr)
            throw std::out_of_range("The tree is empty.");

        while (node->right != nullptr)
            node = node->right;

        return node;
    }

    /**
     *  Finds the node with the specified key starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start searching.
     *  @param[in]  key   The value to search for.
     *
     *  @return Pointer to the node with the specified key, or nullptr if not found.
     */
    KeyValueAVLNode<Key, Value>* find(KeyValueAVLNode<Key, Value>* node, const Key& key) const
    {
        if ((node == nullptr) || (key == node->key))
            return node;
        else if (key < node->key)
            return find(node->left, key);
        else
            return find(node->right, key);
    }

    /**
     *  Inserts a new node with the given key-value pair into the AVL tree starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start inserting.
     *  @param[in]  key     The key to insert.
     *  @param[in]  value   The value of the key to insert.
     *
     *  @return Pointer to the new node.
     */
    KeyValueAVLNode<Key, Value>* insert(KeyValueAVLNode<Key, Value>* node, const Key& key, const Value& value)
    {
        if (node == nullptr)
            node = new KeyValueAVLNode<Key, Value>(key, value);
        else if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            return node;

        // Update height and balance the node
        update_height(node);
        return balance(node);
    }

    /**
     *  Erases the node with the specified value from the AVL tree starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start deleting.
     *  @param[in]  key     The key to delete.
     *
     *  @return Pointer to the new node in the position of node. This is needed to update the parent node.
     */
    KeyValueAVLNode<Key, Value>* erase(KeyValueAVLNode<Key, Value>* node, const Key& key)
    {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = erase(node->left, key);    // The key is in the left subtree
        }
        else if (key > node->key) {
            node->right = erase(node->right, key);  // The key is in the right subtree
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                // The node has one child or no children
                KeyValueAVLNode<Key, Value>* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                // The node has two children
                KeyValueAVLNode<Key, Value>* temp = find_max(node->left);
                node->key = temp->key;
                node->value = temp->value;
                node->left = erase(node->left, temp->key);
            }
        }

        // Update height and balance the node
        update_height(node);
        return balance(node);
    }

    /**
     *  Simple rotation to the left.
     *
     *  @param[in] node Pointer to the current node.
     *
     *  @return Pointer to the new root node after the rotation.
     */
    KeyValueAVLNode<Key, Value>* rotate_left(KeyValueAVLNode<Key, Value>* node)
    {
        KeyValueAVLNode<Key, Value>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        // Update heights
        update_height(node);
        update_height(newRoot);

        return newRoot;
    }

    /**
     * Simple rotation to the right.
     *
     * @param[in] node Pointer to the current node.
     *
     * @return Pointer to the new root node after the rotation.
     */
    KeyValueAVLNode<Key, Value>* rotate_right(KeyValueAVLNode<Key, Value>* node)
    {
        KeyValueAVLNode<Key, Value>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        // Update heights
        update_height(node);
        update_height(newRoot);

        return newRoot;
    }

    /**
     * Left-right double rotation.
     *
     * @param[in] node Pointer to the current node.
     *
     * @return Pointer to the new root node after the rotation.
     */
    KeyValueAVLNode<Key, Value>* rotate_left_right(KeyValueAVLNode<Key, Value>* node)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    /**
     * Right-left double rotation.
     *
     * @param[in] node Pointer to the current node.
     *
     * @return Pointer to the new root node after the rotation.
     */
    KeyValueAVLNode<Key, Value>* rotate_right_left(KeyValueAVLNode<Key, Value>* node)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    /**
     *  Balances the AVL tree starting from the given node.
     *
     *  @param[in] node Pointer to the node from which to start balancing.
     *
     *  @return Pointer to the new root node after balancing.
     */
    KeyValueAVLNode<Key, Value>* balance(KeyValueAVLNode<Key, Value>* node)
    {
        int bf = calculate_balance_factor(node);

        // Rotation to the left
        if (bf == 2) {
            if (calculate_balance_factor(node->right) >= 0)
                return rotate_left(node);
            else
                return rotate_right_left(node);
        }
        // Rotation to the right
        else if (bf == -2) {
            if (calculate_balance_factor(node->left) <= 0)
                return rotate_right(node);
            else
                return rotate_left_right(node);
        }

        return node;
    }

    /**
     *  Prints the contents of the AVL tree in preorder starting from the given node.
     * 
     *  @param[in]  node    Pointer to the node from which to start printing.
     */
    void print_preorder(KeyValueAVLNode<Key, Value>* node) const
    {
        if (node == nullptr)
            return;

        std::cout << "(" << node->key << ", " << node->value << ") ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    /**
     *  Prints the contents of the AVL tree in inorder starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start printing.
     */
    void print_inorder(KeyValueAVLNode<Key, Value>* node) const
    {
        if (node == nullptr)
            return;

        print_inorder(node->left);        
        std::cout << "(" << node->key << ", " << node->value << ") ";
        print_inorder(node->right);
    }

    /**
     *  Prints the contents of the AVL tree in postorder starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start printing.
     */
    void print_postorder(KeyValueAVLNode<Key, Value>* node) const
    {
        if (node == nullptr)
            return;

        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << "(" << node->key << ", " << node->value << ") ";
    }    

    /**
     *  Prints the AVL tree in a graphical way.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[in]  indent      The indentation string.
     *  @param[in]  isRight     Flag to indicate if the node is the right child of its parent.
     */
    void print_tree(KeyValueAVLNode<Key, Value>* node, std::string indent = "", bool isRight = true) const
    {
        if (node == nullptr)
            return;

        print_tree(node->right, indent + (isRight ? "        " : " |      "), true);
        std::cout << indent;
        if (isRight) {
            std::cout << " /";
        }
        else {
            std::cout << " \\";
        }
        std::cout << "----- ";
        std::cout << "(" << node->key << ", " << node->value << ")" << "(bf=" << calculate_balance_factor(node) << ")" << std::endl;
        print_tree(node->left, indent + (isRight ? " |      " : "        "), false);
    }

    /**
     *  Obtains the contents of the AVL tree in preorder starting from the given node.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[out] traversal   Vector to store the elements of the tree.
     */
    void preorder_traversal(KeyValueAVLNode<Key, Value>* node, std::vector<std::pair<Key, Value>>& traversal) const
    {
        if (node == nullptr)
            return;

        traversal.push_back(std::make_pair(node->key, node->value));
        preorder_traversal(node->left, traversal);
        preorder_traversal(node->right, traversal);
    }

    /**
     *  Obtains the contents of the AVL tree in inorder starting from the given node.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[out] traversal   Vector to store the elements of the tree.
     */
    void inorder_traversal(KeyValueAVLNode<Key, Value>* node, std::vector<std::pair<Key, Value>>& traversal) const
    {
        if (node == nullptr)
            return;

        inorder_traversal(node->left, traversal);
        traversal.push_back(std::make_pair(node->key, node->value));
        inorder_traversal(node->right, traversal);
    }

    /**
     *  Obtains the contents of the AVL tree in postorder starting from the given node.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[out] traversal   Vector to store the elements of the tree.
     */
    void postorder_traversal(KeyValueAVLNode<Key, Value>* node, std::vector<std::pair<Key, Value>>& traversal) const
    {
        if (node == nullptr)
            return;
        postorder_traversal(node->left, traversal);
        postorder_traversal(node->right, traversal);
        traversal.push_back(std::make_pair(node->key, node->value));
    }


    KeyValueAVLNode<Key, Value>* root_{ nullptr };    /**< Pointer to the root node of the AVL tree. */
};


#endif
//=================================================================================================================
//  END OF FILE
//=================================================================================================================