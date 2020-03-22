#include "catch.hpp"

#include "ctree/payload.h"

using namespace ctree;

class CustomClass {
  public:
    int value = 3;
    std::string name = "Foo bar";
    std::function<void()> destructorFunc = nullptr;

    CustomClass() {
    }

    CustomClass(std::function<void()> func){
      destructorFunc = func;
    }

    ~CustomClass() {
      if (destructorFunc)
        destructorFunc();
    }
};

TEST_CASE("ctree::payload", ""){

  SECTION("create,get,destroy with default constructor/destructor"){
    Node* node = payload::create<CustomClass>();
    CustomClass* custom = payload::get<CustomClass>(*node);
    REQUIRE((uintptr_t)(custom) == ((uintptr_t)(node)+sizeof(Node)));
    REQUIRE(custom->value == 3);
    REQUIRE(custom->name == "Foo bar");
    payload::destroy<CustomClass>(*node);
  }

  SECTION("create, get, destroy with custom constructor/destructor"){
    int log = 0;

    Node* node = payload::create<CustomClass>([&log]() { log += 1; });
    CustomClass* custom = payload::get<CustomClass>(*node);
    REQUIRE((uintptr_t)(custom) == ((uintptr_t)(node)+sizeof(Node)));

    REQUIRE(custom->value == 3);
    REQUIRE(custom->name == "Foo bar");
    REQUIRE(custom->destructorFunc != nullptr);

    REQUIRE(log == 0);
    payload::destroy<CustomClass>(*node);
    REQUIRE(log == 1);
  }
}

TEST_CASE("ctree::Payload", ""){
  SECTION("create,get,destroy "){
    int log = 0;

    Payload* payload = Payload::create<CustomClass>([&log]() { log += 1; });

    Node* n = payload->getNode();
    CustomClass* instance = payload->getObject<CustomClass>();
    REQUIRE(instance == payload::get<CustomClass>(*n));


    REQUIRE(log == 0);
    delete payload; // no need to "know" the type of the payload for cleanup
    REQUIRE(log == 1);
  }
}
