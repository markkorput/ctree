#pragma once

#include <vector>
#include <iostream>

#include "signal.hpp"

namespace ctree {

  class Node;
  typedef std::shared_ptr<Node> NodeRef;

  class Node : public std::vector<Node*> {
    public:

      typedef std::vector<Node*>::iterator iterator;
      typedef std::vector<Node*>::const_iterator const_iterator;

    public:

      static Node* create(){ return new Node(); }

    public:

      Node() : pParent(NULL) {
      }

      // accessor methods
      Node* child(unsigned int idx){ return (*this)[idx]; }
      Node* parent(){ return this->pParent; }

      // modifier methods
      bool push_back(Node* node);

      iterator erase(iterator pos);
      iterator erase(const_iterator pos);
      iterator erase(iterator first, iterator last );
      iterator erase(const_iterator first, const_iterator last );
      iterator erase(Node* node);

      Node& add(Node& child){ this->push_back(&child); return *this; }
      Node& remove(Node& child){ this->erase(&child); return *this; }

      void clear(){ for(auto child : (*this)) this->erase(child); }

      // TODO overload the remaining modifier methods to make sure they all trigger the necessary event(s)
      void insert(Node*){ std::cerr << "ctree::Node::insert not yet implemented"; }
      // emplace
      // emplace_back
      // pop_back
      // resize
      // swap

    public: // signals

      Signal<void(Node&)> newChildSignal;
      Signal<void(Node&)> childRemovedSignal;

    private:
      Node* pParent;
  };
}
