#pragma once

#include "node.h"

namespace ctree {

  namespace payload {

    template<typename T>
    Node* create() {
      // allocate Node and Object in single block of memory
      // this way we can always calculate the Node's address from
      // the corresponding Object's address.
      void* mem = std::malloc(sizeof(Node) + sizeof(T));
      T* objaddr = (T*)((uintptr_t)mem + sizeof(Node));

      // call the constructors of the Node and Object, but
      // assign memory address manually
      T* obj = new (objaddr) T();
      Node* n = new (mem) Node();

      // // std::cout << "CREATED NODE with name '" << name << "' " << obj << std::endl;

      // // register a destroyFunc, to be executd when n->destroy is called
      // // this way the caller does not need to know about the type of object
      // // that the node points to, but it will still do the proper destruction
      // n->destroyFunc = [mem, obj, n](){
      //   // std::cout << "DELETING NODE with name: '" <<n->getName() << "': " << obj << std::endl;
      //   obj->~T();
      //   n->~Node();
      //   std::free(mem);
      // };

      return n;
    }

    template<typename T, typename... Args>
    Node* create(Args... args) {
      void* mem = std::malloc(sizeof(Node) + sizeof(T));
      T* objaddr = (T*)((uintptr_t)mem + sizeof(Node));

      Node* n = new (mem) Node();
      // call constructor with given args
      T* obj = new (objaddr) T(args...);

      return n;
    }

    template<typename T>
    T* get(Node& n) {
      return (T*)((uintptr_t)(&n) + sizeof(Node));
    }

    template<typename T>
    void destroy(Node& n) {
      T* obj = get<T>(n);
      (&n)->~Node();
      obj->~T();
      // delete &n;
      // delete obj;
      std::free(&n);
    }
  }

  class Payload {
    public:
      template<typename T, typename... Args>

      static Payload* create(Args... args) {
        Payload* payload = new Payload();
        payload->node =payload::create<T>(args...);
        payload->destroyFunc = [payload]() {
          payload::destroy<T>(*payload->node);
        };

        return payload;
      }

      ~Payload() {
        if (destroyFunc)
          destroyFunc();
      }

      Node* getNode() { return node; }

      template<typename T>
      T* getObject() {
        return payload::get<T>(*node);
      }

    private:
      Node* node;
      std::function<void()> destroyFunc = nullptr;
  };
}
