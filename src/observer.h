/**
 * Observer pattern implementation for string type
 *
 * @file: observer.h
 * @date: 18.02.2023
 */

#ifndef IPKCPC_OBSERVER_H
#define IPKCPC_OBSERVER_H

#include <vector>
#include <functional>

/**
 * Events namespace
 *
 * @namespace events
 */
namespace events {
    /**
     * Observer class
     * Class for observing subject. It is used in observer pattern.
     * It is used for notifying observers about changes in subject.
     *
     * @class Observer
     */
    class Observer {
    protected:
        /** @var callback Callback function */
        std::function<void(const char *)> &callback;

    public:
        /**
         * Constructor
         *
         * @param callback Callback function
         */
        explicit Observer(std::function<void(const char *)> &callback);

        /**
         * Update method. It is called when subject notifies about changes.
         * @param subject Subject of the observer
         */
        void update(const char *subject);
    };

    /**
     * Subject class
     * Class for notifying observers about changes.
     *
     * @class Subject
     */
    class Subject {
    protected:
        /** @var observers List of observers */
        std::vector<Observer *> *observers;

    public:
        /**
         * Constructor
         */
        Subject();

        /**
         * Destructor
         */
        ~Subject();

        /**
         * Attach observer to the subject
         *
         * @param observer Observer to be attached
         */
        void attach(Observer &observer);

        /**
         * Detach observer from the subject
         *
         * @param observer Observer to be detached
         */
        void detach(Observer &observer);

        /**
         * Notify observers about changes
         *
         * @param message Message to be sent to observers
         */
        void notify(const char *message);
    };
}// namespace events

#endif// IPKCPC_OBSERVER_H
