/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    Daniel Carr, Jarom Anderson, Arlo Jolly
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:
   //
   // Construct
   //

   // Default Constructor

   Node() : pNext(nullptr), pPrev(nullptr) {}
   // Copy Constructor
   Node(const T& data) : pNext(nullptr), pPrev(nullptr), data(data) {}

   Node(T&& data) : pNext(nullptr), pPrev(nullptr), data(std::move(data)) {}


   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource)
{
   if (!pSource)
      return nullptr;

   // Create the head of the new list
   Node<T>* pDestination = new Node<T>(pSource->data);
   Node<T>* pCurrent = pDestination;

   // Use a standard for loop to copy the rest of the list
   for (const Node<T>* pSrcCurrent = pSource->pNext; pSrcCurrent; pSrcCurrent = pSrcCurrent->pNext)
      pCurrent = insert(pCurrent, pSrcCurrent->data, true);

   return pDestination;
}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
   // pSrc <- pSource
   // pDes <- pDestination
   // WHILE pSrc != NULL AND pDes != NULL
   //     pDes.data <- pSrc.data
   //     pDes <- pDes.pNext
   //     pSrc <- pSrc.pNext

   // IF pSrc != NULL
   //     pDes <- pDesPrevious
   //
   //     WHILE pSrc != NULL
   //         pDes <- insert(pDes, pSrc.data, TRUE)
   //         IF pDestination = NULL
   //             pDestination <- pDes
   //         pSrc <- pSrc.pNext

   // IF pSrc = NULL AND pDes != NULL
   //     setToNull <- FALSE
   //     IF pDes.pPrev != NULL
   //         pDes.pPrev.pNext <- NULL
   //     ELSE
   //         setToNull <- TRUE
   //
   //     freeData(pDes)
   //
   //     IF setToNull
   //         pDestination <- NULL

   const Node<T> * pSrc = pSource;
         Node<T> * pDes = pDestination;
         Node<T> * pDesPrevious = nullptr;

   while (pSrc && pDes)
   {
      pDes->data = pSrc->data;
      pDesPrevious = pDes;
      pDes = pDes->pNext;
      pSrc = pSrc->pNext;
   }

   bool setToNull = false;

   if (!pSrc && pDes) // pSource is smaller than pDestination
   {
      // Node<T> * pEnd = pDes;

      // while (pDes->pNext) // move pDes to the end of the list.
      // {
      //    pDes = pDes->pNext; // move pDes forward 1 node
      // }

      // while (pDes != pEnd) {
      //    delete pDes->pNext;
      //    pDes = pDes->pPrev;
      // }

      if (pDes->pPrev)
      {
         pDes->pPrev->pNext = nullptr;
      }
      else
      {
         setToNull = true;
      }

      clear(pDes);

      if (setToNull)
      {
         pDestination = nullptr;
      }
   }

   if (pSrc)
   {
      pDes = pDesPrevious;

      while (pSrc)
      {
         pDes = insert(pDes, pSrc->data, true);
         if (!pDestination)
         {
            pDestination = pDes;
         }

         pSrc = pSrc->pNext;
      }
   }



}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{

}

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node <T> * remove(const Node <T> * pRemove)
{

   return new Node<T>;
}


/**********************************************
 * INSERT
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node <T> * insert(Node <T> * pCurrent,
                  const T & t,
                  bool after = false)
{
   Node<T>* newNode = new Node<T>(t);

   if (pCurrent)
   {
      if (after)
      {
         newNode->pNext = pCurrent->pNext;
         newNode->pPrev = pCurrent;
         if (pCurrent->pNext)
            pCurrent->pNext->pPrev = newNode;
         pCurrent->pNext = newNode;
      }
      else
      {
         newNode->pPrev = pCurrent->pPrev;
         newNode->pNext = pCurrent;
         if (pCurrent->pPrev)
            pCurrent->pPrev->pNext = newNode;
         pCurrent->pPrev = newNode;
      }
   }

   return newNode;
}

/******************************************************
 * SIZE
 * Find the size an unsorted linked list.
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : number of nodes
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
   return 99;
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   return out;
}

/*****************************************************
 * FREE DATA
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{

}
