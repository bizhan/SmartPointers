#include <iostream>
#include <memory>
using namespace std;

// smart pointers are template classes, a wraper for pointer
/*
NOTES:
0. unique_ptr is a class template.
1. unique_ptr is one of the smart pointer provided by c++11 to prevent memory
leaks.
2. unique_ptr wraps a raw pointer in it, and de-allocates the raw pointer,
   when unique_ptr object goes out of scope.
3. similar to actual pointers we can use arrow and * on the object of
unique_ptr,  because it is overloaded in unique_ptr class.
4. When exception comes then also it will de-allocate the memory hence no memory
leak.
5. Not only object we can create array of objects of unique_ptr.
*/
// Operations:
// release, reset, swap, get, get_deleter

class Foo {
  int x;

public:
  explicit Foo(int x) : x{x} {}
  int getX() { return x; }
  ~Foo() { cout << "Foo Dest" << endl; }
};
class Foo2 {
int x;
public:

};

int main() {
  //new operation example
  //p1 is pointer to Foo ojbect
  Foo *p1 = new Foo(10); 
  cout << p1->getX() << endl;
  delete p1;
  //Another way of allocating object
  //fo is a local object on the stack.
  Foo fo(20);
  cout <<fo.getX()<<endl;

  //Using unique_ptr
  //p3 is an object pointer and it is created on stack
  //a wrapper around pointer to Foo
  unique_ptr<Foo> p3(new Foo(30));
  cout<<p3->getX()<<endl;

  //using make_unique
  //P4 destructor also is called when an exception occurs.
  unique_ptr<Foo> p4 = make_unique<Foo>(40);
  cout<<p4->getX()<<endl;

  unique_ptr<Foo> p5(new Foo(50));
  //can not make p5 = p1, violates the ownership.

  //Another bad way to use unique_ptr
  // Owner ship is violated, since two unique ptr are pointing to the same pointer.
  // exception when destructors are called: (double free detected)
  Foo * p6= new Foo(60);
  unique_ptr<Foo> p7(p6);
  //unique_ptr<Foo> p8(p6);

  // We can use move to change the owner ship
  unique_ptr<Foo> p9= std::move(p4);
  cout<<p9->getX()<<endl;

  // get gives you the pointer wrapped inside the unique_ptr
  Foo *p10 = p9.get();
  cout<<p10->getX()<<endl;

  // release change the owner ship (return the owner)
  // however it SEEMS the new pointer is not managed by any object???
  Foo *p11 = p9.release();
  cout<<p11->getX()<<endl;

  unique_ptr<Foo> p12 = make_unique<Foo>(12);
  cout<<p12->getX()<<endl;
  // release return the pointer that is managed the line before does not work
  // since left hand side of assignment expect a unique_ptr object
  //unique_ptr<Foo> p13 = p12.release();
  //The line below represent what I said above is correct.
  unique_ptr<Foo> p14(p12.release());
  cout<<p14->getX()<<endl;
  
  //p9 is NULL now
  //cout<<p9->getX()<<endl;
  //p10 however still access to the pointer which was wrapped by p9
  cout<<p10->getX()<<endl;

//reset a unique ptr, it replaces the managed object with a new object and previous
  //pointer is deleted.
  unique_ptr<Foo> p15 = make_unique<Foo>(15);
  cout<<p15->getX()<<endl;
  unique_ptr<Foo> p16 = make_unique<Foo>(16);
  cout<<p16->getX()<<endl;
  //The below line will not work since reset take a managed pointer
  //p15.reset(p16);
  Foo *p17 = new Foo(17);
  //Below line works, and two things happens
  //Destroctor for p15 gets called and p15 gets to manage p17 pointer.
  p15.reset(p17);
  cout<<p15->getX()<<endl;

  unique_ptr<Foo> p18 = make_unique<Foo>(18);
  unique_ptr<Foo> p19 = make_unique<Foo>(19);
  // swap takes unique ptr argument and swaps the managed objects of two pointers.
  p18.swap(p19);
  cout<<p18->getX()<<endl;
  cout<<p19->getX()<<endl;
  
  return 0;
}