/*Amanda Ditmore
CS110C
3-20-2017*/

//function definitions for array-based queue class

#include "queue.h"

template<class ItemType>
Queue<ItemType>::Queue()
{
	max_size=50;
	front=0;
	back=0;
	arrayPtr = new ItemType[max_size+1];
}

template<class ItemType>
Queue<ItemType>::~Queue()
{
	delete [] arrayPtr;
}	

template<class ItemType>
bool Queue<ItemType>::enQ(ItemType x)
//returns true if item successfully added to queue
{
	if (front != (back+1) % (max_size+1))
	{	
		arrayPtr[back+1] = x;
		back++;
		return true;
	}
	else
		return false;
}
		
template<class ItemType>
bool Queue<ItemType>::deQ()
//returns true if item successfully removed from queue
{
	if(front != back)	
	{	
		front++;
		return true;
	}
	else
		return false;	
}

template<class ItemType>
ItemType Queue<ItemType>::peek()
//returns the item at the top of the queue
{
	return arrayPtr[front+1];
}

template class Queue<char>;

