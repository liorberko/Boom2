#ifndef LECTUREKEY_H
#define LECTUREKEY_H

struct lectureKey
{
    int lectureID;
    int courseID;
    int viewTime;
    lectureKey(int lectureID, int courseID, int viewTime) : lectureID(lectureID), courseID(courseID), viewTime(viewTime){}
    ~lectureKey() = default;
    bool operator==(const lectureKey& target) const;
    bool operator<(const lectureKey& target) const;
    bool operator>(const lectureKey& target) const;
};

#endif /* LECTUREKEY_H*/