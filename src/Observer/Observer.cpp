//
// Created by IshimotoKiko on 2021/08/31.
//

#include "Observer.hpp"

using namespace Design;

Design::ObserverInterface::~ObserverInterface() { listeners_.clear(); }

void ObserverInterface::addListener(ObserverEventList type, FuncPtr listener) {
  for (auto& entry: listeners_) {
    if (type == entry.type && listener == entry.listener) {
      return;
    }
  }
  ListenerEntry entry;
  entry.type = type;
  entry.listener = listener;
  listeners_.push_back(entry);
}
void ObserverInterface::addListener(ObserverEventList type, ListenerFunction function) {
  auto listener = std::make_shared<ListenerFunction>(function);
  for (auto& entry: listeners_) {
    if (type == entry.type && listener == entry.listener) {
      return;
    }
  }
  ListenerEntry entry;
  entry.type = type;
  entry.listener = listener;
  listeners_.push_back(entry);
}
void ObserverInterface::removeListener(ObserverEventList type, FuncPtr listener) {
  auto end = remove_if(listeners_.begin(), listeners_.end(),
                       [type, &listener](ListenerEntry& e) -> bool {
                         return (e.type == type && e.listener == listener);
                       });
  listeners_.erase(end, listeners_.end());
}

Observer::~Observer() {}

void Observer::interface(Interface interface) { interface_ = interface; }


void Subject::addObserver(Observer& observer) {
  auto tmp = std::find_if(observers.begin(), observers.end(),
                          [&](std::weak_ptr<ObserverInterface> w) {
                            return w.lock() == observer.interface();
                          });
  if (tmp == observers.end()) {
    observers.push_back(observer.interface());
  }
}
void Subject::removeObserver(Observer& observer) {
  auto iter =
      std::find_if(observers.begin(), observers.end(),
                   [&](std::weak_ptr<ObserverInterface> interface) {
                     return interface.lock() == observer.interface();
                   });
  if (iter != observers.end()) {
    observers.erase(iter);
  }
}

void Subject::notify(ObserverEventList type, SubjectData subjectData) {
  sweep();
  for (auto i: observers) {
    std::shared_ptr<ObserverInterface> interface = i.lock();
    for (auto& entry: interface->listeners_) {
      if (entry.type == type)
        (*(entry.listener))(subjectData);
    }
  }
}

void Subject::sweep() {
  observers.erase(std::remove_if(observers.begin(), observers.end(),
                                 [](std::weak_ptr<ObserverInterface> w) {
                                   return w.expired();
                                 }),
                  observers.end());
}