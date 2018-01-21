#include <algorithm>

#include "ctree/node.h"

using namespace ctree;

typedef std::vector<NodeRef> Super;

bool Node::push_back(NodeRef nodeRef){
  bool containsAlready = std::find(this->begin(), this->end(), nodeRef) != this->end();

  if(containsAlready)
    return false;

  Super::push_back(nodeRef);
  nodeRef->pParent = this;

  this->newChildSignal.emit(nodeRef);
  return true;
}

Node::iterator Node::erase(Node::iterator pos){
  NodeRef removed = (pos != this->end()) ? *pos : nullptr;

  auto result = Super::erase(pos);

  if(removed){
    removed->pParent=NULL;
    childRemovedSignal.emit(removed);
  }

  return result;
}

Node::iterator Node::erase(Node::const_iterator pos){
  NodeRef removed = (pos != this->end()) ? *pos : nullptr;

  auto result = Super::erase(pos);

  if(removed){
    removed->pParent=NULL;
    childRemovedSignal.emit(*pos);
  }

  return result;
}

Node::iterator Node::erase(Node::iterator first, Node::iterator last ){
  std::vector<NodeRef> removedNodeRefs(first, last);

  auto result = Super::erase(first,last);

  for(auto removedNodeRef : removedNodeRefs){
    removedNodeRef->pParent = NULL;
    childRemovedSignal.emit(removedNodeRef);
  }

  return result;
}

Node::iterator Node::erase(Node::const_iterator first, Node::const_iterator last ){
  std::vector<NodeRef> removedNodeRefs(first, last);

  auto result = Super::erase(first,last);

  for(auto removedNodeRef : removedNodeRefs){
    removedNodeRef->pParent = NULL;
    childRemovedSignal.emit(removedNodeRef);
  }

  return result;
}

Node::iterator Node::erase(NodeRef nodeRef){
  return this->erase(std::find(this->begin(), this->end(), nodeRef));
}

Node::iterator Node::erase(Node* node){
  for(auto it = this->begin(); it != this->end(); it++)
    if((*it).get() == node)
      return this->erase(it);

  return this->end();
}
