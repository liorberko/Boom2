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
    lecture* lecture2 = new lecture(1,1,3);
    lecture* lecture3 = new lecture(2,1,0);
    lecture* lecture4 = new lecture(3,1,15);
    lecture* lecture5 = new lecture(4,2,2);
    lecture* lecture6 = new lecture(5,2,1);
    lecture* lecture7 = new lecture(5,2,0);
    lecture* lecture8 = new lecture(5,3,15);
    lecture* lecture9 = new lecture(5,4,15);
    lecture* lecture10 = new lecture(0,3,0);
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
    tester = rankTree->addVertex(lecture7,lecture7->getKey());
    if(tester == false) return -7;
    std::cout<<"inserting lecture 8"<< std::endl;
    tester = rankTree->addVertex(lecture8,lecture8->getKey());
    if(tester == false) return -8;
    std::cout<<"inserting lecture 9"<< std::endl;
    tester = rankTree->addVertex(lecture9,lecture9->getKey());
    std::cout<<"inserting lecture 7"<< std::endl;
    if(tester == false) return -9;
    std::cout<<"inserting lecture 10"<< std::endl;
    tester = rankTree->addVertex(lecture10,lecture10->getKey());
    if(tester == false) return -10;
    std::cout<<"removing root"<< std::endl;
    AVLnode<lecture,lectureKey>* root = rankTree->find(lecture5->getKey());
    rankTree->removeVertex(root);
    std::cout<<"The 8ths :"<< std::endl;
    AVLnode<lecture,lectureKey>* the8 = rankTree->findTheIRanke(8);
    std::cout<< *(the8->info) << std::endl;
    std::cout<<"Start printing tree :"<< std::endl;
    rankTree->printTree();
    return 0;
}