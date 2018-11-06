#include "catch.hpp"

#include "cinder/app/App.h" // for CINDER_MSW macro
#include "ctree/node.h"

using namespace ctree;

TEST_CASE("ctree::Node", ""){

  SECTION("size"){
    Node n;
    REQUIRE(n.size() == 0);
  }

  SECTION("push_back"){
    Node parent;
    auto child = Node::create();

    REQUIRE(parent.push_back(child));
    // use operator[] to get first child
    REQUIRE(parent[0] == child);

    // fails to add when child is already in the list
    REQUIRE(!parent.push_back(child));

    // also takes regular pointers
    Node *child2 = new Node();
    REQUIRE(parent.push_back(child2));
    REQUIRE(parent[1] == child2);
  }

  SECTION("newChildSignal"){
    Node parent;
    auto child = Node::create();
    Node* result=NULL;
    // register newChildSignal callback that writes the new child to result
    parent.newChildSignal.connect([&result](Node& newChild){ result = &newChild; });
    // verify initial state
    REQUIRE(result == NULL);
    // add child
    parent.push_back(child);
    // verify signal callback got executed
    REQUIRE(result == child);
  }

  SECTION("childRemovedSignal"){
    SECTION("for_erase_Node"){
      Node parent;
      auto child = Node::create();
      parent.push_back(child);
      Node* result=NULL;
      // register newChildSignal callback that writes the new child to result
      parent.childRemovedSignal.connect([&result](Node& newChild){ result = &newChild; });
      // verify initial state
      REQUIRE(result == NULL);
      // erase child
      parent.erase(child);
      // verify signal callback got executed
      REQUIRE(result == child);
    }

    SECTION("for_erase_iterator"){
      Node parent;
      auto child = Node::create();
      parent.push_back(child);
      Node* result=NULL;
      // register newChildSignal callback that writes the new child to result
      parent.childRemovedSignal.connect([&result](Node& newChild){ result = &newChild; });
      // verify initial state
      REQUIRE(result == NULL);
      // erase child
      // this fails in VS, probably because MSVC STL invalidates the iterator
      // see nmr's answer at: https://stackoverflow.com/questions/8421623/vector-iterators-incompatible
	  auto erase_result = parent.erase(parent.begin());
      #ifndef CINDER_MSW
      REQUIRE(erase_result == parent.end());
      #endif
 
      // verify signal callback got executed
      REQUIRE(result == child);
    }
  }

  SECTION("child_and_parent_add_and_erase"){
    Node root;
    auto a1 = Node::create()
      , a2 = Node::create()
      , b1 = Node::create();

    root
      .add(a1->add(*a2))
      .add(*b1);

    REQUIRE(root.child(0)->child(0) == a2);
    REQUIRE(root.child(0)->child(0)->parent() == a1);

    root.erase(a1);
    REQUIRE(root.child(0) == b1);
    REQUIRE(a1->parent() == NULL);
    REQUIRE(a2->parent() == a1);
  }
}
