#include "catch.hpp"

#include "ctree/ctree.h"

using namespace ctree;

TEST_CASE("ctree::Node", ""){

  SECTION("getChildren"){
    Node n;
    REQUIRE(n.getChildren().size() == 0);
  }
}
