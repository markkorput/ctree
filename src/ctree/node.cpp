#include <algorithm>

#include "ctree/node.h"

using namespace ctree;

typedef std::vector<NodeRef> Super;

bool Node::push_back(NodeRef nodeRef){
  bool containsAlready = std::find(this->begin(), this->end(), nodeRef) != this->end();

  if(containsAlready)
    return false;

  Super::push_back(nodeRef);
  this->newChildSignal.emit(nodeRef);
  return true;
}

Node::iterator Node::erase(Node::iterator pos){
  bool contained = (pos != this->end());

  auto result = Super::erase(pos);

  if(contained){
    childRemovedSignal.emit(*pos);
  }

  return result;
}

Node::iterator Node::erase(Node::const_iterator pos){
  bool contained = (pos != this->end());

  auto result = Super::erase(pos);

  if(contained){
    childRemovedSignal.emit(*pos);
  }

  return result;
}

Node::iterator Node::erase(Node::iterator first, Node::iterator last ){
  std::vector<NodeRef> removedNodeRefs(first, last);

  auto result = Super::erase(first,last);

  for(auto removedNodeRef : removedNodeRefs){
    childRemovedSignal.emit(removedNodeRef);
  }

  return result;
}

Node::iterator Node::erase(Node::const_iterator first, Node::const_iterator last ){
  std::vector<NodeRef> removedNodeRefs(first, last);

  auto result = Super::erase(first,last);

  for(auto removedNodeRef : removedNodeRefs){
    childRemovedSignal.emit(removedNodeRef);
  }

  return result;
}

Node::iterator Node::erase(NodeRef nodeRef){
  return this->erase(std::find(this->begin(), this->end(), nodeRef));
}
