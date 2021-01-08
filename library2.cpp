#include "library2.h"
#include "boom.h"


void *Init(){
    try{
        boom *DS=new boom();
        return (void*)DS;
    }
    catch(...){
        return NULL;
    }
}

StatusType AddCourse(void* DS, int courseID){
    if(courseID <=0 || DS==nullptr) return INVALID_INPUT;
    try{
        ((boom*)DS)->AddCourse(courseID);
    }
    catch (Allocation_Error T)
    {
        return ALLOCATION_ERROR;
    }
    catch (Invalid_input T)
    {
        return INVALID_INPUT;
    }
    catch (Failure T)
    {
        return FAILURE;
    }
    catch(...){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType RemoveCourse(void *DS, int courseID){
    if((courseID <=0)|| (DS == NULL)) return INVALID_INPUT;
    try{
        ((boom*)DS)->RemoveCourse(courseID);
    }
    catch (Allocation_Error T)
    {
        return ALLOCATION_ERROR;
    }
    catch (Invalid_input T)
    {
        return INVALID_INPUT;
    }
    catch (Failure T)
    {
        return FAILURE;
    }
    catch(...){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddClass(void* DS, int courseID, int* classID)
{
    if ((DS == NULL) || (courseID <= 0)) return INVALID_INPUT;
    try
    {
        *classID = ((boom*)DS)->AddClass(courseID);
    }
    catch (Allocation_Error T)
    {
        return ALLOCATION_ERROR;
    }
    catch (Invalid_input T)
    {
        return INVALID_INPUT;
    }
    catch (Failure T)
    {
        return FAILURE;
    }
    catch(...){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if(courseID <=0 || classID <0 || time<=0 || DS==nullptr) return INVALID_INPUT;
    try{
       ((boom*)DS)->WatchClass(courseID,classID,time);
    }
    catch (Allocation_Error T)
    {
        return ALLOCATION_ERROR;
    }
    catch (Invalid_input T)
    {
        return INVALID_INPUT;
    }
    catch (Failure T)
    {
        return FAILURE;
    }
    catch(...){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    if (DS==NULL || courseID<=0 || classID<0 ) return INVALID_INPUT;
    if (timeViewed == nullptr)
    {
        return INVALID_INPUT;
    }
    try{
        int temp= ((boom*)DS)->TimeViewed(courseID , classID);
        *timeViewed = temp;   
    }
    catch (Allocation_Error T)
    {
        return ALLOCATION_ERROR;
    }
    catch (Invalid_input T)
    {
        return INVALID_INPUT;
    }
    catch (Failure T)
    {
        return FAILURE;
    }
    catch(...){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID){
    if (DS==NULL || i<=0) return INVALID_INPUT;
    try{
        lecture* res = ((boom*)DS)->GetIthWatchedClass(i);
        if (res == NULL) return FAILURE;
        *courseID = res->getCourseID();
        *classID = res->getLectureID();
    }
    catch (Allocation_Error T)
    {
        return ALLOCATION_ERROR;
    }
    catch (Invalid_input T)
    {
        return INVALID_INPUT;
    }
    catch (Failure T)
    {
        return FAILURE;
    }
    catch(...){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS)
{
    boom* to_delet = (boom*)(*DS);
    delete (to_delet);
    (*DS) = NULL;
}