#include <algorithm>

#include "ctree/node.h"

using namespace ctree;

typedef std::vector<NodeRef> Super;

bool Node::push_back(NodeRef nodeRef){
  bool containsAlready = std::find(this->begin(), this->end(), nodeRef) != this->end();

  if(containsAlready)
    return false;

  Super::push_back(nodeRef);
  return true;
}

Node::iterator Node::erase(Node::iterator pos){
  bool contained = (pos != this->end());

  Super::erase(pos);

  if(contained){
    // removedChildEvent.trigger(*it)
  }
}

Node::iterator Node::erase(Node::const_iterator pos){
  bool contained = (pos != this->end());

  Super::erase(pos);

  if(contained){
    // removedChildEvent.trigger(*it)
  }
}

Node::iterator Node::erase(Node::iterator first, Node::iterator last ){
  std::vector<NodeRef> removedNodeRefs(first, last);

  Super::erase(first,last);

  for(auto removeNodeRef : removedNodeRefs){
    // removedChildEvent.trigger(*it)
  }
}

Node::iterator Node::erase(Node::const_iterator first, Node::const_iterator last ){
  std::vector<NodeRef> removedNodeRefs(first, last);

  Super::erase(first,last);

  for(auto removeNodeRef : removedNodeRefs){
    // removedChildEvent.trigger(*it)
  }
}

Node::iterator Node::erase(NodeRef nodeRef){
  this->erase(std::find(this->begin(), this->end(), nodeRef));
}
