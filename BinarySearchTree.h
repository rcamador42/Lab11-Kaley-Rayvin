//**************************************************
//   KALEY WHITE
//   AND
//   RAYVIN CARL AMADOR
//   
//   APRIL 6, 2017
//   CSC 2111 LAB 11: BST & TREE SORT
//   SPRING 2017
//   DR. DAVID BROWN
//
//   TABS = 5 SPACES
//**************************************************
#if !defined (BINARYSEARCHTREE_H)
#define BINARYSEARCHTREE_H

#include "BinaryTreeIterator.h"
#include "TreeNode.h"
#include "Text.h"
using CSC2110::String;
#include "Line.h"
#include "Drawable.h"
#include "wx/wx.h"


template < class T >
class BinarySearchTree : public Drawable
{

     private:
          TreeNode<T>* root;
          int sze;
          void destroyItem(TreeNode<T>* tNode);
          void destroy();

          TreeNode<T>* insertItem(TreeNode<T>* tNode, T* item);
          TreeNode<T>* removeItem(TreeNode<T>* tNode, String* sk);
          TreeNode<T>* removeNode(TreeNode<T>* tNode);
          TreeNode<T>* removeLeftMost(TreeNode<T>* tNode);
          T* findLeftMost(TreeNode<T>* tNode);

          TreeNode<T>* getRootNode();
          void setRootNode(TreeNode<T>* tNode);
          int getHeight(TreeNode<T>* tNode);
          bool isBalanced(TreeNode<T>* tNode);

          int (*compare_items) (T* item_1, T* item_2);
          int (*compare_keys) (String* key, T* item);

          void drawRec(TreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr);

     public:
          BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
          ~BinarySearchTree();

          bool isEmpty();
          void makeEmpty();

          T* retrieve(String* search_keys);
          void insert(T* item);
          void remove(String* search_keys);

          BinaryTreeIterator<T>* iterator();
          T* getRootItem();
          int getHeight();
          bool isBalanced();

          T** toArray();
          static T** treeSort(T** items, int num_itemss, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

          void draw(wxDC& dc, int width, int height);
          void mouseClicked(int x, int y);
};

// THIS CHECKS IF
template < class T >
void BinarySearchTree<T>::remove(String* sk)
{
     //DO THIS

     //******************************************
     //   (START) ADD OWN CODE FROM HERE
     //******************************************

     //-------------------
     // PASS THE ROOT AND 
     // THE ITEM THAT WE 
     // WANT TO REMOVE
     //-------------------
     root = removeItem(root, sk);

     removeNode(root);
     sze--; // NEED THIS RIGHT???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     
     //******************************************
     //   (END) TO HERE
     //******************************************
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeItem(TreeNode<T>* tNode, String* sk)
{
     //DO THIS

     //******************************************
     //   (START) ADD OWN CODE FROM HERE
     //******************************************

     // NEED THIS????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     // CHECK IF tNode IS NULL FIRST
     if(tNode == NULL)
     {
          return NULL;
     }
     

     T* itemData = tNode->getItem();
     // DO WE ALSO NEED TO GET THE sk
     int compareValue = (*compare_keys)(sk, itemData);
     //------------------------
     // sk = CD Title 1
     // itemData = CD Title 2
     //------------------------

     if(compareValue == 0)
     {
          //------------------------
          // compareValue IS 0 IF
          // sk and itemData are 
          // equal
          //------------------------

      return tNode;
          //------------------------
          // JUST RETURN tNode 
          // BECAUSE IT'S THE SAME
          //------------------------ 
     }
     else if(compareValue < 0)
     {
          //--------------------------
          // compareValue IS < 0 IF
          // OF sk COMES BEFORE
          // itemData
          //--------------------------
      TreeNode<T>* subtree = removeItem(tNode->getLeft(), sk);
          tNode = tNode->setLeft(subtree);
     }
     else // THIS IS if(compareValue > 0)
     {
          //--------------------------
          // compareValue IS > 0 IF
          // itemData COMES BEFORE sk
          //--------------------------
      TreeNode<T>* subtree = removeItem(tNode->getRight(), sk);
          tNode = tNode->setRight(subtree);
     }

     // PASS BACK TO REMOVE FUNCTION, INTO THE ROOT VARIABLE
     return tNode;

     //******************************************
     //   (END) TO HERE
     //******************************************
}

// IF YOU ARE ON A LEAF NODE, CALL THIS FUNCTION
template < class T >
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* tNode)
{
     if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
     {
          delete tNode;
          return NULL;
     }
     else if (tNode->getLeft() == NULL)
     {
          TreeNode<T>* temp = tNode->getRight();
          delete tNode;
          return temp;
     }
     else if (tNode->getRight() == NULL)
     {
          TreeNode<T>* temp = tNode->getLeft();
          delete tNode;
          return temp;
     }
     else 
     {
          //DO THIS

          //******************************************
          //   (START) ADD OWN CODE FROM HERE
          //******************************************

          //------------------------------------------------
          // THIS IS THE HARD CASE WHERE THE tNode HAS
          // 2 KIDS. NEED TO FIND THE IN ORDER SUCCESSOR
          //------------------------------------------------
          //
          // STEPS
          //------------------------------------------------
          // 1. GET THE DATA FORM THE IN ORDER SUCCESSOR
          // 2. OVERWRITE WHAT I AM REPLACING (tNode) 
          //    WITH THE IN ORDER SUCCESSOR
          // 3. REMOVE THE NODE WITH THE IN ORDER SUCCESSOR
          //------------------------------------------------

          //-------------------
          // DOES NOT NEED TO
          // BE RECURSIVE, IT
          // CAN JUST LOOP
          // BECAUSE I DON'T
          // CARE ABOUT THE
          // MIDDLE PARTS
          //
          // left_most IS THE
          // IN ORDER SUCC
          //-------------------
          T* left_most = findLeftMost(tNode->getRight()); 

          //-------------------
          // NOW I HAVE TO SAVE
          // THAT DATA.
          // OVERWRITE THE
          // ORIGINAL 
          // ROOT (tNode)
          //-------------------
          tNode->setItem(left_most);

          //-------------------
          // GO BACK DOWN TO
          // THE IN ORDER 
          // SUCCESSOR
          // AND REMOVE.
          //
          // I ALSO HAVE TO
          // WORRY ABOUT
          // CHANGING LINKS
          //-------------------
          TreeNode<T>* subtree = removeLeftMost(tNode->getRight());
          tNode->setRight(subtree);

          return tNode;

          //******************************************
          //   (END) TO HERE
          //******************************************
     }
}

template < class T >
T* BinarySearchTree<T>::findLeftMost(TreeNode<T>* tNode)
{
     //DO THIS (use a while loop)

     //******************************************
     //   (START) ADD OWN CODE FROM HERE
     //******************************************

     //-------------------
     // NO NEED FOR
     // RECURSION BECAUSE
     // THE MIDDLE PARTS
     // DO NOT MATTER
     // 
     // THIS WHILE LOOP
     // IS JUST GONNA KEEP
     // GOING DOWN, CHECK 
     // IF IT'S NOT A NULL,
     // AND REPEAT UNTIL
     // IT FINALLY FINDS A
     // NULL AND GETS OUT
     // OF THE WHILE LOOP
     //-------------------
     while(tNode->getLeft() != NULL)
     {
          tNode = tNode->getLeft();
     }

     //-------------------
     // WHEN WE GET OUT OF
     // THE WHILE LOOP,
     // DO NOT RETURN THE
     // NODE. JUST RETURN
     // THE DATA AT THAT
     // NODE
     //-------------------
     return tNode->getItem();

     //******************************************
     //   (END) TO HERE
     //******************************************
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeLeftMost(TreeNode<T>* tNode)
{
     //DO THIS (recursion)

     //******************************************
     //   (START) ADD OWN CODE FROM HERE
     //******************************************

     //-------------------
     // BASE CASE
     //-------------------
     if(tNode->getLeft() == NULL)
     {
          TreeNode<T>* right = tNode->getRight();
          delete tNode;

          //-------------------
          // RETURN RIGHT
          // BECAUSE I'M AT
          // THE END OF MY
          // LEFT, I HAVE NO
          // MORE LEFTS TO GO
          // TO. SO ALL I CARE
          // ABOUT IS WHAT'S 
          // TO MY RIGHT
          //-------------------
          return right;
     }
     else
     {
          //-------------------
          // HARD PART
          //-------------------
          // HAVE TO RESET
          // LINKS BUT ALWAYS
          // ON THE SAME SIDE.
          //
          // ALWAYS GONNA BE
          // ON THE LEFT
          //-------------------
          TreeNode<T>* subtree = removeLeftMost(tNode->getLeft());
          tNode->setLeft(subtree); // THIS IS WHAT RESETS THE LINKS

          return tNode;
     }


     //******************************************
     //   (END) TO HERE
     //******************************************
}

template < class T >
T** BinarySearchTree<T>::toArray()
{
     //DO THIS
     //------------------------
     // WRITE THIS METHOD TO
     // TO RETURN AN ARRAY
     // CONTAINING THE 
     // CONTENTS OF THE
     // BINARY SEARCH TREE
     // IN SORTED ORDER
     //------------------------

     //******************************************
     //   (START) ADD OWN CODE FROM HERE
     //******************************************

     //------------------------
     // CREATE A NEW ARRAY
     //------------------------
     T** sorted_array = new T*[sze];

     BinaryTreeIterator<T>* iter = BinarySearchTree::iterator();

     //------------------------
     // SETS IT IN INORDER
     // TRAVERSAL
     //------------------------
     iter->setInorder();

     //------------------------
     // COUNTER VARIABLE
     //------------------------
     int i = 0;

     //------------------------
     // IN ORDER TRAVERSAL
     //------------------------
     while(iter->hasNext())
     {
          T* item = iter->next();
          sorted_array[i] = item;
          i++;
     }

     delete iter;
     return sorted_array;

     //******************************************
     //   (END) TO HERE
     //******************************************
}

template < class T >
T** BinarySearchTree<T>::treeSort(T** items, int num_itemss, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
     //------------------------
     // ASSUMING I ALREADY
     // HAVE A BST,
     // TREE SORT IS THE
     // EASIEST
     //------------------------
     // DO AN IN ORDER
     // TRAVERSAL
     //------------------------
     // 1. CEATE A BST
     // 2. PUT UNSORTED
     //    ITEMS INTO TREE
     // 3. DO IN ORDER
     //    TRAVERSAL. AS
     //    THE ITEMS COME
     //    OUT, PUT THEM
     //    BACK IN THE 
     //    ARRAY, OVERWRITING
     //    THE UNSORTED ITEMS
     //------------------------

     //DO THIS

     //******************************************
     //   (START) ADD OWN CODE FROM HERE
     //******************************************

     //------------------------
     // CREATE A BINARY SEARCH
     // TREE AND GIVE IT THE
     // FUNCTION POINTERS SO 
     // KNOWS HOW TO COMPARE
     // THE ITEMS AND
     // DETERMINING WHETHER TO
     // PUT THEM ON THE LEFT
     // OR THE RIGHT
     //------------------------
     BinarySearchTree<T>* binary_search_tree = new BinarySearchTree<T>(comp_items, comp_keys);

     //------------------------
     // DIRECTLY PULL FROM THE
     // ORIGINAL UNSORTED
     // ARRAY AND INSERT THEM
     // TO THE TREE 
     //------------------------
     for(int i = 0; i < num_itemss; i++)
     {
          binary_search_tree->insert(items[i]);
     }

     /*
     T** sorted_array = binary_search_tree->toArray
     delete binary_search_tree;
     */
  
     return binary_search_tree->toArray();

     //******************************************
     //   (END) TO HERE
     //******************************************
}

template < class T >
int BinarySearchTree<T>::getHeight()
{
   return getHeight(getRootNode());
}

template < class T >
int BinarySearchTree<T>::getHeight(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       int left = getHeight(tNode->getLeft());
       int right = getHeight(tNode->getRight());

       if (left >= right)
       {
           return left + 1;
       }
       else
       {
          return right + 1;
       }
   }
}

template < class T >
bool BinarySearchTree<T>::isBalanced()
{
    bool bal = isBalanced(root);
    return bal;
}

template < class T >
bool BinarySearchTree<T>::isBalanced(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return true;
   }

   TreeNode<T>* left = tNode->getLeft();
   TreeNode<T>* right = tNode->getRight();

   bool left_bal = isBalanced(left);
   if (left_bal == false)
   {
      return false;
   }

   bool right_bal = isBalanced(right);
   if (right_bal == false)
   {
      return false;
   }

   int lh = getHeight(left);
   int rh = getHeight(right);
   if (abs(lh - rh) > 1)
   {
      return false;
   }

   return true;
}

template < class T >
BinarySearchTree<T>::BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   root = NULL;
   sze = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
BinarySearchTree<T>::~BinarySearchTree()
{
   destroy();
}

template < class T >
void BinarySearchTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinarySearchTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool BinarySearchTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
void BinarySearchTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::getRootNode()
{
   return root;
}

template < class T >
void BinarySearchTree<T>::setRootNode(TreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* BinarySearchTree<T>::getRootItem()
{
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
void BinarySearchTree<T>::insert(T* item)
{
   root = insertItem(root, item);
}

template < class T >
T* BinarySearchTree<T>::retrieve(String* sk)
{
   TreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if (comp == 0)
      {
         //no duplicate search keys allowed, so do nothing
         return node_items;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }

   return NULL; //item is not in the tree
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::insertItem(TreeNode<T>* tNode, T* item)
{
   TreeNode<T>* subtree;
   if (tNode == NULL)
   { 
      sze++;
      return new TreeNode<T>(item);
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_items) (item, node_items);

   if (comp == 0)
   {
      //no duplicate search keys allowed, so do nothing
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
   }
   
   return tNode;
}

template < class T >
BinaryTreeIterator<T>* BinarySearchTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}

template < class T >
void BinarySearchTree<T>::draw(wxDC& dc, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void BinarySearchTree<T>::drawRec(TreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
void BinarySearchTree<T>::mouseClicked(int x, int y) {}
#endif
