#ifndef _RANDOM_MAP_H_
#define _RANDOM_MAP_H_

#include <unordered_map>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

class RandomMap
{

public:
    RandomMap() { _size = 0; }
    ~RandomMap(){};

    void insert(string str)
    {
        if (_mapStringIndex.find(str) == _mapStringIndex.end())
        {
            //插入的时候，两个map都插入
            _mapStringIndex[str] = _size;
            _mapIndexString[_size] = str;
            _size++;
        }
    }

    string getRandom()
    {
        //产生一个随机数
        int index = rand() % _size; //产生一个 0 ~ _size - 1 之间的数
        //返回_mapIndexString中的数据
        return _mapIndexString[index];
    }

    void del(string delString)
    {
        auto it = _mapStringIndex.find(delString);
        if (it == _mapStringIndex.end())
            return;
        int delIndex = _mapStringIndex[delString];
        //把下标最大的string，maxIndexString替换过来

        //下标delIndex对应的字符串改成 maxIndexString
        _mapIndexString[delIndex] = _mapIndexString[_size - 1];

        //maxIndexString的下标改成 delIndex
        _mapStringIndex[_mapIndexString[_size - 1]] = delIndex;

        //删除
        _mapIndexString.erase(_size - 1);
        _mapStringIndex.erase(delString);
        _size--;
    }

private:
    unordered_map<string, int> _mapStringIndex;
    unordered_map<int, string> _mapIndexString;
    int _size;
};

#endif