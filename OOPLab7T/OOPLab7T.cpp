#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>
template <typename T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <>
const char* getMin<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) < 0) ? a : b;
}

template <>
const char* getMax<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) > 0) ? a : b;
}

void task1_7() {
    std::cout << "\nTask 1.7: Min/Max template functions\n";

    int a = 3, b = 7;
    std::cout << "\n[int] a=" << a << ", b=" << b;
    std::cout << "\n  min = " << getMin(a, b);
    std::cout << "\n  max = " << getMax(a, b);

    double x = 3.14, y = 2.71;
    std::cout << "\n\n[double] x=" << x << ", y=" << y;
    std::cout << "\n  min = " << getMin(x, y);
    std::cout << "\n  max = " << getMax(x, y);

    char c1 = 'Z', c2 = 'A';
    std::cout << "\n\n[char] c1='" << c1 << "', c2='" << c2 << "'";
    std::cout << "\n  min = " << getMin(c1, c2);
    std::cout << "\n  max = " << getMax(c1, c2);

    const char* s1 = "apple";
    const char* s2 = "banana";
    std::cout << "\n\n[char*] s1=\"" << s1 << "\", s2=\"" << s2 << "\"";
    std::cout << "\n  min (lex) = " << getMin(s1, s2);
    std::cout << "\n  max (lex) = " << getMax(s1, s2);

    std::cout << "\n";
}
template <typename T>
void shellSort(T arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

template <>
void shellSort<const char*>(const char* arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            const char* temp = arr[i];
            int j = i;
            while (j >= gap && strcmp(arr[j - gap], temp) > 0) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

template <typename T>
void printArray(const std::string& label, T arr[], int n) {
    std::cout << label;
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << (i < n - 1 ? ", " : "\n");
}

template <>
void printArray<const char*>(const std::string& label, const char* arr[], int n) {
    std::cout << label;
    for (int i = 0; i < n; i++)
        std::cout << "\"" << arr[i] << "\"" << (i < n - 1 ? ", " : "\n");
}

void task2_2() {
    std::cout << "\nTask 2.2: Shell Sort template\n";

    int iArr[] = { 45, 12, 3, 99, 27, 8, 61 };
    int iN = sizeof(iArr) / sizeof(iArr[0]);
    printArray("\n[int]    before: ", iArr, iN);
    shellSort(iArr, iN);
    printArray("         after:  ", iArr, iN);

    double dArr[] = { 3.14, 1.41, 2.71, 0.57, 1.73 };
    int dN = sizeof(dArr) / sizeof(dArr[0]);
    printArray("\n[double] before: ", dArr, dN);
    shellSort(dArr, dN);
    printArray("         after:  ", dArr, dN);

    char cArr[] = { 'f', 'a', 'z', 'm', 'b', 'q' };
    int cN = sizeof(cArr) / sizeof(cArr[0]);
    printArray("\n[char]   before: ", cArr, cN);
    shellSort(cArr, cN);
    printArray("         after:  ", cArr, cN);

    const char* sArr[] = { "banana", "apple", "mango", "cherry", "avocado" };
    int sN = sizeof(sArr) / sizeof(sArr[0]);
    printArray("\n[char*]  before: ", sArr, sN);
    shellSort(sArr, sN);
    printArray("         after:  ", sArr, sN);

    std::cout << "\n";
}

namespace task3 {

    template <typename T>
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    template <typename T>
    class LinkedList {
    private:
        Node<T>* head;
        int size;

    public:
        LinkedList() : head(nullptr), size(0) {}

        LinkedList(const LinkedList& other) : head(nullptr), size(0) {
            Node<T>* cur = other.head;
            while (cur) { pushBack(cur->data); cur = cur->next; }
        }

        LinkedList& operator=(const LinkedList& other) {
            if (this != &other) {
                clear();
                Node<T>* cur = other.head;
                while (cur) { pushBack(cur->data); cur = cur->next; }
            }
            return *this;
        }

        ~LinkedList() { clear(); }

        void pushFront(const T& val) {
            Node<T>* node = new Node<T>(val);
            node->next = head;
            head = node;
            size++;
        }

        void pushBack(const T& val) {
            Node<T>* node = new Node<T>(val);
            if (!head) { head = node; }
            else {
                Node<T>* cur = head;
                while (cur->next) cur = cur->next;
                cur->next = node;
            }
            size++;
        }

        void insertAt(int index, const T& val) {
            if (index < 0 || index > size)
                throw std::out_of_range("Index out of range");
            if (index == 0) { pushFront(val); return; }
            Node<T>* cur = head;
            for (int i = 0; i < index - 1; i++) cur = cur->next;
            Node<T>* node = new Node<T>(val);
            node->next = cur->next;
            cur->next = node;
            size++;
        }

        void popFront() {
            if (!head) throw std::underflow_error("List is empty");
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
            size--;
        }

        void popBack() {
            if (!head) throw std::underflow_error("List is empty");
            if (!head->next) { delete head; head = nullptr; size--; return; }
            Node<T>* cur = head;
            while (cur->next->next) cur = cur->next;
            delete cur->next;
            cur->next = nullptr;
            size--;
        }

        void removeAt(int index) {
            if (index < 0 || index >= size)
                throw std::out_of_range("Index out of range");
            if (index == 0) { popFront(); return; }
            Node<T>* cur = head;
            for (int i = 0; i < index - 1; i++) cur = cur->next;
            Node<T>* tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
            size--;
        }

        void removeValue(const T& val) {
            if (!head) return;
            if (head->data == val) { popFront(); return; }
            Node<T>* cur = head;
            while (cur->next && cur->next->data != val)
                cur = cur->next;
            if (cur->next) {
                Node<T>* tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
                size--;
            }
        }

        T& operator[](int index) {
            if (index < 0 || index >= size)
                throw std::out_of_range("Index out of range");
            Node<T>* cur = head;
            for (int i = 0; i < index; i++) cur = cur->next;
            return cur->data;
        }

        T& front() {
            if (!head) throw std::underflow_error("List is empty");
            return head->data;
        }

        T& back() {
            if (!head) throw std::underflow_error("List is empty");
            Node<T>* cur = head;
            while (cur->next) cur = cur->next;
            return cur->data;
        }

        int find(const T& val) const {
            Node<T>* cur = head;
            int idx = 0;
            while (cur) {
                if (cur->data == val) return idx;
                cur = cur->next;
                idx++;
            }
            return -1;
        }

        void reverse() {
            Node<T>* prev = nullptr;
            Node<T>* cur = head;
            while (cur) {
                Node<T>* next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
            }
            head = prev;
        }

        void clear() { while (head) popFront(); }

        int  getSize() const { return size; }
        bool isEmpty() const { return size == 0; }

        void print() const {
            Node<T>* cur = head;
            std::cout << "[ ";
            while (cur) {
                std::cout << cur->data;
                if (cur->next) std::cout << " -> ";
                cur = cur->next;
            }
            std::cout << " ]\n";
        }
    };

}

void task3_7() {
    std::cout << "\nTask 3.7: Parameterized Singly Linked List\n";

    std::cout << "\n[int list]\n";
    task3::LinkedList<int> li;
    li.pushBack(10); li.pushBack(20); li.pushBack(30);
    li.pushFront(5); li.insertAt(2, 15);
    std::cout << "After pushBack(10,20,30), pushFront(5), insertAt(2,15):\n  ";
    li.print();

    li.popFront();
    std::cout << "After popFront:  "; li.print();

    li.popBack();
    std::cout << "After popBack:   "; li.print();

    li.removeValue(15);
    std::cout << "After remove(15):"; li.print();

    std::cout << "find(20) = index " << li.find(20) << "\n";
    std::cout << "front=" << li.front() << "  back=" << li.back() << "\n";

    li.reverse();
    std::cout << "After reverse:   "; li.print();

    std::cout << "\n[double list]\n";
    task3::LinkedList<double> ld;
    ld.pushBack(1.1); ld.pushBack(2.2); ld.pushBack(3.3);
    std::cout << "List: "; ld.print();
    std::cout << "Size: " << ld.getSize() << "\n";

    std::cout << "\n[char list]\n";
    task3::LinkedList<char> lc;
    for (char ch : {'C', '+', '+', '!'}) lc.pushBack(ch);
    std::cout << "List: "; lc.print();

    std::cout << "\n[string list]\n";
    task3::LinkedList<std::string> ls;
    ls.pushBack("one"); ls.pushBack("two"); ls.pushBack("three");
    ls.insertAt(1, "ONE.FIVE");
    std::cout << "List: "; ls.print();
    ls.removeAt(1);
    std::cout << "After removeAt(1): "; ls.print();

    std::cout << "\n";
}

namespace task4 {

    template <typename T>
    struct Node {
        T     data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    template <typename T>
    class ListIterator {
    private:
        Node<T>* current;

    public:
        explicit ListIterator(Node<T>* node) : current(node) {}

        T& operator*() {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return current->data;
        }

        T* operator->() {
            if (!current) throw std::runtime_error("Null iterator");
            return &current->data;
        }

        ListIterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ListIterator operator+(int n) const {
            ListIterator tmp = *this;
            for (int i = 0; i < n && tmp.current; i++) ++tmp;
            return tmp;
        }

        bool operator==(const ListIterator& other) const { return current == other.current; }
        bool operator!=(const ListIterator& other) const { return current != other.current; }
        bool isValid() const { return current != nullptr; }
        Node<T>* ptr() const { return current; }
    };

    template <typename T>
    class LinkedList {
    private:
        Node<T>* head;
        int      size;

    public:
        LinkedList() : head(nullptr), size(0) {}

        LinkedList(const LinkedList& other) : head(nullptr), size(0) {
            for (auto it = other.begin(); it != other.end(); ++it)
                pushBack(*it);
        }

        LinkedList& operator=(const LinkedList& other) {
            if (this != &other) {
                clear();
                for (auto it = other.begin(); it != other.end(); ++it)
                    pushBack(*it);
            }
            return *this;
        }

        ~LinkedList() { clear(); }

        ListIterator<T> begin() const { return ListIterator<T>(head); }
        ListIterator<T> end()   const { return ListIterator<T>(nullptr); }

        void pushFront(const T& val) {
            Node<T>* node = new Node<T>(val);
            node->next = head;
            head = node;
            size++;
        }

        void pushBack(const T& val) {
            Node<T>* node = new Node<T>(val);
            if (!head) { head = node; }
            else {
                Node<T>* cur = head;
                while (cur->next) cur = cur->next;
                cur->next = node;
            }
            size++;
        }
        ListIterator<T> insertAfter(ListIterator<T> it, const T& val) {
            Node<T>* target = it.ptr();
            if (!target) { pushBack(val); return ListIterator<T>(head); }
            Node<T>* node = new Node<T>(val);
            node->next = target->next;
            target->next = node;
            size++;
            return ListIterator<T>(node);
        }

        void popFront() {
            if (!head) throw std::underflow_error("List is empty");
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
            size--;
        }
        ListIterator<T> removeAt(ListIterator<T> it) {
            Node<T>* target = it.ptr();
            if (!target) throw std::runtime_error("Invalid iterator");
            if (head == target) {
                head = head->next;
                delete target;
                size--;
                return ListIterator<T>(head);
            }
            Node<T>* cur = head;
            while (cur->next && cur->next != target) cur = cur->next;
            if (!cur->next) throw std::runtime_error("Element not found");
            cur->next = target->next;
            Node<T>* nextNode = target->next;
            delete target;
            size--;
            return ListIterator<T>(nextNode);
        }

        void clear() {
            while (head) popFront();
            size = 0;
        }

        ListIterator<T> find(const T& val) const {
            for (auto it = begin(); it != end(); ++it)
                if (*it == val) return it;
            return end();
        }

        int  getSize() const { return size; }
        bool isEmpty() const { return size == 0; }

        void print() const {
            std::cout << "[ ";
            for (auto it = begin(); it != end(); ++it) {
                std::cout << *it;
                if ((it + 1) != end()) std::cout << " -> ";
            }
            std::cout << " ]\n";
        }
    };

} 

void task4_2() {
    std::cout << "\nTask 4.2: Singly Linked List with Iterator\n";

    task4::LinkedList<int> list;
    for (int v : {10, 20, 30, 40, 50}) list.pushBack(v);

    std::cout << "\n[1] Initial list:\n  ";
    list.print();

    std::cout << "\n[2] Manual iterator walk (prefix ++):\n  ";
    for (auto it = list.begin(); it != list.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "\n[3] Postfix ++ (print then advance):\n  ";
    auto it = list.begin();
    while (it != list.end()) {
        auto old = it++;
        std::cout << *old << " ";
    }
    std::cout << "\n";

    std::cout << "\n[4] begin() + 2  =>  value = " << *(list.begin() + 2) << "\n";
    std::cout << "    begin() + 4  =>  value = " << *(list.begin() + 4) << "\n";

    std::cout << "\n[5] find(30):\n";
    auto found = list.find(30);
    if (found != list.end())
        std::cout << "  Found: " << *found << "\n";

    std::cout << "    find(99):\n";
    auto notFound = list.find(99);
    std::cout << "  " << (notFound == list.end() ? "Not found\n" : "Found\n");

    std::cout << "\n[6] insertAfter(find(20), 25):\n";
    list.insertAfter(list.find(20), 25);
    std::cout << "  "; list.print();

    std::cout << "\n[7] removeAt(find(25)):\n";
    list.removeAt(list.find(25));
    std::cout << "  "; list.print();

    std::cout << "\n[8] Range-based for loop:\n  ";
    for (const auto& val : list)
        std::cout << val << " ";
    std::cout << "\n";

    std::cout << "\n[9] Multiply each element by 2 via iterator:\n";
    for (auto it2 = list.begin(); it2 != list.end(); ++it2)
        *it2 *= 2;
    std::cout << "  "; list.print();

    std::cout << "\n[10] Copy constructor:\n";
    task4::LinkedList<int> copy = list;
    std::cout << "  Original: "; list.print();
    std::cout << "  Copy:     "; copy.print();

    std::cout << "\n";
}
int main() {
    int choice = 0;
    do {
        std::cout << "\n--------------------------------------\n";
        std::cout << "-        MENU                          -\n";
        std::cout << "+--------------------------------------+\n";
        std::cout << "-  1. Task 1.7                         -\n";
        std::cout << "-  2. Task 2.2                         -\n";
        std::cout << "-  3. Task 3.7                         -\n";
        std::cout << "-  4. Task 4.2                         -\n";
        std::cout << "-  0. Exit                             -\n";
        std::cout << "+--------------------------------------+\n";
        std::cout << "  Choose: ";
        std::cin >> choice;

        switch (choice) {
        case 1: task1_7(); break;
        case 2: task2_2(); break;
        case 3: task3_7(); break;
        case 4: task4_2(); break;
        case 0: std::cout << "\n Go away\n"; break;
        default: std::cout << "\nUnknown option, try again.\n"; break;
        }
    } while (choice != 0);

    return 0;
}