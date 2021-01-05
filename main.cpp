#include "course.h"
#include "AVLtree.h"
#include "AVLnode.h"
#include "lecture.h"
#include "lectureKey.h"
#include "hashTable.h"
#include <iostream>


int main()
{
    
    lecture* lecture1 = new lecture(0,1,0);
    lecture* lecture2 = new lecture(1,1,50);
    lecture* lecture3 = new lecture(2,1,100);
    lecture* lecture4 = new lecture(3,1,150);
    lecture* lecture5 = new lecture(4,2,200);
    lecture* lecture6 = new lecture(5,2,400);
    AVLtree<lecture,lectureKey>* rankTree = new AVLtree<lecture,lectureKey>();
    std::cout<<"inserting lecture 1"<< std::endl;
    bool tester = rankTree->addVertex(lecture1,lecture1->getKey());
    if(tester == false) return -1;
    std::cout<<"inserting lecture 2"<< std::endl;
    tester = rankTree->addVertex(lecture2,lecture2->getKey());
    if(tester == false) return -2;
    std::cout<<"inserting lecture 3"<< std::endl;
    tester = rankTree->addVertex(lecture3,lecture3->getKey());
    if(tester == false) return -3;
    std::cout<<"inserting lecture 4"<< std::endl;
    tester = rankTree->addVertex(lecture4,lecture4->getKey());
    if(tester == false) return -4;
    std::cout<<"inserting lecture 5"<< std::endl;
    tester = rankTree->addVertex(lecture5,lecture5->getKey());
    if(tester == false) return -5;
    std::cout<<"inserting lecture 6"<< std::endl;
    tester = rankTree->addVertex(lecture6,lecture6->getKey());
    if(tester == false) return -6;
    rankTree->printTree();
    return 0;
}