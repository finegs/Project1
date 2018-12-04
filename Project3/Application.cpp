#if 0
#include <iostream>
#include <utility>
#include <set>

using namespace std;

template<class _A, class _B, class _Compare = less<_A>>
class MMap : public set < pair<_A, _B>, _Compare >
{
public:
    MMap() : set< pair<_A, _B>, _Compare >() {};
    ~MMap() {};
};

template<typename InPair>
struct MMapComp {
    bool operator() (InPair a, InPair b) {
        if (a.first == b.first) return a.second > b.second;
        else return a.first < b.first;
    }
};

int main(int argc, char* argv[]) {

    MMap<char, int, MMapComp<pair<char, int>>> test;

    test.insert(make_pair('D', 1));
    test.insert(make_pair('D', 1));
    test.insert(make_pair('D', 1));
    test.insert(make_pair('D', 1));
    test.insert(make_pair('D', 1));
    test.insert(make_pair('D', 1));

    return 0;
}
#endif // 0

#if 0
#include <iostream>

using namespace std;

struct Rectangle {
public:
    int width, height;

public:
    Rectangle() {};
    Rectangle(int _x, int _y) : width(_x), height(_y) {};
    int area() { return width*height; }
    friend Rectangle duplicate(const Rectangle&);

#if 1
    friend istream& operator >> (istream& is, Rectangle& rect);
#endif // 0

    friend ostream& operator << (ostream& os, const Rectangle& rect);
};

Rectangle duplicate(const Rectangle& param) {
    Rectangle res;
    res.width = param.width;
    res.height = param.height;
    return res;
}

#if 1
istream& operator >> (istream& is, Rectangle& rect) {
    is >> rect.width >> rect.height;
    return is;
}
#endif // 0


ostream& operator<<(ostream& os, const Rectangle& rect) {
    os << "hash=" << &rect << ",width=" << rect.width << ",height=" << rect.height << std::endl;
    return os;
}

int main(int argc, char* argv[]) {
    Rectangle rect;

    cin >> rect;

    cout << rect;
}
#endif

#if 0
#include <iostream>

using namespace std;

template <class _T>
struct Node {
    _T data;
    Node* next;

    //static const char* (toStr)();
};

//const char* Node::toStr() {
//
//}

template <class _T>
class LinkedList {
private:
    int size;
    Node<_T>* head;
    Node<_T>* tail;
public:
    LinkedList() : size(0), head(NULL) {}

    void addFirst(_T d);
    void addLast(_T d);
    void display(ostream& os);
};

template<class _T>
void LinkedList<_T>::addFirst(_T d) {
    Node<_T> newElement = new Node<_T>();
    newElement->data = d;

    newElement->next = head;

    if (!head) last = newElement;

    head = newElement;

    size++;
}

template<class _T>
void LinkedList<_T>::addLast(_T d) {
    Node<_T> *newElement = new Node<_T>();
    newElement->data = d;

    if (tail) {
        tail = tail->next = newElement;
    }
    else {
        tail = head = newElement;
    }

    size++;
}

template<class _T>
void LinkedList<_T>::display(ostream& os) {
    os << "hashcode=" << this;
    os << ", size=" << size;
    os << ", data={";

    for (Node<_T>* n = head; n; n = n->next) {
        os << n->data << (n->next ? ", " : "");
    }
    os << "}";
}

int main(int argc, char* argv[]) {

    LinkedList<int> list;

    list.addLast(1);
    list.addLast(2);
    list.addLast(3);

    list.display(cout);

    cout << endl;

    return 0;
}


#endif // 1


#if 1
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <utility>

using namespace std;

stringstream ss(std::ios_base::ate | std::ios_base::in | std::ios_base::out);

struct A
{
    std::string s;
    int k;
    A() : s("test"), k(-1) {}
    A(const A& o) : s(o.s), k(o.k) 
    { 
        std::cout << "move failed@!!!\n";
    }
    A(A&& o) noexcept :
        //s(std::move(o.s)),
        s(o.s),
        k(std::exchange(o.k, 0)) {

        std::cout << "move constructor.\n";
    }

    A& operator=(const A& o) 
    {
        s = o.s;
        k = o.k;
        std::cout << "¡á¡á¡á copy assigned ¡á¡á¡á\n";
        return *this;
    }

    A& operator=(A&& o) 
    { 
        //s = std::move(o.s);
        s = o.s;
        k = std::exchange(o.k, -1);
        std::cout << "¡à¡à¡àmove assigned¡à¡à¡à\n";
        return *this; 
    }
};

A func(A a)
{
    //stringstream ss(std::ios_base::ate|std::ios_base::in|std::ios_base::out);

    ss.clear();
    ss.str("");

    ss << "aaaa";

    ss << "bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb "
        "bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb "
        "bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb "
        "bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb "
        "bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb bbbb ";
    a.s = ss.str();

    return a;
}

struct B : A
{
public:
    std::string s2;
    int n;
};

struct C : B
{
public:
    ~C() { }
};

struct D : C
{
public:
    D() { }
    ~D() { }
    D(D&&) = default;
};


std::vector<string> v;

void add() {
    string s;
    stringstream ss(ios_base::ate | ios_base::out | ios_base::in);

    ss << "aaa" << " " << "bbb";

    cout << &ss.str() << endl;
    cout << &ss.str() << endl;

    v.push_back(ss.str());
    v.push_back(ss.str());
}

void print() {

    for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
        cout << ' ' << *it;
    cout << std::endl;

    v.clear();
}

void run01() 
{
    for (int i = 0; i < 100000000; i++) {
        add();
        print();
        this_thread::sleep_for(chrono::milliseconds(250ms));
    }
}

void run02()
{
    for (int i = 0; i < 100000000; i++) 
    {
        std::cout << "Trying to move A\n";
        A a1;
        for (int j = 0; j < 1000000000; j++)
            a1 = func(A()); // return by value move-constructs the target from the function parameter
        std::cout << "Befoer move, a1.s = " << std::quoted(a1.s) << " a1.k = " << a1.k << '\n';
        A a2 = std::move(a1); // move-constructs from xvalue
        std::cout << "After move, a1.s = " << std::quoted(a1.s) << " a1.k = " << a1.k << '\n';

        std::cout << "Trying to move B\n";
        B b1;
        std::cout << "Before move, b1.s = " << std::quoted(b1.s) << "\n";
        B b2 = std::move(b1); // calls implicit move constructor
        std::cout << "After move, b1.s = " << std::quoted(b1.s) << "\n";

        std::cout << "Trying to move C\n";
        C c1;
        C c2 = std::move(c1); // calls copy constructor

        std::cout << "Trying to move D\n";
        D d1;
        D d2 = std::move(d1);

        this_thread::sleep_for(chrono::microseconds(1us));

    }
}


int main(int argc, char* argv[]) {

    //thread t1(run01);
    thread t2(run02);

    this_thread::sleep_for(chrono::minutes(20min));

    //t1.join();
    t2.join();


    return 0;
}

#endif
