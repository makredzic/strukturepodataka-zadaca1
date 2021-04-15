#pragma once
#include <utility>
#include <cstddef> // size_t --> type_traits ukljucuje cstddef
#include <iterator>

template <typename T>
class List {

private:
  class Node {
    T element_;
    Node* next_ = nullptr;
    Node* prev_ = nullptr;

    Node(const T& el, Node* n = nullptr, Node* p = nullptr) : element_{el}, next_{n}, prev_{p} {} 
    Node(T&& el, Node* n = nullptr, Node* p = nullptr) : element_{std::move(el)}, next_{n}, prev_{p} {}
  };

  Node* head_{nullptr}; //pokazivac na 1. node
  Node* tail_{nullptr}; //pokazivac na zadnji node
  size_t size_{0};

public:
  // Pravilo 6-torke
  List() = default; // ne zahtjeva implementaciju jer su clanovi klase default konstruisani

  List(const List& other);
  List(List&&);
  List& operator=(const List&);
  List& operator=(List&&);
  ~List() {clear();};
  
  size_t size() const {return size_;}
  bool empty() const { return size_ == 0;}

  void clear();

  void push_back(const T&);
  void push_back(T&&);

  void push_front(const T&);
  void push_front(T&&);

  void pop_back();
  void pop_front();

  class iterator;

  iterator begin();
  iterator end();

};


//  DEFINICIJE METODA
template<typename T>
void List<T>::clear() {
  if (size_ == 0) return;

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

template<typename T>
class List<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T>{
    private:
      Node* p_{nullptr};
    public:
      iterator() = default;
      iterator(Node* ptr) : p_{ptr} {}
      
      iterator& operator++() {
        if (p_ != nullptr) p_ = p_->next_;  
        return *this;
      };
      
      iterator operator++(int) {
        auto temp = iterator{p_};
        if (p_ != nullptr) p_ = p_->next_;
        
        return temp;
      };
      
      bool operator==(const iterator& other) const {
        return p_ == other.p_;
      }
      
      bool operator!=(const iterator& other) const {
        return p_ != other.p;
      }
      
      T& operator*() {
        return p_->element_;
      };
      
      T& operator->() {
        return p_->element_; 
      }
};

template <typename T>
class List<T>::iterator List<T>::begin() {
  return iterator{head_};
}

template <typename T>
class List<T>::iterator List<T>::end() {
  return iterator{}; //vracamo iterator koji pokazuje na nullptr, default konstruktor inicijalizira sa nullptr pa ne pise u {} eskplicitno nullptr
}
