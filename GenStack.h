/* Nicole Chu
* 2290152
* nichu@chapman.edu
* 350-01
* Assignment #3
*/

/*
 * This is my stack template class GenStack. It contains the standard push, pop, and peek fucntions.
   It also contains functions that will inform the user if their stack is full or empty, a function
   that tells the user the size of the stack, and a void function that doubles the size of the stack
   if the stack becomes full but the user still has data to push onto it.
 */

#ifndef GENSTACK_H
#define GENSTACK_H

#include <iostream>

using namespace std;

template <typename T>
class GenStack
{
public:
  GenStack();
  GenStack(int maxSize);
  ~GenStack();

  void push(T d);
  void pop();
  T popReturn();
  T peek();

  bool isFull();
  bool isEmpty();
  int getSize();
  int getTop();
  void increaseSize();

private:
  int size;
  int top;
  T *myArray;
};

/*
 * The default constructor builds a stack of size 50.
 */
template <typename T>
GenStack<T>::GenStack()
{
  myArray = new T[50];
  size = 50;
  top = -1;
}

/*
 * This constructor takes an int argument called maxSize and builds a
   stack of size maxSize.
 */
template <typename T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize];
  size = maxSize;
  top = -1;
}

/*
 * The destructor deletes myArray to free up memory and returns a message to the user.
 */
template <typename T>
GenStack<T>::~GenStack()
{
  delete myArray;
  cout << "Stack destroyed" << endl;
}

/*
 * push
 * The push function allows the user to add data to their stack. If the stack is not yet
   full, their data (of any datatype) is added to the top of the stack and the class
   variable top is incremented. If the stack is full, the increaseSize function is called
   to double the size of the array-based stack.
 */
template<typename T>
void GenStack<T>::push(T d)
{
  if(isFull())
  {
    increaseSize();
  }
  if(!isFull())
      myArray[++top] = d;
}

/*
 * popReturn
 * The popReturn function will remove the item on the top of the stack and return its value
   to the user. If the stack is empty and there is nothing to be popped, an error
   message is returned.
 */
template <typename T>
T GenStack<T>::popReturn()
{
  if(!isEmpty())
  {
    return myArray[top--];
  }
  else
  {
    cout << "ERROR: Cannot pop. Stack is empty." << endl;
  }
}

/*
 * pop
 * The pop function will remove the item on the top of the stack without returning its value
   to the user. If the stack is empty and there is nothing to be popped, an error
   message is returned.
 */
template <typename T>
void GenStack<T>::pop()
{
  if(!isEmpty())
  {
    top--;
  }
  else
  {
    cout << "ERROR: Cannot pop. Stack is empty." << endl;
  }
}

/*
 * peek
 * The peek function returns to the user the item on top of the stack (without removing
   it from the stack).
 */
template <typename T>
T GenStack<T>::peek()
{
  return myArray[top];
}

/*
 * isFull
 * Returns a boolean to the user if the stack is full.
 */
template <typename T>
bool GenStack<T>::isFull()
{
  return (top == size-1);
}

/*
 * isEmpty
 * Returns a boolean to the user if the stack is empty.
 */
template <typename T>
bool GenStack<T>::isEmpty()
{
  return (top == -1);
}

/*
 * getSize
 * Returns the size of the stack.
 */
template <typename T>
int GenStack<T>::getSize()
{
  return size;
}

/*
 * getSize
 * Returns the size of the stack.
 */
template <typename T>
int GenStack<T>::getTop()
{
  return top;
}

/*
 * increaseSize
 * This function creates a new temporary array which is used as a copy of myArray.
   myArray is then deleted and re-declared to be of double its original size. The
   contents of temp are then put back into myArray and temp is deleted.
 */
template <typename T>
void GenStack<T>::increaseSize()
{
  T *temp = new T[size];

  for(int i = 0; i < size; i++)
  {
    temp[i] = myArray[i];
  }

  delete myArray;
  size = 2 * size;

  myArray = new T[size];

  for(int i = 0; i < size/2; i++)
  {
    myArray[i] = temp[i];
  }

  delete temp;
}

#endif
