//
// Created by IshimotoKiko on 2021/09/05.
//

#include <KeyBoardController.hpp>
#include <sys/time.h>

int main(){
  KeyBoardController keyBoardController;
  Observer observer;
  observer.interface(std::make_shared<ObserverInterface>());
  observer.interface()->addListener(ObserverEventList::KEYBOARD_ON_INPUT,[](SubjectData subject){
    auto msg = static_cast<UserControllerInterface::EventBody*>(subject.get());
    std::cout << "KEYBOARD_ON_INPUT "<< msg->key.debug() << std::endl;

  });
  keyBoardController.addObserver(observer);
  keyBoardController.startInputMonitoring();
  while (1){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  keyBoardController.stopInputMonitoring();

  struct timeval tv, tv0;
  struct termios t, t0;
  int c, c0 = 0;
  long ti;

  gettimeofday(&tv0, 0);
  tcgetattr(0, &t);
  t0 = t;
  t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                 | INLCR | IGNCR | ICRNL | IXON);
  t.c_oflag &= ~OPOST;
  t.c_lflag &= ~(ECHO | ECHONL | ICANON  | IEXTEN);
  t.c_cflag &= ~(CSIZE | PARENB);
  t.c_cflag |= CS8;
  tcsetattr(0, TCSANOW, &t);

  while (1) {
    c = getchar();
    gettimeofday(&tv, 0);
    ti = (tv.tv_sec - tv0.tv_sec) * 1000 + (tv.tv_usec - tv0.tv_usec) / 1000;
    if (ti < 100) break;
    tv0 = tv;
    c0 = c;
//    printf("%c\r\n", c);
  }
  printf(" %c %c\r\n", c0, c);

  tcsetattr(0, TCSANOW, &t0);
  return 0;
}