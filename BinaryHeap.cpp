#include "BinaryHeap.h"
#include <iostream>
BinaryHeap::BinaryHeap()
{
    // TODO: or not
    theSize = 0;
}

bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    for(int i=1; i<theSize+1; i++)
    {
        if(elements[i].uniqueId == uniqueId) return false;
    }
   
    if(HeapSize() == 0) elements.resize(1);
    elements[0].weight = weight; // initialize sentinel
    elements[0].uniqueId = uniqueId;
    
    if((theSize + 1) == ((int) elements.size()))
    {
        elements.resize(elements.size()*2 + 1);
    }
    
    //Percolate up
    int hole = ++theSize ;
    for( ; weight < elements[hole/2].weight ; hole /= 2)
    {
        elements[hole] = elements[hole/2];
    }
    elements[hole].uniqueId = uniqueId;
    elements[hole].weight = weight;
    
    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if(theSize == 0) return false;
   
    HeapElement tmp = elements[1];
    elements[1] = elements[theSize];
    theSize--;
    bubbleDown(1);
    outUniqueId=tmp.uniqueId;
    outWeight = tmp.weight;
    
    return true;
}

void BinaryHeap::bubbleDown(int hole)
{
    int child;
    HeapElement tmp = elements[hole];
    
    for( ; hole*2 <= theSize; hole = child) {
        child = hole * 2;
        if(child != theSize && elements[child + 1].weight < elements[child].weight)
            child++;
        if(elements[child].weight < tmp.weight)
            elements[hole] = elements[child];
        else
            break;
    }
    elements[hole] = tmp;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    //if there is no such item return false
    bool result = false;
    int valInd;
    for(int i=1; i<theSize+1; i++)
    {
        if(elements[i].uniqueId == uniqueId) 
        {
            result = true;
            valInd = i; 
            break;
        }
    }
    if(!result) return result;
    
    elements[valInd].weight = newWeight;
    
    if(valInd != 1 && elements[valInd].weight < elements[valInd/2].weight)
    {
        bubbleUp(valInd);
    }
    
    else
    {
        if((valInd*2 <= theSize && elements[valInd].weight > elements[valInd*2].weight) || (valInd*2+1 <= theSize && elements[valInd].weight > elements[valInd*2+1].weight))
        {
            bubbleDown(valInd);
        }
    }
    
    return true;
}

void BinaryHeap::bubbleUp(int hole)
{
    int parent;
    HeapElement tmp = elements[hole];
    
    for( ; hole/2 > 0 && tmp.weight < elements[hole/2].weight; hole = parent)
    {
        parent = hole/2;
        elements[hole] = elements[parent];
    }
    elements[hole] = tmp;
}
int BinaryHeap::HeapSize() const
{
    // TODO:
    return theSize;
}