
#include <string>
#include <iostream>

class Screen {
public:
    // interface member functions
    typedef std::string::size_type index;
    char get() const { return contents[cursor]; }
    inline char get(index ht, index wd) const;
    Screen(index ht = 0, index wd = 0):
       contents(ht * wd, ' '), cursor(0), height(ht), width(wd) { }
    Screen& move(index r, index c);
    Screen& set(char);
    Screen& set(index, index, char);
    // display overloaded on whether the object is const or not
    Screen& display(std::ostream &os)
                  { do_display(os); return *this; }
    const Screen& display(std::ostream &os) const
                  { do_display(os); return *this; }
private:
     // single function to do the work of displaying a Screen,
     // will be called by the display operations
     void do_display(std::ostream &os) const
                       { os << contents; }
    // as before
private:
    std::string contents;
    index cursor;
    index height, width;
    // other members as before
};

Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

Screen& Screen::move(index r, index c)
{
    index row = r * width; // row location
    cursor = row + c;
    return *this;
}

Screen& Screen::set(index r, index c, char ch)
{
    index row = r * width; // row location
    contents[row + c] = ch;
    return *this;
}

char Screen::get(index r, index c) const
{
    index row = r * width; // row location
    return contents[row + c];
}

