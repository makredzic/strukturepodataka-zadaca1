#pragma once
#include <cstddef> // size_t --> type_traits ukljucuje cstddef
#include <exception>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename T> class List {

private:
  struct Node {
    T element_;
    Node* next_ = nullptr;
    Node* prev_ = nullptr;

    Node(const T &el, Node *n = nullptr, Node *p = nullptr)
        : element_{el}, next_{n}, prev_{p} {}
    Node(T &&el, Node *n = nullptr, Node *p = nullptr)
        : element_{std::move(el)}, next_{n}, prev_{p} {}
  };

  Node* head_{nullptr}; // pokazivac na 1. node
  Node* tail_{nullptr}; // pokazivac na zadnji node
  size_t size_{0};

public:
  // Pravilo 6-torke
  List() = default; // ne zahtjeva implementaciju jer su clanovi klase default konstruisani

  List(const List &other);
  List(List &&);
  List &operator=(const List &);
  List &operator=(List &&);
  ~List() { clear(); };

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  void clear();

  void push_back(const T &);
  void push_back(T &&);

  void push_front(const T &);
  void push_front(T &&);

  void pop_back();
  void pop_front();

  void print() const;

  class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    Node* p_;
		Node* pPrev_;

  public:
    iterator() = delete;

    iterator(Node* ptrCurrent = nullptr, Node* ptrPrev = nullptr) : p_{ptrCurrent}, pPrev_{ptrPrev} {
			if (!ptrCurrent && !ptrPrev) throw std::invalid_argument("Both arguments can't be nullptr.");
		}

		iterator(const iterator& other) : p_{other.p_}, pPrev_{other.pPrev_} {} //copy-constructor


    iterator &operator=(const iterator &other) {
      p_ = other.p_;
			pPrev_ = other.pPrev_;
      return *this;
    }

    iterator &operator++() {
			if (p_ != nullptr) { //u slucaju da trenutni p_ nije nullptr odnosno nije end()
				pPrev_ = p_;
				p_ = p_->next_;
			}

      return *this;
    };

    iterator operator++(int) {
      auto temp = iterator{p_};
			if (p_ != nullptr) {
				pPrev_ = p_;
				p_ = p_->next_;
			}

      return temp;
    };

    iterator& operator--() {
			if (pPrev_ != nullptr) {
				p_ = pPrev_;
				pPrev_ = pPrev_ -> prev_;
			}

      return *this;
    };

    iterator operator--(int) {
      auto temp = iterator{p_};
			if (pPrev_ != nullptr) {
				p_ = pPrev_;
				pPrev_ = pPrev_ -> prev_;
			}

      return temp;
    };

    bool operator==(const iterator &other) const { return p_ == other.p_; } //nema potrebe porediti i prethodne pointere jer se uvijek zajendo krecu
    bool operator!=(const iterator &other) const { return p_ != other.p_; }

    T& operator*() { 
			if (p_ == nullptr) throw std::string("Error calling operator*(). Can't dereference nullptr.\n"); //trebaju se samo exceptions bacati, nisam mogao naci koji std excpetion odgovara ovome zato sam odlucio bolje string exception baciti nego dozvoliti pokusaj dereferenciranja nullptr
			return p_->element_;
		}
    T& operator->() {
			if (p_ == nullptr) throw std::string("Error calling operator->(). Can't dereference nullptr.\n"); 
			return p_->element_;
		}

    friend List;
  };

  iterator begin() { return iterator{head_}; }
  iterator end() {return iterator{nullptr, tail_}; } //konstruktor od iteratora uzima 2 argumenta, 1. je pointer na trenutni, 2. je pointer na prethodni

	//potreban je overload sa rvalue referencom za slucaj da proslijedimo it++ kao argument
  void insert(iterator&, const T &);
  void insert(iterator&&, const T &);
  void remove(iterator&);
  void remove(iterator&&);
};

//  DEFINICIJE METODA
template <typename T> void List<T>::push_back(const T &el) {

  Node *new_node_ptr = new Node{el};

  if (empty()) {
    head_ = tail_ = new_node_ptr;
  } else {
    tail_->next_ = new_node_ptr;
    new_node_ptr->prev_ = tail_;
    tail_ = new_node_ptr;
  }

  ++size_;
};

template <typename T> void List<T>::push_back(T &&el) {

  Node *new_node_ptr = new Node{std::move(el)};

  if (empty()) {
    head_ = tail_ = new_node_ptr;
  } else {
    tail_->next_ = new_node_ptr;
    new_node_ptr->prev_ = tail_;
    tail_ = new_node_ptr;
  }

  ++size_;
};

template <typename T> void List<T>::push_front(const T &el) {
  if (empty())
    push_back(el);
  else {
    Node *new_node_ptr = new Node{el, head_};
    head_->prev_ = new_node_ptr;
    head_ = new_node_ptr;
    ++size_;
  }
};

template <typename T> void List<T>::push_front(T &&el) {
  if (empty())
    push_back(std::move(el));
  else {
    Node *new_node_ptr = new Node{std::move(el), head_};
    head_->prev_ = new_node_ptr;
    head_ = new_node_ptr;
    ++size_;
  }
};

template <typename T> void List<T>::pop_back() {
  if (empty())
    return;
  if (size_ == 1)
    return clear();

  Node *temp = tail_;

  tail_ = tail_->prev_;
  tail_->next_ = nullptr;

  temp->prev_ = nullptr; // vjerovatno bespotrebno jer se node taj brise ispod
  delete temp;
};

template <typename T> void List<T>::pop_front() {
  if (empty())
    return;
  if (size_ == 1)
    return clear();

  Node *temp = head_;

  head_ = head_->next_;
  head_->prev_ = nullptr;

  temp->next_ =
      nullptr; // isto vjerovatno bespotrebno jer se svakako ispod brise temp
  delete temp;
};

template <typename T> List<T>::List(const List &other) {
  if (other.empty())
    return;
  for (Node *temp = other.head_; temp != nullptr; temp = temp->next_)
    push_back(temp->element_);
};

template <typename T>
List<T>::List(List &&other)
    : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
};

template <typename T> List<T> &List<T>::operator=(const List &other) {
  if (this == &other)
    return *this;

  clear();
  for (Node *temp = other.head_; temp != nullptr; temp = temp->next_)
    push_back(temp->element_);
  return *this;
};

template <typename T> List<T> &List<T>::operator=(List &&other) {
  if (this == &other)
    return *this;

  clear();

  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;

  return *this;
};

template <typename T>

void List<T>::clear() {
  if (size_ == 0)
    return;

  auto temp = head_;
  while (temp != nullptr) {
    head_ = temp;
    temp = temp->next_;
    delete head_;
    --size_;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T> void List<T>::print() const {

  for (Node *temp = head_; temp != nullptr; temp = temp->next_) {
    std::cout << temp->element_ << " ";
  }
  std::cout << std::endl;
};

template <typename T> void List<T>::insert(iterator& it, const T &el) {

  if (it == begin()) {
    push_front(el);
  } else

  if (it == end()) {
    push_back(el);
  } else {

    Node *new_node = new Node{el, it.p_, it.p_->prev_};

    it.p_->prev_->next_ = new_node;
    it.p_->prev_ = new_node;

		it.pPrev_ = new_node;

    ++size_;
  }
};

template <typename T> void List<T>::remove(iterator& it) {

  if (it == begin()) {
    pop_front();
  } else

	if (it == end()) {
    pop_back();
  } else {

    it.p_->prev_->next_ = it.p_->next_;
    it.p_->next_->prev_ = it.p_->prev_;

		it.pPrev_ = it.p_->prev_;
    --size_;
  }
};

template <typename T> void List<T>::insert(iterator&& it, const T &el) {

  if (it == begin()) {
    push_front(el);
  } else

  if (it == end()) {
    push_back(el);
  } else {

    Node *new_node = new Node{el, it.p_, it.p_->prev_};

    it.p_->prev_->next_ = new_node;
    it.p_->prev_ = new_node;

    ++size_;
  }
};

template <typename T> void List<T>::remove(iterator&& it) {

  if (it == begin()) {
    pop_front();
  } else

	if (it == end()) {
    pop_back();
  } else {

    it.p_->prev_->next_ = it.p_->next_;
    it.p_->next_->prev_ = it.p_->prev_;

    --size_;
  }
};
