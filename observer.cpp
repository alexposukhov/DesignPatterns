#include <iostream>
#include <string>
#include <list>

using namespace std;

class SupervisedString;
class IObserver
{
public:
    virtual void handleEvent(const SupervisedString&) = 0;
};

class SupervisedString // Observable class
{
    string _str;
    list<IObserver*> _observers;

    void _Notify()
    {
        std::list<IObserver*>::iterator it;
        for (it = _observers.begin(); it != _observers.end(); ++it)
        {
            (*it)->handleEvent(*this);
        }
    }

public:
    void add(IObserver& ref)
    {
        _observers.push_back(&ref);
    }

    void remove(IObserver& ref)
    {
        _observers.remove(&ref);
    }

    const string& get() const
    {
        return _str;
    }

    void reset(string str)
    {
        _str = str;
        _Notify();
    }
};

class Reflector: public IObserver // Prints the observed string into cout
{
public:
    virtual void handleEvent(const SupervisedString& ref)
    {
        cout << ref.get() << endl;
    }
};

class Counter: public IObserver // Prints the length of observed string into cout
{
public:
  virtual void handleEvent(const SupervisedString& ref)
  {
      cout << "length = " << ref.get().length() << endl;
  }
};

int main()
{
    SupervisedString str;
    Reflector refl;
    Counter cnt;

    str.add(refl);
    str.reset("Hello, World!");
    cout << endl;

//    str.remove(refl);
    str.add(cnt);
    str.reset("World, Hello!");
    cout << endl;

    return 0;
}
