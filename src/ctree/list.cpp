#include "ctree/list.h"

#include <iostream>

using namespace ctree;

void List::setup(){
  this->newItemSignal.connect([this](NodeRef nodeRef){
    this->registerItem(nodeRef);
  });

  this->itemRemovedSignal.connect([this](NodeRef nodeRef){
    this->unregisterItem(nodeRef);
  });
}

void List::registerItem(NodeRef itemRef){
  std::shared_ptr<std::vector<cinder::signals::Connection>> connections = std::make_shared<std::vector<cinder::signals::Connection>>();

  connections->push_back(itemRef->newChildSignal.connect([this](NodeRef newChildRef){
    this->bUpToDate=false;

    // // register entire subtree
    // this->walkDown(newChildRef, [this](NodeRef nodeRef){
    //   this->registerItem(nodeRef);
    // });
  }));

  connections->push_back(itemRef->childRemovedSignal.connect([this](NodeRef removedItemRef){
    this->bUpToDate=false;

    // // unregister entire subtree
    // this->walkDown(removedItemRef, [this](NodeRef nodeRef){
    //   this->unregisterItem(nodeRef);
    // });
  }));

  this->itemConnections[itemRef.get()] = connections;
}

void List::unregisterItem(NodeRef itemRef){
  auto connections = this->itemConnections[itemRef.get()];

  if(connections == nullptr){
    std::cerr << "no connections vector found for item";
    return;
  }

  for(auto conn : (*connections))
    conn.disconnect();

  this->itemConnections.erase(itemRef.get());
}

void List::populate(){
  this->clear();

  if(!this->rootRef) return;

  this->walkDown(this->rootRef, [this](NodeRef nodeRef){
    this->push_back(nodeRef);
  });

  this->bUpToDate = true;
}

void List::walkDown(NodeRef nodeRef, std::function<void(NodeRef)> func){
  func(nodeRef);

  for(auto child : (*nodeRef)){ // node
    this->walkDown(child, func);
  }
}
