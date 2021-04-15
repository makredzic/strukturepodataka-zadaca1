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

  size_t size_{0};
  Node* head_{nullptr}; //pokazivac na 1. node
  Node* tail_{nullptr}; //pokazivac na zadnji node

public:
  // Pravilo 6-torke
  List() = default; // ne zahtjeva implementaciju jer su clanovi klase default konstruisani

  List(const List& el);
  List(List&& el);
  List& operator=(const List& el);
  List& operator=(List&& el);
  ~List();
  
  size_t size() const {return size_;}
  bool empty() const { return size_ == 0;}

  void clear();

  void push_back();
  void push_front();
  void pop_back();
  void pop_front();

  class iterator;

  iterator begin();
  iterator end();

};

template<typename T>
class List<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T>{
    private:
      Node* p_{nullptr};
    public:
      iterator() = default;
      iterator(Node* ptr) : p_{ptr} {}
      
      iterator& operator++() {
        p_ = p_->next_;  
        return *this;
      };
      
      iterator operator++(int) {
        auto temp = iterator{p_};
        p_ = p_->next_;
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

 /*
iterator
  */
