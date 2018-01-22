#include <algorithm>

#include "ctree/node.h"

using namespace ctree;

typedef std::vector<Node*> Super;

bool Node::push_back(Node* node){
  bool containsAlready = std::find(this->begin(), this->end(), node) != this->end();

  if(containsAlready)
    return false;

  Super::push_back(node);
  node->pParent = this;

  this->newChildSignal.emit(*node);
  return true;
}

Node::iterator Node::erase(Node::iterator pos){
  Node* removed = (pos != this->end()) ? *pos : nullptr;

  auto result = Super::erase(pos);

  if(removed){
    removed->pParent=NULL;
    childRemovedSignal.emit(*removed);
  }

  return result;
}

Node::iterator Node::erase(Node::const_iterator pos){
  Node* removed = (pos != this->end()) ? *pos : nullptr;

  auto result = Super::erase(pos);

  if(removed){
    removed->pParent=NULL;
    this->childRemovedSignal.emit(*(*pos));
  }

  return result;
}

Node::iterator Node::erase(Node::iterator first, Node::iterator last ){
  std::vector<Node*> nodes(first, last);

  auto result = Super::erase(first,last);

  for(auto node : nodes){
    node->pParent = NULL;
    childRemovedSignal.emit(*node);
  }

  return result;
}

Node::iterator Node::erase(Node::const_iterator first, Node::const_iterator last ){
  std::vector<Node*> nodes(first, last);

  auto result = Super::erase(first,last);

  for(auto node : nodes){
    node->pParent = NULL;
    childRemovedSignal.emit(*node);
  }

  return result;
}

Node::iterator Node::erase(Node* node){
  return this->erase(std::find(this->begin(), this->end(), node));
}
