
#include <iostream>
#include <vector>
using namespace std;

template<typename Type>

class LinkedList {

public:
	LinkedList() : size(0), head(nullptr), tail(nullptr) {}

	LinkedList(const vector<Type> &v) : size(v.size()), head(nullptr), tail(nullptr) {
						
		head = new node(v[0], nullptr);
		tail = head;

		node* jumper = this->head;

		for (size_t i = 1; i < size; i++) {

			jumper->next = new node(v[i]);
			jumper = jumper->next;
		}

		tail = jumper;
		
	}

	LinkedList(const LinkedList& other) {

		size = other.size;
		head = new node(other.head->value, nullptr);
		tail = head;

		node* jumper1 = this->head;
		node* jumper2 = other.head;

		for (size_t i = 1; i < size; i++) {

			jumper1->next = new node(jumper2->next->value);
			jumper1 = jumper1->next;
			jumper2 = jumper2->next;
		}

		tail = jumper1;
	}
	LinkedList& operator=(LinkedList& other) {

		swap(*this, other);
		return *this;
	}

	void push_back(const Type& new_element) {

		// push_back complexity O(1), because we know where the tail is
		if (size == 0) {
		
			head = new node(new_element);
			tail = head;

			size++;
			return;
		}
		
		tail->next = new node(new_element);
		tail = tail->next;

		size++;
	}

	void push_front(const Type& new_element) {

		// push_front complexity O(1), because we know where the head is
		node* second = head;
		head = new node(new_element, second);

		if (size++ == 0) tail = head; // if size was 0, tail is head (size is now 1)
	}

	void pop_front() {

		node* trash = head;

		if (size > 0) {
			head = head->next;
			if (size-- < 2) tail = head; // if size was 2 or less, tail is head (tail and head are nullptr if size was 1)
		}

		delete trash;
	}

	void pop_back() {

		node* trash = tail;

		if (size > 1) {
			
			tail = node_at_index(size - 2); // fix tail position with complexity O(n), price to pay so that push_back is O(1)
			tail->next = nullptr; // very important step
			size--;
		}
		else if (size == 1) {

			head = nullptr;
			tail = nullptr;
			size = 0;
		}

		delete trash; // trash could be nullptr, in that case nothing will happen
	}

	const bool remove(size_t index) {

		// removes element at given index with O(n) complexity
		if (index >= size) return false;

		if (index == size - 1) { pop_back(); return true; }
		if (index == 0) { pop_front(); return true; }


		// at this point we are removing from somewhere in the middle
		node* jumper = node_at_index(index - 1); // jump to the node just before the one to be removed	

		node* trash = jumper->next; // this node will be deleted
		jumper->next = trash->next; // removed node is now skipped

		delete trash;
		size--;

	}

	const size_t find(const Type& element) const {

		// returns index of given element with O(n) complexity
		node* jumper = head;
		for (size_t i = 0; i < size; i++) {
			
			if (jumper->value == element) return i;
			jumper = jumper->next;
		}
		return -1;

	}

	Type& operator[](size_t index) {

		if (index >= size) index = size - 1;
		return node_at_index(index)->value;
	}
	const Type operator[](size_t index) const {

		if (index >= size) index = size - 1;
		return node_at_index(index)->value;
	}

	const size_t length() const {
		return size;
	}

	ostream& toOstream(ostream& out) const {

		node* jumper = head;

		out << "[ ";
		for (size_t i = 0; i < size; i++) {

			out << jumper->value << " ";
			jumper = jumper->next;
		}
		out << "]";
		return out;
	}

	void display_info() const {

		node* jumper = head;

		cout << "Linked List: [ ";
		for (size_t i = 0; i < size; i++) {

			cout << "->(" << jumper->value << ") ";
			jumper = jumper->next;
		}
		cout << "]" << endl;

		if (size > 0) {
			cout << "Head Value: " << head->value << endl;
			cout << "Tail Value: " << tail->value << endl;
		}		
		cout << "Size: " << size << endl << endl;
	}

	~LinkedList() {

		while (head != nullptr) {

			// we would usually create a jumper not to lose the head
			// but since this is a destructor we can jump using the head
			node* trash = head;
			head = head->next;
			delete trash;
		}
	}



private:

	struct node {

		node(const Type& v, node* next = nullptr) : value(v), next(next) {}

		Type value;
		node* next;
	};

	node* node_at_index(const size_t& index) const { // returns the node at the given index (node at index 0 is the head)

		if (index<0 || index>=size) return nullptr;

		node* jumper = head;
		for (size_t i = 0; i < index; i++) {

			jumper = jumper->next;
		}
		return jumper;
	}

	size_t size;
	node* head;
	node* tail;

	friend void swap(LinkedList& l1, LinkedList& l2);

};

template<typename Type>
void swap(LinkedList<Type>& l1, LinkedList<Type>& l2) {

	using std::swap;
	swap(l1.size, l2.size);
	swap(l1.head, l2.head);
	swap(l1.tail, l2.tail);
}

template<typename Type>
ostream& operator<<(ostream& out, const LinkedList<Type>& l) {

	return l.toOstream(out);
}



int main() {

	LinkedList<short> l1({1, 2, 3, 4, 5});
	LinkedList<double> l2({1.2, 2.56, 3.34, 4.94, 5.77});
	LinkedList<string> l3({"Coded", "by", "Youssef", "Yammine"});

	cout << "Linked List of integers: " << l1 << endl;
	cout << "Linked List of doubles: " << l2 << endl;
	cout << "Linked List of strings: " << l3 << endl << endl;

	l1.pop_back();
	cout << "pop_back() from first list: " << l1 << endl;
	l1.pop_front();
	cout << "pop_front() from first list: " << l1 << endl;
	l1.remove(1);
	cout << "remove(1) from first list: " << l1 << endl << endl;

	cout << "Find 'Youssef' in third list: " << l3.find("Youssef") << endl;
	l3.push_back(".");
	cout << "push_back('.') to third list: " << l3 << endl;

	return 0;
}