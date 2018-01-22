#pragma once

#include "signal_vector.hpp"
#include "node.h"

namespace ctree {
  class NodeOp {
    // NodeOp
  };

  class List;
  typedef std::shared_ptr<List> ListRef;

  class List : public signal_vector<Node*> {
    public:
      static ListRef from(Node& root){
        auto list = std::make_shared<List>(root);
        return list;
      }

    public:
      List(Node& root): pRoot(&root), bUpToDate(false){
        this->setup();
      }

      List& populated(){
        if(!this->bUpToDate)
          this->populate();
        return *this;
      }

    private:
      void setup();
      void registerItem(Node& item);
      void unregisterItem(Node& item);

    private:
      void populate();
      void walkDown(Node&, std::function<void(Node&)> func);

    private:
      bool bUpToDate;
      Node* pRoot;
      std::map<Node*, std::shared_ptr<std::vector<cinder::signals::Connection>>> itemConnections;
  };
}
