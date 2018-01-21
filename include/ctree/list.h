#pragma once

#include "node.h"

namespace ctree {
  class NodeOp {
    // NodeOp
  };

  class List;
  typedef std::shared_ptr<List> ListRef;

  class List : public std::vector<NodeRef> {
    public:
      static ListRef from(NodeRef rootRef){
        auto list = std::make_shared<List>(rootRef);
        list->populate();
        return list;
      }

    public:
      List(NodeRef rootRef): rootRef(rootRef){}

      void populate();
      void walkDown(NodeRef, std::function<void(NodeRef)> func);

    private:
      NodeRef rootRef;
  };
}
