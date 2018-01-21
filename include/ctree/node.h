#pragma once

#include <vector>
#include <iostream>

#include "signal.hpp"

namespace ctree {

  class Node;
  typedef std::shared_ptr<Node> NodeRef;

  class Node : public std::vector<NodeRef> {
    public:

      typedef std::vector<NodeRef>::iterator iterator;
      typedef std::vector<NodeRef>::const_iterator const_iterator;

    public:

      static NodeRef create(){ return std::make_shared<Node>(); }

    public:

      Node() : pParent(NULL) {
      }

      // accessor methods
      NodeRef child(unsigned int idx){ return (*this)[idx]; }
      Node* parent(){ return this->pParent; }

      // modifier methods
      bool push_back(NodeRef nodeRef);
      bool push_back(Node* node){ return this->push_back(std::shared_ptr<Node>(node)); }

      iterator erase(iterator pos);
      iterator erase(const_iterator pos);
      iterator erase(iterator first, iterator last );
      iterator erase(const_iterator first, const_iterator last );
      iterator erase(NodeRef nodeRef);
      iterator erase(Node* node);

      Node& add(NodeRef child){ this->push_back(child); return *this; }
      Node& add(Node* child){ this->push_back(child); return *this; }
      Node& remove(NodeRef child){ this->erase(child); return *this; }
      Node& remove(Node* child){ this->erase(child); return *this; }

      void clear(){ for(auto child : (*this)) this->erase(child); }

      // TODO overload the remaining modifier methods to make sure they all trigger the necessary event(s)
      void insert(NodeRef){ std::cerr << "ctree::Node::insert not yet implemented"; }
      // emplace
      // emplace_back
      // pop_back
      // resize
      // swap

    public: // signals

      Signal<void(NodeRef)> newChildSignal;
      Signal<void(NodeRef)> childRemovedSignal;

    private:
      Node* pParent;
  };
}
