#include "ctree/list.h"

using namespace ctree;

void List::populate(){
  this->clear();

  if(auto root = this->observer.getRoot())
    observer::walkDown(*root, [this](Node& node){
      this->push_back(&node);
    });

  this->bUpToDate = true;
}
