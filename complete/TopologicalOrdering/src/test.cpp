#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <mutex>
using namespace boost;

std::mutex mtx;

// マルチスレッドで実行する関数
void run(int &count) {
  mtx.lock();
  for (int i = 0; i < 10000000; i++) {
    count++;
  }
  mtx.unlock();
  std::cout << "hello" << std::endl;
  std::cout << "thread:" << count << std::endl;
}
 
int main()
{
  int vnum = boost::thread::hardware_concurrency();  // 論理コア数
  int pnum = boost::thread::physical_concurrency();  // 物理コア数
  // スレッドグループの生成と実行開始
  thread_group thr_grp;
  int count = 0;
  for (int i = 0; i < pnum; ++i) {
    // create_thread()でrun()を別スレッドで実行
    thr_grp.create_thread(bind(&run, std::ref(count)));
  }
  // join_all()で全スレッドの終了を待つ
  thr_grp.join_all();
  std::cout << count << std::endl;
  return 0;
}
