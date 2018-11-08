#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
    // For the mandatory running times below:
    //
    // n is the number of elements in the MinPriorityQueue.
    //
    // Assume that the operations of unordered_map are O(1) time
    // (they are average case, but not worst-case).

public:
    // Creates an empty MinPriorityQueue
    MinPriorityQueue()
    {
        // TODO
    }

    // Returns the number of elements in the MinPriorityQueue.
    //
    // Must run in O(1) time.
    int size()
    {
        // TODO
        return static_cast<int>(H.size());
    }

    // Pushes a new value x with priority p
    // into the MinPriorityQueue.
    //
    // Must run in O(log(n)) time.
    void push(T x, int p)
    {
        // TODO
        // PUSH
        H.push_back(make_pair(x,p));
        I[x] = static_cast<int>(H.size()-1);
        //BUBBLE UP
        bubble_up(static_cast<int>(H.size()-1));
    }

    // Returns the value at the front of the MinPriorityQueue.
    // Undefined behavior if the MinPriorityQueue is empty.
    //
    // Must run in O(1) time.
    T front()
    {
        return H.begin()->first;
    }

    // Removes the value at the front of the MinPriorityQueue.
    // Undefined behavior if the MinPriorityQueue is empty.
    //
    // Must run in O(log(n)) time.
    void pop()
    {
        // TODO
        if(H.size() == 0)
        {
            return;
        }

        if(H.size() == 1)
        {
            I.erase(H[0].first);
            H.pop_back();
            return;
        }
        else
        {
        //swaps the front and the back

        I.erase(H[0].first);

        //swap(I.at(H[0].first), I.at(H[H.size()-1].first));
        swap(H[0], H[H.size()-1]);

        //deletes the last element
        H.pop_back();

        //bubbles down
        //bubbleDown(I.at(H.begin()->first));
        bubbleDown(0);
        }
}

    // If x is in the MinPriorityQueue
    // with current priority at least new_p,
    // then changes the priority of x to new_p.
    // Undefined behavior otherwise.
    //
    // Must run in O(log(n)) time.
    void decrease_key(T x, int new_p)
    {
        if(I.find(x) == I.end())
        {


        }
        else
        {

            //find the key
            int index = I[x];

            //set new key
            H[index].second = new_p;

            //if parent or child violation
            if(parent_violation(index))
            {
                bubble_up(index);
            }
            else if(child_violation(index))
            {
                bubbleDown(index);

            }
        }




    }

private:
    // You don't need any other instance variables,
    // but you can add some if you want to.
    vector< pair<T, int> > H; // The heap.
    unordered_map<T, int> I;  // Maps values to their indices in H.

    //FIX WHILE INSERTING
    void bubble_up(int p)
    {

        while(parent_violation(p))
        {
            swap(H[p], H[parent(p)]);
            swap(I[H[p].first], I[H[parent(p)].first]);
            p = parent(p);
        }
    }

    //fix the pop
    void bubbleDown(int p) {
        while(child_violation(p))
        {
                if(rchild(p) == H.size())
                {
                    swap(H[p], H[lchild(p)]);
                    p = lchild(p);
                }
                else
                {
                    if (H[lchild(p)].second < H[rchild(p)].second)
                    {
                        swap(H[p], H[lchild(p)]);
                        swap(I[H[p].first], I[H[lchild(p)].first]);
                        p = lchild(p);
                    }
                }
                else
                {
                    swap(H[p], H[rchild(p)]);
                    swap(I[H[p].first], I[H[rchild(p)].first]);
                    p = rchild(p);
                }
            }
        }
        I[H[p].first] = p;
    }

    //check if there is a parent violation
    bool parent_violation(int i)
    {

        if(H[i].second < H[parent(i)].second) //&& H.size() > 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool child_violation(int index)
    {
        if(lchild(index) >= H.size()) {
            // no child
            return false;
        }
        else if(rchild(index) == H.size()){
            //  one child
            if(H[lchild(index)].second < H[index].second)
                return true;
            else
                return false;
        }
        else {
            //  two children
            int small = min(H[lchild(index)].second, H[rchild(index)].second);
            if (small < H[index].second)
                return true;
            else
                return false;
        }

    }

    //return the parent
    int parent(int i)
    {
        return (i-1)/2;
    }

    //return the left child
    int lchild(int i)
    {
        return (i*2)+1;
    }

    //return right child
    int rchild(int i)
    {
        return lchild(i)+1;
    }
};

#endif
