#pragma once

#include "signal_vector.hpp"
#include "observer.h"
#include "node.h"

namespace ctree {
  class List;
  typedef std::shared_ptr<List> ListRef;

  class List : public signal_vector<Node*> {
    public:
      static ListRef from(Node& root){
        auto list = std::make_shared<List>(root);
        return list;
      }

    public:
      List(Node& root): observer(root), bUpToDate(false){
        auto func = [this](Node&n){ this->bUpToDate = false; };
        this->observer.nodeAddedSignal.connect(func);
        this->observer.nodeRemovedSignal.connect(func);
      }

      List& populated(){
        if(!this->bUpToDate)
          this->populate();
        return *this;
      }

    private:
      void populate();

    private:
      bool bUpToDate;
      observer observer;
  };
}
