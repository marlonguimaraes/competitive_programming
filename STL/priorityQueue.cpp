#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

struct myClass {
    int a;
    pair<int, int> ii;

    myClass() {}
    myClass(int _a, pair<int, int> _ii) {
        a = _a;
        ii = _ii;
    }

    bool operator<(const myClass &example) const {
        if(a == example.a) {
            return ii < example.ii;
        }
        return a < example.a;
    }
    void printClass() {
        printf("[a] = %d\n", a);
        printf("ii = (%d, %d)\n", ii.first, ii.second);
    }
};

struct compareMyClass {
    bool operator()(const myClass &lhs, const myClass &rhs) const {
        if(lhs.a == rhs.a) {
            return lhs.ii > rhs.ii;
        }
        return lhs.a > rhs.a;
    }
};


/* Priority Queue

    template <class T, class Container = vector<T>,
              class Compare = less<typename Container::value_type> > class priority_queue;

              T = class template (type)

              Container = which container are going to be used internally by the priority queue;

              Compare is a binary predicate that compare two objects of type T and must return bool;
              compare(a, b) must return true if b is considered to have more priority than a
              considering that .top() returns the element with the most priority level;

              By default, the predicate less<T> is used, which is equivalent of implementint the operator <
              If you don't want to use operator < you have to pass an class or struct by parameter;
*/

int main() {

    vector<myClass> examples{ { 5, {14, 13}},
                              { 2, { 5, 3}},
                              {-8, {11, 17}}
                            };

    priority_queue< myClass, vector<myClass> > usingOperatorLess(examples.begin(), examples.end()); //useful constructor
    while(!usingOperatorLess.empty()) {
        auto next = usingOperatorLess.top();
        next.printClass();
        usingOperatorLess.pop();
        cout << "\n";
    }
    cout << "\n\n";

    priority_queue< myClass, vector<myClass>, compareMyClass> usingStruct(examples.begin(), examples.end()); //useful constructor
    while(!usingStruct.empty()) {
        auto next = usingStruct.top();
        next.printClass();
        usingStruct.pop();
        cout << "\n";
    }
    cout << "\n\n";
 
    return 0;
}
