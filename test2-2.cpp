/*

CSE A section

DS mini project

Topic:
            Indexed Priority Queue with Implementation in c++
Team members:
            Navaneet R Rao - 1JT21CS064
            Ayush
            saksh
            Drushan
            Bushan
            Aruna


*/

#include <bits/stdc++.h>

using namespace std;

long long get_key[100], get_key_values[100], total_key, total_values, new_key[100], new_value[100];

template <class T1, class T2,
          class Comparator = less<T2>,
          class Hash = hash<T1>>

class indexed_priority_queue
{

    // Storing indices of values using key
    unordered_map<T1, long long int, Hash> m;

    // Container
    vector<pair<T1, T2>> v;

    // Size
    long long numberOfElement;

    // Creating a instance of Comparator class
    Comparator comp;

    // Max Capacity
    long long capacity = LLONG_MAX; // 64 bit has a maximum value of 9,223,372,036,854,775,807

    // Obtaining the index value from hash map
    long long int getValueIndex(T1 key)
    {
        if (m[key] == 0)
        {
            cout << "No Such Key Exist";
            return -1;
        }
        return v[m[key] - 1];
    }

    // heapify the container
    void heapify(vector<pair<T1, T2>> &v,
                 long long int heap_size,
                 long long index)
    {
        long long leftChild = 2 * index + 1,
                  rightChild = 2 * index + 2,
                  suitableNode = index;

        if (leftChild < heap_size &&
            comp(v[suitableNode].second,
                 v[leftChild].second))
        {
            suitableNode = leftChild;
        }

        if (rightChild < heap_size &&
            comp(v[suitableNode].second,
                 v[rightChild].second))
        {
            suitableNode = rightChild;
        }

        if (suitableNode != index)
        {

            // swap the value
            pair<T1, T2> temp = v[index];
            v[index] = v[suitableNode];
            v[suitableNode] = temp;

            // updating the map
            m[v[index].first] = index + 1;
            m[v[suitableNode].first] = suitableNode + 1;

            // heapify other affected nodes
            heapify(v, numberOfElement,
                    suitableNode);
        }
    }

public:
    indexed_priority_queue()
    {
        numberOfElement = 0;
        m.clear();
        v.clear();
    }

    void push(T1 key, T2 value)
    {
        if (numberOfElement == capacity)
        {
            cout << "Overflow";
            return;
        }
        if (m[key] != 0)
        {
            cout << "Element Already Exists";
            return;
        }

        // Adding element
        v.push_back(make_pair(key, value));
        numberOfElement++;
        m[key] = numberOfElement;

        long long index = numberOfElement - 1;

        // Comparing to parent node
        while (index != 0 &&
               comp(v[(index - 1) / 2].second,
                    v[index].second))
        {

            // swap the value
            pair<T1, T2> temp = v[index];
            v[index] = v[(index - 1) / 2];
            v[(index - 1) / 2] = temp;

            // updating the map
            m[v[index].first] = index + 1;
            m[v[(index - 1) / 2].first] = (index - 1) / 2 + 1;

            // updating index in map
            index = (index - 1) / 2;
        }
    }

    void pop()
    {
        if (::total_key == 0)
        {
            cout << "UnderFlow";
            return;
        }

        // Removing element
        v.erase(v.begin());
        numberOfElement--;
        heapify(v, numberOfElement, 0);
    }

    pair<T1, T2> top()
    {
        return v[0];
    }

    long long int size()
    {
        return numberOfElement;
    }

    bool empty()
    {
        return numberOfElement == 0;
    }

    void changeAtKey(T1 key, T2 value)
    {
        if (m[key] == 0)
        {
            cout << "No Such Key Exist";
            return;
        }
        long long index = m[key] - 1;
        v[index].second = value;

        // Comparing to child nodes
        heapify(v, numberOfElement, index);

        // Comparing to Parent Node
        while (index != 0 &&
               comp(v[(index - 1) / 2].second,
                    v[index].second))
        {

            // swap the value
            pair<T1, T2> temp = v[index];
            v[index] = v[(index - 1) / 2];
            v[(index - 1) / 2] = temp;

            // updating the map
            m[v[index].first] = index + 1;
            m[v[(index - 1) / 2].first] = (index - 1) / 2 + 1;

            // updating index in map
            index = (index - 1) / 2;
        }
    }
};

void display(indexed_priority_queue<int, int> IPQ)
{
    indexed_priority_queue<int, int> temp = IPQ;
    while (!IPQ.empty())
    {
        pair<int, int> tmp;
        tmp = IPQ.top();
        IPQ.pop();
        cout << "( " << tmp.first << ", " << tmp.second << " ) ";
    }
    cout << '\n';
}

void topAndSize(indexed_priority_queue<int, int> IPQ)
{
    cout << "IPQ: ";
    display(IPQ);
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
         << "Size: " << IPQ.size() << endl;
    cout << "Top: " << IPQ.top().first << ", " << IPQ.top().second << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
         << endl;
}
// Driver Code
int main()
{
    // First parameter is key datatype
    // and it should be hashable
    // Second parameter is value datatype comparator
    // function (by default it implements maxheap)
    indexed_priority_queue<int, int> IPQ;
    int choice;
    int total_dequeue, popCount = 0;
    int total_updates;
    do
    {
        printf("\n\n\n\n~~~~~~Menu~~~~~~ : ");
        printf("\n=>1.Add an element into the queue and Overflow  ");
        printf("\n=>2.pop an element from the queue and Underflow ");
        printf("\n=>3.Display ");
        printf("\n=>4.update the element in queue  ");
        printf("\n=>5.Exit");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            cout << "Enter the total number of members key in the queue: \n";
            cin >> ::total_key;

            cout << "Enter the total number of members key values in the queue: \n";
            cin >> ::total_values;

            if (::total_key != ::total_values)
            {
                cout << "ERROR :: The number of keys and there respected values are not equal!!";
            }

            cout << "First insert the keys in your order: \n";
            for (int i = 0; i < ::total_key; i++)
            {
                cin >> get_key[i];
            }

            cout << "Second insert the values of respective keys: \n";
            for (int i = 0; i < ::total_values; i++)
            {
                cin >> ::get_key_values[i];
            }

            cout << '\n';

            // Check if empty
            cout << "Checking if initially the IPQ is empty: \n";
            if (::total_key == 0 || ::total_values == 0)
            {
                cout << "IPQ is empty\n";
            }
            else
            {
                cout << "IPQ is not empty\n";
            }

            for (int i = 0; i < ::total_key; i++)
            {
                IPQ.push(::get_key[i], ::get_key_values[i]);
            }

            cout << '\n';
            break;
        case 2:

            cout << "Enter the total number of times pop operation should be done:" << endl;
            cin >> total_dequeue;

            while (popCount < total_dequeue)
            {
                cout << "\n Popping an element from IPQ: " << endl;
                display(IPQ);
                IPQ.pop();
                popCount++;
                cout << '\n';
            }
            break;
        case 3:
            topAndSize(IPQ);
            break;
        case 4:

            cout << "Enter the total number of key-values to be updated:" << endl;
            cin >> total_updates;

            cout << "Enter first the key value to be updated and second its new value:" << endl;
            for (int i = 0; i < total_updates; i++)
            {
                cin >> ::new_key[i] >> ::new_value[i];
            }

            for (int i = 0; i < total_updates; i++)
            {
                IPQ.changeAtKey(::new_key[i], ::new_value[i]);
            }
            break;
        case 5:
            exit(0);
        default:
            printf("\n Please enter valid choice ");
            break;
        }
    } while (choice != 5);

    return 0;
}