#include <iostream>
#include <cstdlib>
#include <windows.h> // Necessary for using Windows-specific functions and types
#include <limits>  // Required for std::numeric_limits

using namespace std;

struct TreeNode 
{
    int value;   // The value stored in the node
    TreeNode* left;  // Pointer to the left child
    TreeNode* right; // Pointer to the right child

    
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // Constructor initializes a node with a given value
};

class BST 
{
    public:
        TreeNode* root;   // Root pointer of the tree

   
    BST() : root(nullptr) {}  // Constructor initializes an empty BST

    
    void insert(int val) // Function to insert a value into the BST
    {
        root = insertRec(root, val);
    }

   
    TreeNode* insertRec(TreeNode* node, int val)  // Recursive helper function to insert a value into the BST
    {
        if (node == nullptr) 
        {
            return new TreeNode(val); // Create a new node if the spot is found
        }
        if (val < node->value) 
        {
            node->left = insertRec(node->left, val); // Recur on the left subtree
        }
        else if (val > node->value) 
        {
            node->right = insertRec(node->right, val); // Recur on the right subtree
        }
        return node;
    }

    
    bool search(int val) // Function to search for a value in the BST
    {
        return searchRec(root, val);
    }

   
    bool searchRec(TreeNode* node, int val)  // Recursive helper function to search for a value in the BST
     {
        if (node == nullptr) return false; // Base case: not found
        if (node->value == val) return true; // Value found
        return val < node->value ? searchRec(node->left, val) : searchRec(node->right, val);
    }

    
    TreeNode* deleteNode(TreeNode* root, int val) // Function to delete a node from the BST
    {
        if (root == nullptr) return root; // If the tree is empty
        if (val < root->value) 
        { 
            root->left = deleteNode(root->left, val); // Value is less than root's value, go left
        }
        else if (val > root->value) 
        { 
            root->right = deleteNode(root->right, val); // Value is greater than root's value, go right
        }
         else 
         {
            if (root->left == nullptr) // Node with only one child or no child
             {
                TreeNode* temp = root->right;
                delete root; // Delete the node
                return temp;
            } 
            else if (root->right == nullptr) 
            {
                TreeNode* temp = root->left;
                delete root; // Delete the node
                return temp;
            }
            
            TreeNode* temp = minValueNode(root->right); // Node with two children: Get the inorder successor
            root->value = temp->value; // Copy the inorder successor's content to this node
            root->right = deleteNode(root->right, temp->value); // Delete the inorder successor
        }
        return root;
    }

    
    TreeNode* minValueNode(TreeNode* node) // Helper function to find the minimum value node in the BST
    {
        TreeNode* current = node;
        while (current && current->left != nullptr) 
        {
            current = current->left; // Move to the leftmost leaf
        }
        return current;
    }

    
    void inorder() // Functions to perform inorder, preorder, and postorder traversal
     {
        inorderRec(root);
        cout << endl;
    }

    void inorderRec(TreeNode* node) 
    {
        if (node != nullptr) 
        {
            inorderRec(node->left); // Visit left subtree
            cout << node->value << " "; // Visit root
            inorderRec(node->right); // Visit right subtree
        }
    }

    void preorder() 
    {
        preorderRec(root);
        cout << endl;
    }

    void preorderRec(TreeNode* node) 
    {
        if (node != nullptr) 
        {
            cout << node->value << " "; // Visit root
            preorderRec(node->left); // Visit left subtree
            preorderRec(node->right); // Visit right subtree
        }
    }

    void postorder() 
    {
        postorderRec(root);
        cout << endl;
    }

    void postorderRec(TreeNode* node) 
    {
        if (node != nullptr)
         {
            postorderRec(node->left); // Visit left subtree
            postorderRec(node->right); // Visit right subtree
            cout << node->value << " "; // Visit root
        }
    }
};

void clearScreen() // Function to clear the screen based on operating system 
{
    #ifdef _WIN32
        system("cls");  // Clear the console on Windows
    #else
        system("clear");  // Clear the console on Unix-like systems
    #endif
}

void setcolor(int txtcolor,int bgcolor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Get a handle to the console
    SetConsoleTextAttribute(hConsole,(bgcolor << 4) | txtcolor);  // Set the console text and background color
}

int main() {
    setcolor(95,0);
    BST bst;
    int value, n;

    cout << "***************************Binary Search Tree***************************" << endl;
    cout << "Enter number of values to insert: ";
    cin >> n;

    for (int i = 0; i < n; i++)
     {
        cout << "Enter value to insert: ";
        cin >> value;
        bst.insert(value);
    }

    int option, traversalOption;
    bool running = true;

    while (running) 
    {
        clearScreen();
        cout << "Select an operation:\n";
        cout << "1. Traversal\n";
        cout << "2. Search for a Value\n";
        cout << "3. Delete a Value\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) 
        {
            case 1:
                clearScreen();
                cout << "Select Traversal Type:\n";
                cout << "1. Inorder\n";
                cout << "2. Preorder\n";
                cout << "3. Postorder\n";
                cout << "Enter your choice for traversal: ";
                cin >> traversalOption;
                switch (traversalOption) 
                {
                    case 1:
                        cout << "Inorder traversal: ";
                        bst.inorder();
                        break;
                    case 2:
                        cout << "Preorder traversal: ";
                        bst.preorder();
                        break;
                    case 3:
                        cout << "Postorder traversal: ";
                        bst.postorder();
                        break;
                    default:
                        cout << "Invalid traversal option." << endl;
                }
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (bst.search(value))
                 {
                    cout << "Value found." << endl;
                 }
                else 
                {
                    cout << "Value not found." << endl;
                }
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                bst.root = bst.deleteNode(bst.root, value);
                cout << "Value deleted." << endl;
                break;
            case 4:
                running = false;
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
        if (running)
         {
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the buffer to handle the next input correctly
            cin.get();  // Wait for user to press Enter
        }
    }
    return 0;
}
