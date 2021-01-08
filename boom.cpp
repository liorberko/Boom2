#include "boom.h"

boom::~boom(){
    
}

bool boom::AddCourse(int courseID){
    if(hash_courses.find(courseID)) return false; // course already exists// failure by definition
    course* new_course = new course(courseID);  
    hash_courses.insert(new_course, courseID);
    return true;
}

void boom::RemoveCourse(int courseID)
{
    course* to_remove = hash_courses.find(courseID);
    for (int i=0 ; i< to_remove->getNumOfLectures(); i++)
    {
        AVLnode<lecture,lectureKey>* lecture_to_remove = avl_lectures.find(((to_remove->getLectures())->find(i))->getKey());
        avl_lectures.removeVertex(lecture_to_remove);
    }
    hash_courses.removeElement(to_remove->getCourseID());
    delete (to_remove);
}

int boom::AddClass(int courseID){
    if(!hash_courses.find(courseID)) return -1; // course does not exist.
    course* course=hash_courses.find(courseID);
    int lectureID = course->addLecture();
    return lectureID;
}

bool boom::WatchClass(int courseID, int classID, int time)
{
    course* the_course = hash_courses.find(courseID);
    if (the_course == NULL)
    {
        return false;
    }
    lecture* the_lec = ((the_course->getLectures()).find(courseID));
    if (the_lec == NULL)
    {
        return false;
    }
    if (the_lec->getViewTime() == 0)
    {
        the_lec->getViewTime() = time;
        avl_lectures.
    }
    
}

lecture* boom::GetIthWatchedClass(int i);

int boom::TimeViewed(int courseID, int classID){
    if(!hash_courses.find(courseID)) return false; // course does not exists// failure by definition
    course* course=hash_courses.find(courseID);
    hashTable<lecture>* course_lecturs_has = course->getLectures();
}