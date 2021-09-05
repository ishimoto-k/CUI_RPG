//
// Created by IshimotoKiko on 2021/09/05.
//

#ifndef APPEAL_KEYBOARDCONTROLLER_HPP
#define APPEAL_KEYBOARDCONTROLLER_HPP
#include "UserControllerInterface.hpp"
#include <fcntl.h>
#include <map>
#include <termios.h>
#include <thread>

class KeyBoardController : public UserControllerInterface{
  std::thread inputThread;
  bool running = false;
public:
  KeyBoardController(){
  }
  int getCharactor(){

    termios t, t0;
    int c, c0 = 0;
    long ti;
    tcgetattr(0, &t);
    int oldf;
    t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                   | INLCR | IGNCR | ICRNL | IXON);
    t.c_lflag &= ~(ECHO  | ICANON  | IEXTEN);
    tcsetattr(0, TCSANOW, &t);
    auto ret = getchar();

    return ret;
  }
  void startInputMonitoring() override {
    if(running)return;
    running = true;
    inputThread = std::thread([this](){
      int key;
      while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        key = getCharactor(); /* 入力されたキー番号 */
        auto body = std::make_shared<EventBody>();
        body->key = Key(key);
        notify(ObserverEventList::KEYBOARD__ON_INPUT,body);
      }
    });
  }
  static int getKey(){

    termios t, t0;
    int c, c0 = 0;
    long ti;
    tcgetattr(0, &t);
    int oldf;
    t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                   | INLCR | IGNCR | ICRNL | IXON);
    t.c_lflag &= ~(ECHO  | ICANON  | IEXTEN);
    tcsetattr(0, TCSANOW, &t);
    auto ret = getchar();

    return ret;
  }
  static bool checkInputKey(){
    // 参考
    // https://hotnews8.net/programming/tricky-code/c-code03
    // からコピーしました。
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
      ungetc(ch, stdin);
      return 1;
    }

    return 0;
  }
  void stopInputMonitoring() override {
    running = false;
  }
  virtual ~KeyBoardController(){
    inputThread.join();
  }
};

#endif // APPEAL_KEYBOARDCONTROLLER_HPP
