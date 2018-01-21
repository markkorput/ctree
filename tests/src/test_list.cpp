#include "catch.hpp"

#include "ctree/list.h"

using namespace ctree;

TEST_CASE("ctree::List", ""){
  SECTION("basics"){
    NodeRef root = Node::create();
    root->add(Node::create());
    root->add(Node::create());
    root->child(0)->add(Node::create());
    root->child(1)->add(Node::create());

    auto listRef = List::from(root);
    REQUIRE(listRef->size() == 5);
    REQUIRE(listRef->at(0) == root);
    REQUIRE(listRef->at(1) == root->child(0));
    REQUIRE(listRef->at(2) == root->child(0)->child(0));
    REQUIRE(listRef->at(3) == root->child(1));
    REQUIRE(listRef->at(4) == root->child(1)->child(0));
  }
}
