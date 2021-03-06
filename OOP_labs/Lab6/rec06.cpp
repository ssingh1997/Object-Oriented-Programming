/*
 * Satyen Singh
  Recitation 06
  CS2124

  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
            : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    friend ostream& operator<<(ostream& os, const Directory& rhs) {
        for (size_t i = 0; i < rhs.size; ++i) {
            os << *rhs.entries[i] << endl;
        }
        return os;
    }
    // Overload output operator
public:
    Directory() : size(0), capacity(1), entries(new Entry*[1]) {}

    Directory(const Directory& rhs) {
        size = rhs.size;
        capacity = rhs.capacity;
        entries = new Entry* [capacity];
        for (size_t i = 0; i < size; ++i) {
            entries[i] = new Entry (*rhs.entries[i]);
        }


    }
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...


    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{

            capacity *= 2;
            Entry**  new_entries = new Entry* [capacity];
            for (size_t i = 0; i < size; ++i) {
                new_entries[i] = entries[i];
            }
            delete [] entries;
            entries = new_entries;
            // something is missing!!!  Add it!

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    Directory& operator=(const Directory& rhs) {
        if (this != &rhs) {
            for (size_t i = 0; i < size; ++i) {
                delete entries[i];
            }
            delete [] entries;

            size = rhs.size;
            capacity = rhs.capacity;
            entries = new Entry* [capacity];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = new Entry (*rhs.entries[i]);
            }

        }
        return *this;
    }

    unsigned operator[] (const string& name) const {
        //cout<<"here\n";
        for (size_t i = 0; i < size; ++i) {
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
        return 0000000000;
    }

    ~Directory() {
        for (size_t i = 0; i < size; ++i) {
            delete entries[i];
        }
        delete [] entries;
    }

private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d2 << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;

} // main
