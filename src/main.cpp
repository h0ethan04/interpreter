// #include <boost/version.hpp>
#include <iostream>
#include <iomanip>

#include <variant>

int main()
{

   return 0;
}




// int main()
// {
// //    std::cout << "C++ Boost version: " 
// //          << BOOST_VERSION / 100000
// //          << "."
// //          << BOOST_VERSION / 100 % 1000
// //          << "."
// //          << BOOST_VERSION % 100 
// //          << std::endl;

//    std::variant<int, std::string> hello{"hello world"};
   
//    if (std::holds_alternative<int>(hello))
//    {
//       std::cout << "int " << std::get<int>(hello) << " was in hello" << std::endl;
//    }
//    else if (std::holds_alternative<std::string>(hello))
//    {
//       std::cout << "string " << std::get<std::string>(hello) << " was in hello" << std::endl;
//    }

//    return 0;
// }



// #include<iostream>

// int main() {
//     if (__cplusplus == 202101L) std::cout << "C++23";
//     else if (__cplusplus == 202002L) std::cout << "C++20";
//     else if (__cplusplus == 201703L) std::cout << "C++17";
//     else if (__cplusplus == 201402L) std::cout << "C++14";
//     else if (__cplusplus == 201103L) std::cout << "C++11";
//     else if (__cplusplus == 199711L) std::cout << "C++98";
//     else std::cout << "pre-standard C++." << __cplusplus;
//     std::cout << "\n";
//     return 0;
// }

// #include <iostream>
// class X
// {
// public: int i;
//       // first X constructor
//    X(int ia)
//    {
//       i = ia;
//    };
//       // second X constructor
//    X(int ib, int jb)
//    {
//       i = ib + jb;
//    };
//        // X member function myfunc()
//    void myfunc()
//    {
//       i *= 2;
//    };
//       // X destructor
//    ~X()
//    {
//       int id;
//       id = i / 2;
//       if (id < 7 || id > 10)
//       printf("Error - Out of range\n");
//    };
// };
// int main()
// {
//    X *x1 = new X(7);
//    X *x2 = new X(6,2);
//    X *x3 = new X(9);
//    X *x4 = new X(9,1);
//    x1->myfunc();
//    x2->myfunc();
//    x3->myfunc();
//    x4->myfunc();
//    delete x1;
//    delete x2;
//    delete x3;
//    delete x4;
//    return 0;
// }