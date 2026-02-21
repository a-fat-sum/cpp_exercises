add_library(ExemplarCollections
    ResizingArray.cpp
    SinglyLinkedList.cpp
    DoublyLinkedList.cpp
    Queue.cpp
    Stack.cpp
    BinarySearchTree.cpp
    Heap.cpp
    HashMap.cpp
)

target_include_directories(ExemplarCollections PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
