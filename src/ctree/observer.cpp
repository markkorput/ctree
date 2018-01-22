#include "ctree/list.h"

#include <iostream>

using namespace ctree;

observer::~observer(){
  if(this->pRoot)
    this->unregisterItem(*this->pRoot, true);

  if(!this->itemConnections.empty()){
    std::cerr << "observer's itemConnections not empty after recursively unregistering root";

    for(auto it=this->itemConnections.begin(); it != this->itemConnections.end(); it++) {
      for(auto conn : *(it->second))
        conn.disconnect();
    }

    itemConnections.clear();
  }
}


void observer::registerItem(Node& item, bool recursive){
  std::shared_ptr<std::vector<cinder::signals::Connection>> connections = std::make_shared<std::vector<cinder::signals::Connection>>();

  // TODO; optimize by storing one instance of both lambdas in thise observer instance and always using those
  connections->push_back(item.newChildSignal.connect([this](Node& node){
    this->registerItem(node);
    this->nodeAdded(node);
    this->nodeAddedSignal.emit(node);
  }));

  connections->push_back(item.childRemovedSignal.connect([this](Node& node){
    this->unregisterItem(node);
    this->nodeRemoved(node);
    this->nodeRemovedSignal.emit(node);
  }));

  this->itemConnections[&item] = connections;

  if(recursive)
    for(auto child : item)
      this->registerItem(*child, true);
}

void observer::unregisterItem(Node& item, bool recursive){
  if(recursive)
    for(auto child : item)
      this->unregisterItem(*child, true);

  auto connections = this->itemConnections[&item];

  if(!connections){
    std::cerr << "no connections vector found for item";
    return;
  }

  for(auto conn : (*connections))
    conn.disconnect();

  this->itemConnections.erase(&item);
}


void observer::walkDown(Node& node, std::function<void(Node&)> func){
  func(node);

  for(auto child : node)
    walkDown(*child, func);
}
