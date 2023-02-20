/**
 * Observer pattern implementation for string type
 *
 * @file: observer.cpp
 * @date: 18.02.2023
 */

#include "observer.h"

namespace events {
    Observer::Observer(std::function<void(const std::string &)> &callback) : callback(callback) {}

    void Observer::update(const std::string &subject) { callback(subject); }

    Subject::Subject() { this->observers = new std::vector<Observer *>(); }

    Subject::~Subject() {
        for (auto observer: *this->observers) { delete observer; }
        delete this->observers;
    }

    void Subject::attach(events::Observer &observer) { this->observers->push_back(&observer); }

    void Subject::detach(events::Observer &observer) {
        this->observers->erase(std::remove(this->observers->begin(), this->observers->end(), &observer),
                               this->observers->end());
    }

    void Subject::notify(const std::string &message) {
        for (auto observer: *this->observers) { observer->update(message); }
    }
}// namespace events