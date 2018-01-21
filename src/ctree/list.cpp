#include "ctree/list.h"

using namespace ctree;

void List::populate(){
  this->clear();

  if(!this->rootRef) return;

  this->walkDown(this->rootRef, [this](NodeRef nodeRef){
    this->push_back(nodeRef);
  });
}


void List::walkDown(NodeRef nodeRef, std::function<void(NodeRef)> func){
  func(nodeRef);

  for(auto child : (*nodeRef)){ // node
    this->walkDown(child, func);
  }
}
