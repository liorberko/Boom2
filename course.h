#ifndef COURSE_H
#define COURSE_H
#include "lecture.h"
#include "hashTable.h"

class course 
{
    int courseID;
    int num_of_lectures;
    hashTable<lecture> lectures;
    public:
    int getCourseID();
    int getNumOfLectures();
    int addLecture();
    hashTable<lecture>* getLectures();
    friend std::ostream& operator<<(std::ostream& out, const course target) ;
    course(int courseID) : courseID(courseID), num_of_lectures(0),lectures() {} 
    course(course& target);
    ~course();
};


#endif /* COURSE_H */ 