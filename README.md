# ctree
C-language hierarchical tree utils

## Run Tests

To build and run unit tests using cmake and make:
```bash
# build
cd tests
mkdir build
cd build
cmake ../proj/cmake
make -j4

# run
./Debug/ctreeTests/ctreeTests.app/Contents/MacOS/ctreeTests
```

## Usage

### Basic hierarchy operations

```c++
using namespace ctree;

std::shared_ptr<Node> root(Node::create());
std::shared_ptr<Node> child1(Node::create());
std::shared_ptr<Node> child1_child1(Node::create());
std::shared_ptr<Node> child2(Node::create());

root->add(*child1);
child1->add(*child1_child1);
root->add(*child2);
root->remove(*child1);
```

### Payload for attaching any kind of object to your node

Use functions in ctre::payload:: namespace to instantiating/fetching/destroying
custom objects alongside ctree Nodes.
```c++
using namespace ctree;

std::shared_ptr<Node> root(Node::create());

// Use payload functions to instantiate any class and 'attach' it to a node
// Yse payload functions to fetch the attached object and perform cleanups.
Node* node payload::createNode<MyCustomClass>(myclassArg1, myclassArg2);
MyCustomClass* instance = payload::getObject<MyCustomClass>(*node);
payload::destroyNode<MyCustomClass>(node);
```

Or use the Payload class as fire-and-forget container for both node and custom type objects

```c++
using namespace ctree;

Payload* payload = payload::create<MyCustomClass>(myclassArg1, myclassArg2);
Node* node = payload->getNode();

// To fetch the custom object instance we'll still need to explicitly mention its type
MyCustomClass* instance = payload->getObject<MyCustomClass>();

// payload destructor will take care of properly destructing the custom class instance, no need to know its type at this moment
delete payload; 
```