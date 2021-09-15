//
// Created by IshimotoKiko on 2021/08/31.
//

#ifndef APPEAL_OBSERVER_HPP
#define APPEAL_OBSERVER_HPP

#include "ObserverEventList.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

namespace Design {
class Subject;
class SubjectDataBody {};
typedef std::shared_ptr<SubjectDataBody> SubjectData;
typedef std::function<void(SubjectData)> ListenerFunction;
typedef std::shared_ptr<ListenerFunction> FuncPtr;

struct ListenerEntry {
  ObserverEventList type;
  FuncPtr listener;
};

//observerのリスナーを持つクラス
//observerに委譲することで、
//リスナーを実行できる
class ObserverInterface {
  friend class Subject;

public:
protected:
  std::vector<ListenerEntry> listeners_;

public:
  virtual ~ObserverInterface();
  void addListener(ObserverEventList type, FuncPtr listener);
  void addListener(ObserverEventList type, ListenerFunction function);
  void removeListener(ObserverEventList type, FuncPtr listener);
};

//イベント観測者
//subject.addObserverで自信を登録してもらうと、
//subjectからのイベントを受信できる。
class Observer {
  friend class Subject;
  typedef std::shared_ptr<ObserverInterface> Interface;

private:
  Interface interface_;

public:
  virtual ~Observer();
  void interface(Interface interface);
  Interface interface() const { return interface_; }
};

//イベント発行者
//継承し、notifyを実行することで、
//登録しているobserversにイベントを発行できる。
class Subject {
private:
  std::vector<std::weak_ptr<ObserverInterface>> observers = {};

public:
  virtual void addObserver(Observer &observer);
  void removeObserver(Observer &observer);

  void notify(ObserverEventList type, SubjectData subjectData = nullptr);

public:
  void sweep();
};
}

#endif // APPEAL_OBSERVER_HPP
