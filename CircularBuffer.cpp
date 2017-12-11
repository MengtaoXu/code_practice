/*
Implementing a circular buffer
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <stdexcept>

template <typename T>
class CircularBuffer {
  public:
    CircularBuffer(std::size_t size):m_size(size),m_head(0),m_tail(0) {
      m_buffer.reserve(size);
    }
    T pop() {
      if (m_head == m_tail) {
        throw std::runtime_error("Queue is empty!");
      }
      else {
        T tmp = m_buffer[m_head];
        m_head = (m_head+1)%(m_size+1);
      }
    }
    void push(const T &t){
      if(isfull()) {
        throw std::runtime_error("Queue is full!");
      }
      else {
        m_buffer[m_tail] = t;
        m_tail= (m_tail+1)%(m_size+1);
      }
    }
    friend std::ostream& operator <<(std::ostream &os, const CircularBuffer<T> &c) {
      for (std::size_t i = c.m_head; i != c.m_tail; i = (i+1)%(c.m_size+1) ) {
        os << c.m_buffer[i] << std::endl;
      }
      return os;
    }
  private:
    std::size_t m_head, m_tail;
    std::size_t m_size;
    std::vector<T> m_buffer;
    
    bool isfull() {
      return (m_head+m_size)%(m_size+1) == m_tail;
    }
};


int main () {
  CircularBuffer<std::string> c(3);
  c.push("abc");
  c.push("d");
  c.push("f");
  std::cout << c << std::endl;
}

