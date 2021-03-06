//
// Created by IshimotoKiko on 2021/09/05.
//

#include "KeyBoardController.hpp"


int KeyBoardController::getCharactor(){

  termios t;
  tcgetattr(0, &t);
  t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                 | INLCR | IGNCR | ICRNL | IXON);
  t.c_lflag &= ~(ECHO  | ICANON  | IEXTEN);
  tcsetattr(0, TCSANOW, &t);
  auto ret = getchar();

  return ret;
}
void KeyBoardController::startInputMonitoring() {
  if(running)return;
  running = true;
  inputThread = std::thread([this](){
    int key;
    while (running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      key = getCharactor(); /* 入力されたキー番号 */
      auto body = std::make_shared<EventBody>();
      body->key = Key(key);
      notify(ObserverEventList::KEYBOARD_ON_INPUT,body);
    }
  });
}
bool KeyBoardController::checkInputKey(){
  // 参考
  // https://hotnews8.net/programming/tricky-code/c-code03
  // からコピーしました。
  termios oldt, newt;
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
void KeyBoardController::stopInputMonitoring()  {
  running = false;
}
KeyBoardController::~KeyBoardController(){
  inputThread.join();
  tcsetattr(0, TCSANOW, &oldt);
  //終了時、端末の入力設定を戻す。
}
