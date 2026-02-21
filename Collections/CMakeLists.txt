add_library(Collections 
Foo.cpp Foo.h 
SinglyLinkedList.cpp SinglyLinkedList.h 
DoubleLinkedList.h DoubleLinkedList.cpp
ResizingArray.h ResizingArray.cpp)

target_include_directories(Collections PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
