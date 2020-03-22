#include "catch.hpp"

#include "ctree/list.h"

using namespace ctree;

TEST_CASE("ctree::List", ""){
  SECTION("basics"){
    // create node
    auto root = &Node::create()
      // add child node, whit grandchild node
      ->add(Node::create()->add(*Node::create()))
      // add another child node with a grandchild node
      .add(Node::create()->add(*Node::create()));

    // check list (array) from hierarchy
    auto listRef = List::from(*root);
    REQUIRE(listRef->populated().size() == 5);
    REQUIRE(listRef->at(0) == root);
    REQUIRE(listRef->at(1) == root->child(0));
    REQUIRE(listRef->at(2) == root->child(0)->child(0));
    REQUIRE(listRef->at(3) == root->child(1));
    REQUIRE(listRef->at(4) == root->child(1)->child(0));

    // remove child (with grand child)
    root->remove(*root->child(0));
    // verify has only one (direct) child
    REQUIRE(root->size() == 1);
    // full hierarchy contains 3 nodes
    REQUIRE(listRef->populated().size() == 3);
    // remove grandchild
    root->child(0)->remove(*root->child(0)->child(0));
    // add new grandchild
    root->child(0)->add(*Node::create());
    // and child to grandchild
    root->child(0)->child(0)->add(*Node::create());
    // verify full hierarchy contains 4 nodes
    REQUIRE(listRef->populated().size() == 4);
  }
}
