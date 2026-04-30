#pragma once
#include <iostream>
#include <vector>

template <typename T>
class RingBuffer
{
private:
    std::vector<T> data; // 고정 크기 배열 (capacity 만큼 미리 확보)
    int capacity; // 최대 저장 가능 항목 수
    int head; // 다음 위치
    int count; // 현재 저장된 항목 수
public:
    RingBuffer(int capacity) : data(capacity), capacity(capacity), head(0), count(0) {}
    
    void push(const T& value)
    {
        data[head] = value;
        head = (head + 1) % capacity; // 끝에 도달하면 0으로 순환
        if (count < capacity) count++;
    }
    
    void printAll() const
    {
        int start = (count < capacity) ? 0 : head;
        for (int i = 0; i < count; i++)
        {
            int index = (start + i) % capacity;
            std::cout << data[index];
        }
    }
    
    int size() { return count; }
    int empty() { return count == 0; }
};
