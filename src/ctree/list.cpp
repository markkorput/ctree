#include "ctree/list.h"

#include <iostream>

using namespace ctree;

void List::setup(){
  this->newItemSignal.connect([this](Node* node){
    this->registerItem(*node);
  });

  this->itemRemovedSignal.connect([this](Node* node){
    this->unregisterItem(*node);
  });
}

void List::registerItem(Node& item){
  std::shared_ptr<std::vector<cinder::signals::Connection>> connections = std::make_shared<std::vector<cinder::signals::Connection>>();

  auto func = [this](Node& child){
    this->bUpToDate=false;
  };

  connections->push_back(item.newChildSignal.connect(func));
  connections->push_back(item.childRemovedSignal.connect(func));
  this->itemConnections[&item] = connections;
}

void List::unregisterItem(Node& item){
  auto connections = this->itemConnections[&item];

  if(!connections){
    std::cerr << "no connections vector found for item";
    return;
  }

  for(auto conn : (*connections))
    conn.disconnect();

  this->itemConnections.erase(&item);
}

void List::populate(){
  this->clear();

  if(!this->pRoot) return;

  this->walkDown(*this->pRoot, [this](Node& node){
    this->push_back(&node);
  });

  this->bUpToDate = true;
}

void List::walkDown(Node& node, std::function<void(Node&)> func){
  func(node);

  for(auto child : node)
    this->walkDown(*child, func);
}
