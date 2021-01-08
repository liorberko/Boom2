#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_
#include <string>
class BoomExceptions : public std::exception
{
public:
  std::string error_name;
  BoomExceptions(std::string description) : error_name(description) {};
  std::string what()
  {
    return error_name;
  };
};

class Success : public BoomExceptions
{
public:
  Success() : BoomExceptions("SUCCESS") {}
};
class Failure : public BoomExceptions
{
public:
  Failure() : BoomExceptions("FAILURE") {}
};
class Invalid_input : public BoomExceptions
{
public:
  Invalid_input() : BoomExceptions("INVALID_INPUT") {}
};
class Allocation_Error : public BoomExceptions
{
public:
  Allocation_Error() : BoomExceptions("ALLOCATION_ERROR") {}
};
#endif