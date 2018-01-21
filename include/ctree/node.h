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

      // modifier methods
      bool push_back(NodeRef nodeRef);
      bool push_back(Node* node){ return this->push_back(std::shared_ptr<Node>(node)); }

      iterator erase(iterator pos);
      iterator erase(const_iterator pos);
      iterator erase(iterator first, iterator last );
      iterator erase(const_iterator first, const_iterator last );
      iterator erase(NodeRef nodeRef);

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
      NodeRef parentRef;
  };
}
