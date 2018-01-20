#pragma once

#include <vector>

namespace ctree {
  class Node {

  public:
    const std::vector<std::shared_ptr<Node>>& getChildren() { return this->children; }

  private:
    std::vector<std::shared_ptr<Node>> children;
  };
}
