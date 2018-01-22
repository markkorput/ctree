#include "catch.hpp"

#include "ctree/converter_list.hpp"

using namespace ctree;

TEST_CASE("ctree::ConverterList", ""){
  SECTION("typical_usage"){
    class MyObject;

    // create a Custom Node-based type that points at your custom object
    class CustomNode : public Node {
    public:
      CustomNode(MyObject* obj) : object(obj){}
      MyObject* object;
    };

    // Give your custom object an instance of your custom node type
    class MyObject {
    public:
      MyObject() : node(this), counter(0){}
      int counter;
      CustomNode node;
    };

    // by adding your custom node instances you've added
    // hierarchy logic to oyur object
    MyObject rootObj, childObj;
    rootObj.node.add(childObj.node);

    // use a converter list to get your custom object (or anything else)
    // for all nodes in a hiearchical structure
    converter_list<MyObject*> convList(rootObj.node, [](Node& n){
      return ((CustomNode*)&n)->object;
    });

    REQUIRE(convList.size() == 0);
    // always request .updated() because the convert_list
    // does not update automatically, but will not re-update if it is already up-to-date
    convList.updated();
    REQUIRE(convList.size() == 2);
    REQUIRE(convList[0] == &rootObj);
    REQUIRE(convList[1] == &childObj);

    for(auto obj : convList){
      obj->counter += 1;
    }

    REQUIRE(convList[0]->counter == 1);
    REQUIRE(convList[1]->counter == 1);
  }
}
