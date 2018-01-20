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
}
