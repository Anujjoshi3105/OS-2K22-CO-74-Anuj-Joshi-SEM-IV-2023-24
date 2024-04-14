#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
using namespace std;

class ReadersWriters
{
private:
  mutex mutex;
  sem_t write_mutex;
  int readers_count;

public:
  ReadersWriters() : readers_count(0)
  {
    sem_init(&write_mutex, 0, 1);
  }

  void start_read()
  {
    mutex.lock();
    readers_count++;
    if (readers_count == 1)
    {
      sem_wait(&write_mutex);
    }
    mutex.unlock();

    // Reading the shared resource
    cout << "Reader is reading" << endl;

    mutex.lock();
    readers_count--;
    if (readers_count == 0)
    {
      sem_post(&write_mutex);
    }
    mutex.unlock();
  }

  void start_write()
  {
    sem_wait(&write_mutex);

    // Writing to the shared resource
    cout << "Writer is writing" << endl;

    sem_post(&write_mutex);
  }
};

void reader_thread(ReadersWriters &rw, int id)
{
  while (true)
  {
    // Reading
    rw.start_read();
    // Simulating some delay for reading
    this_thread::sleep_for(chrono::milliseconds(1000));
  }
}

void writer_thread(ReadersWriters &rw, int id)
{
  while (true)
  {
    // Writing
    rw.start_write();
    // Simulating some delay for writing
    this_thread::sleep_for(chrono::milliseconds(2000));
  }
}

int main()
{
  ReadersWriters rw;

  // Creating reader threads
  thread readers[5];
  for (int i = 0; i < 5; ++i)
  {
    readers[i] = thread(reader_thread, ref(rw), i);
  }

  // Creating writer threads
  thread writers[2];
  for (int i = 0; i < 2; ++i)
  {
    writers[i] = thread(writer_thread, ref(rw), i);
  }

  // Joining threads
  for (int i = 0; i < 5; ++i)
  {
    readers[i].join();
  }
  for (int i = 0; i < 2; ++i)
  {
    writers[i].join();
  }

  return 0;
}
