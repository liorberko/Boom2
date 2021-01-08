#include "boom.h"

boom::~boom(){
    for(int i=0; i<hash_courses.getSize(); i++){
        hash_element<course>* current = hash_courses[i];
        while (current!= nullptr)
        {
            delete current->data;
            current=current->next;
        }
    }
}

void boom::AddCourse(int courseID){
    if(hash_courses.find(courseID)) throw(Failure()); // course already exists// failure by definition
    course* new_course = new course(courseID);  
    hash_courses.insert(new_course, courseID);
}

void boom::RemoveCourse(int courseID)
{
    course* to_remove = hash_courses.find(courseID);
    if (to_remove == NULL) throw (Failure());
    for (int i=0 ; i< to_remove->getNumOfLectures(); i++)
    {
        AVLnode<lecture,lectureKey>* lecture_to_remove = avl_lectures.find(((to_remove->getLectures())->find(i))->getKey());
        avl_lectures.removeVertex(lecture_to_remove);
    }
    hash_courses.removeElement(to_remove->getCourseID());
    delete (to_remove);
}

int boom::AddClass(int courseID){
    if(!hash_courses.find(courseID)) throw( Failure()); // course does not exist.
    course* course=hash_courses.find(courseID);
    int lectureID = course->addLecture();
    return lectureID;
}

void boom::WatchClass(int courseID, int classID, int time)
{
    course* the_course = hash_courses.find(courseID);
    if (the_course == NULL)
    {
        throw Failure();
    }
    lecture* the_lec = ((the_course->getLectures())->find(classID));
    if (the_lec == NULL)
    {
        throw Invalid_input();
    }
    if (the_lec->getViewTime() == 0)
    {
        the_lec->getViewTime() = time;
        avl_lectures.addVertex(the_lec,the_lec->key);
    }
    else
    {
        the_lec->getViewTime() += time;
        avl_lectures.removeVertex(avl_lectures.find(the_lec->key));
        avl_lectures.addVertex(the_lec,the_lec->key);
    }
}

lecture* boom::GetIthWatchedClass(int i)
{
    AVLnode<lecture,lectureKey>* lec = avl_lectures.findTheIRanke(i);
    if (lec == NULL)
    {
        throw Failure();
    }
    return lec->info;
}

int boom::TimeViewed(int courseID, int classID){
    if(!hash_courses.find(courseID)) throw(Failure()); // course does not exists// failure by definition
    course* course=hash_courses.find(courseID);
    if((classID+1) > course->getNumOfLectures()) throw(Invalid_input());
    hashTable<lecture>* course_lectures_hash = course->getLectures();
    lecture* lecture = course_lectures_hash->find(classID);
    return lecture->getViewTime();
}