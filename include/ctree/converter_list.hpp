#pragma once

#include "signal_vector.hpp"
#include "observer.h"

namespace ctree {
  template<typename T>
  class converter_list : public signal_vector<T> {
    public:
      typedef std::function<T(Node&)> ConverterFunc;

    public:
      converter_list(Node& root, ConverterFunc func)
      : observer(root), converterFunc(func), bDirty(true) {
        // if we observe any changes to our root's subtree, simply set our dirty flag
        auto dirtifier = [this](Node& n){ this->bDirty = true; };
        this->observer.nodeAddedSignal.connect(dirtifier);
        this->observer.nodeRemovedSignal.connect(dirtifier);
      }

      converter_list& updated(){
        if(this->bDirty) this->update();
        return *this;
      }

    private:

      void update() {
        this->clear();

        observer.walkDown([this](Node& n){
          // TODO: optimize so earlier converts are cached and re-used
          // and only discarded of the are no longer in the list
          auto convert = this->converterFunc(n);
          this->push_back(convert);
        });

        this->bDirty = false;
      }

    private:
      bool bDirty;
      observer observer;
      ConverterFunc converterFunc;
  };
}
