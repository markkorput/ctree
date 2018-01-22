#pragma once

#include "node.h"
#include "signal.hpp"

namespace ctree {

  class observer {

    public:
      observer(Node& root): pRoot(&root) {
        this->registerItem(root, true);
      }

      ~observer();

      static void walkDown(Node&, std::function<void(Node&)> func);
      void walkDown(std::function<void(Node&)> func){ observer::walkDown(*this->pRoot, func); }

      inline Node* getRoot(){ return this->pRoot; };

    private: // private operations
      void registerItem(Node& item, bool recursive=true);
      void unregisterItem(Node& item, bool recursive=true);

    protected: // virtual method for custom behaviour by inheriting classes
      virtual void nodeAdded(Node& item){}
      virtual void nodeRemoved(Node& item){}

    public: // signals
      Signal<void(Node&)> nodeAddedSignal;
      Signal<void(Node&)> nodeRemovedSignal;

    private:
      Node* pRoot;
      std::map<Node*, std::shared_ptr<std::vector<cinder::signals::Connection>>> itemConnections;
  };
}
