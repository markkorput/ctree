#include "catch.hpp"

#include "ctree/ctree.h"

using namespace ctree;

TEST_CASE("ctree::Node", ""){

  SECTION("size"){
    Node n;
    REQUIRE(n.size() == 0);
  }

  SECTION("push_back"){
    Node parent;

    auto child = std::make_shared<Node>();

    REQUIRE(parent.push_back(child));
    // use operator[] to get first child
    REQUIRE(parent[0] == child);

    // fails to add when child is already in the list
    REQUIRE(!parent.push_back(child));

    // also takes regular pointers
    Node *child2 = new Node();
    REQUIRE(parent.push_back(child2));
    REQUIRE(parent[1].get() == child2);
  }

  SECTION("newChildSignal"){
    Node parent;
    auto child = std::make_shared<Node>();
    NodeRef result=nullptr;
    // register newChildSignal callback that writes the new child to result
    parent.newChildSignal.connect([&result](NodeRef newChildRef){ result = newChildRef; });
    // verify initial state
    REQUIRE(result == nullptr);
    // add child
    parent.push_back(child);
    // verify signal callback got executed
    REQUIRE(result == child);
  }

  SECTION("childRemovedSignal"){
    SECTION("for_erase_NodeRef"){
      Node parent;
      auto child = std::make_shared<Node>();
      parent.push_back(child);
      NodeRef result=nullptr;
      // register newChildSignal callback that writes the new child to result
      parent.childRemovedSignal.connect([&result](NodeRef newChildRef){ result = newChildRef; });
      // verify initial state
      REQUIRE(result == nullptr);
      // erase child
      parent.erase(child);
      // verify signal callback got executed
      REQUIRE(result == child);
    }

    SECTION("for_erase_iterator"){
      Node parent;
      auto child = std::make_shared<Node>();
      parent.push_back(child);
      NodeRef result=nullptr;
      // register newChildSignal callback that writes the new child to result
      parent.childRemovedSignal.connect([&result](NodeRef newChildRef){ result = newChildRef; });
      // verify initial state
      REQUIRE(result == nullptr);
      // erase child
      REQUIRE(parent.erase(parent.begin()) == parent.end());
      // verify signal callback got executed
      REQUIRE(result == child);
    }
  }
}
