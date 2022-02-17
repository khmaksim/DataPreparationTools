#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton {
    public:
        static T& instance() {
            static T instance;
            return instance;
        }

    private:
        Singleton();
        Singleton(const Singleton &);
        Singleton& operator=(const Singleton &);
        ~Singleton();
};

#endif // SINGLETON_H
