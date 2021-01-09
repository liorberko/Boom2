#include "course.h"
#include "lecture.h"
#include "hashTable.h"


int course::addLecture(){
    int new_lecture_ID= num_of_lectures;
    lecture* new_lecture = new lecture(new_lecture_ID, courseID,0);
    lectures.insert(new_lecture,new_lecture_ID);
    num_of_lectures++;
    return new_lecture_ID;
}

course::course(course& target) : courseID(target.courseID), num_of_lectures(target.num_of_lectures), lectures()
{
    for (int i=0 ; i< num_of_lectures; i++)
    {
        lecture* new_lecture = new lecture(*target.lectures.find(i));
        lectures.insert(new_lecture, i);
    }
}

std::ostream& operator<<(std::ostream& out, const course target) 
{
    out<< target.courseID;
    return out;
}

int course::getCourseID()
{
    return courseID;
}

int course::getNumOfLectures()
{
    return num_of_lectures;
}

hashTable<lecture>* course::getLectures()
{
    return &lectures;
}

course::~course()
{
    for (int i = 0 ; i< num_of_lectures; i++)
    {
        delete (lectures.find(i));
    }
    // delete(&lectures);
}