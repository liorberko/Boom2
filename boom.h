#ifndef BOOM_H
#define BOOM_H
#include "lecture.h"
#include "AVLnode.h"
#include "AVLtree.h"
#include "exceptions.h"
#include "course.h"
#include "hashTable.h"

class boom
{
private:
    hashTable<course> hash_courses;
    AVLtree<lecture, lectureKey> avl_lectures;
    int class_counter;
public:
    boom()=default;

    ~boom();

    void AddCourse(int courseID);

    void RemoveCourse(int courseID);

    int AddClass(int courseID);

    void WatchClass(int courseID, int classID, int time);

    lecture* GetIthWatchedClass(int i);

    int TimeViewed(int courseID, int classID);

};

#endif /* BOOM_H */