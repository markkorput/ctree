#pragma once

#include "node.h"
#include "signal.hpp"

namespace ctree {

  class converter {

    public:
      template<typename T>
      convert(Node& root, std::function<T(Node&)> func)
        : observer(root), converterFunc(func) {
        this->observer.nodeAddedSignal.connect([this](Node& n){ this->convertNode(n); });
      }

      // ~convert();

      observer& getObserver(){ return this->observer; }

    private: // private operations

      void convertNode(Node& n){
        auto result = this->converterFunc(item);
        this.onConversion(node, result);
        this.conversionSignal.emit(node, result);
      }

    protected: // virtual method for custom behaviour by inheriting classes
      virtual void onConversion(Node& item, T result){}

    public: // signals
      Signal<void(Node&, T)> conversionSignal;

    private:
      observer observer;
      std::function<T(Node&)> converterFunc;
  };
}
