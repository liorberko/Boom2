#include "course.h"
#include "AVLtree.h"
#include "AVLnode.h"
#include "lecture.h"
#include "lectureKey.h"
#include "hashTable.h"
#include "boom.h"
#include <iostream>

main ()
{
    boom test;
    try
    {
        std::cout << "Add class 111 : ";
        test.AddCourse(111);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Add class 222 : ";
        test.AddCourse(222);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Add class 333 : ";
        test.AddCourse(333);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Add class 444 : ";
        test.AddCourse(444);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Add class 555 : ";
        test.AddCourse(555);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Add class 555 : "; //  tring to faile
        test.AddCourse(555);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    try
    {
        std::cout << "remove course 555 : ";
        test.RemoveCourse(555);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "add class 0 to course 111 : ";
        test.AddClass(111);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "add class 1 to course 111 : ";
        test.AddClass(111);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "add class 2 to course 111 : ";
        test.AddClass(111);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "add class 0 to course 222 : ";
        test.AddClass(222);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "add class 0 to course 333 : ";
        test.AddClass(333);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Watch class 1 of course 111 : ";
        test.WatchClass(111, 1 , 1);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Watch class 0 of course 222 : ";
        test.WatchClass(222, 0 , 2);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Watch class 0 of course 333 : ";
        test.WatchClass(333, 0 , 3);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "Watch class 0 of course 444, tring to faile : ";
        test.WatchClass(444, 0 , 4);
        std::cout << "Succes" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "the srconde watched class is : ";
        std::cout << test.GetIthWatchedClass(2) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "the timed viewed off class 0 of course 222 is : ";
        std::cout << test.TimeViewed(222, 0) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 1;
}