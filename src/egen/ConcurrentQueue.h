#ifndef CONCURRENTQUEUE_H_
#define CONCURRENTQUEUE_H_

/* Header created: 2011-07-06

  egen - Erik's generic library
  Copyright (C) 2011 Erik Åldstedt Sund

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  To contact the author, e-mail at erikalds@gmail.com or through
  regular mail:
    Erik Åldstedt Sund
    Darres veg 14
    NO-7540 KLÆBU
    NORWAY
*/

#include <boost/optional.hpp>

#include <atomic>

/// This should be set somehow else, but must be set at compile time...
#define CACHE_LINE_SIZE 64

//---
// Which version of g++ is being used?
//---
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

//---
// The new C++ keyword nullptr is not present in 4.5.x and earlier.
//---
#if GCC_VERSION < 40600
#  ifndef nullptr
#    define nullptr (NULL)
#  else
#    error nullptr defined somewhere as a MACRO. You need to fix it.
#  endif
#endif

namespace egen
{
  /// Generalized concurrent FIFO queue.
  ///
  /// It is based on C++11 atomic.
  ///
  /// Based on "Writing a Generalized Concurrent Queue", by Herb
  /// Sutter, October 29, 2008, Dr. Dobb's Journal,
  /// http://drdobbs.com/cpp/211601363.
  template<typename T>
  class ConcurrentQueue
  {
  public:
    /// Create an empty queue.
    ConcurrentQueue()
    {
      m_first = m_last = new Node(nullptr);
      m_producer_lock = m_consumer_lock = false;
    }

    ~ConcurrentQueue()
    {
      while (m_first != nullptr)
      {
        Node* tmp = m_first;
        m_first = tmp->m_next;
        delete tmp->m_value;
        delete tmp;
      }
    }

    /// Push an item \c t on the queue.
    ///
    /// This member function is called Produce in Sutter's implementation.
    ///
    /// \param t The value to be placed in the back of the queue.
    void push_back(const T& t)
    {
      Node* tmp = new Node(new T(t));
      while (m_producer_lock.exchange(true)) {}  // acquire exclusivity
      m_last->m_next = tmp;  // publish to consumers
      m_last = tmp;  // swing last forward
      m_producer_lock = false;  // release exclusivity
    }

    /// Pop the front item off of the queue.
    ///
    /// This member function is called Consume in Sutter's implementation.
    ///
    /// \return The value that was at the front of the queue, or an
    /// uninitialized optional value if the queue is empty.
    boost::optional<T> pop_front()
    {
      while (m_consumer_lock.exchange(true)) {}  // acquire exclusivity

      Node* the_first = m_first;
      Node* the_next = m_first->m_next;
      if (the_next != nullptr)  // if queue is nonempty
      {
        T* val = the_next->m_value;  // take it out
        the_next->m_value = nullptr;  // of the Node
        m_first = the_next;  // swing first forward
        m_consumer_lock = false;  // release exclusivity

        boost::optional<T> result(*val);  // copy value
        delete val;  // clean up the value
        delete the_first;  // ... and the old dummy
        return result;  // ... and report success and return value in same op
      }

      m_consumer_lock = false;  // release exclusivity
      return boost::optional<T>();  // ... and report empty queue
    }

  private:
    /// Internal node of the singly linked list.
    struct Node
    {
      Node(T* val) : m_value(val), m_next(nullptr) {}

      T* m_value;
      std::atomic<Node*> m_next;
      char pad[CACHE_LINE_SIZE - sizeof(T*) - sizeof(std::atomic<Node*>)];
    };

    char pad0[CACHE_LINE_SIZE];

    // for one consumer at a time
    Node* m_first;
    char pad1[CACHE_LINE_SIZE - sizeof(Node*)];

    // shared among consumers
    std::atomic<bool> m_consumer_lock;
    char pad2[CACHE_LINE_SIZE - sizeof(atomic<bool>)];

    // for one producer at a time
    Node* m_last;
    char pad3[CACHE_LINE_SIZE - sizeof(Node*)];

    // shared among producers
    std::atomic<bool> m_producer_lock;
    char pad4[CACHE_LINE_SIZE - sizeof(atomic<bool>)];
  };

} // namespace egen

#endif // CONCURRENTQUEUE_H_
