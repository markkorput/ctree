#pragma once

#include "signal_vector.hpp"
#include "node.h"

namespace ctree {
  class NodeOp {
    // NodeOp
  };

  class List;
  typedef std::shared_ptr<List> ListRef;

  class List : public signal_vector<NodeRef> {
    public:
      static ListRef from(NodeRef rootRef){
        auto list = std::make_shared<List>(rootRef);
        return list;
      }

    public:
      List(NodeRef rootRef): rootRef(rootRef), bUpToDate(false){
        this->setup();
      }

      List& populated(){
        if(!this->bUpToDate)
          this->populate();
        return *this;
      }

    private:
      void setup();
      void registerItem(NodeRef itemRef);
      void unregisterItem(NodeRef itemRef);

    private:
      void populate();
      void walkDown(NodeRef, std::function<void(NodeRef)> func);

    private:
      bool bUpToDate;
      NodeRef rootRef;
      std::map<Node*, std::shared_ptr<std::vector<cinder::signals::Connection>>> itemConnections;
  };
}
