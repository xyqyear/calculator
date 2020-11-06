#pragma once
template <typename E>
class Link
{
public:
    E element;  // Value for this node
    Link* next; // Pointer to next node in list
    // Constructors
    Link(const E& elemval, Link* nextval = NULL)
    {
        element = elemval;
        next = nextval;
    }
    Link(Link* nextval = NULL) { next = nextval; }
};

// Stack abtract class
template <typename E>
class Stack
{
private:
    void operator=(const Stack&) {} // Protect assignment
    Stack(const Stack&) {}          // Protect copy constructor
public:
    Stack() {}          // Default constructor
    virtual ~Stack() {} // Base destructor
    // Reinitialize the stack. The user is responsible for
    // reclaiming the storage used by the stack elements.
    virtual void clear() = 0;
    // Push an element onto the top of the stack.
    // it: The element being pushed onto the stack.
    virtual void push(const E& it) = 0;
    // Remove the element at the top of the stack.
    // Return: The element at the top of the stack.
    virtual E pop() = 0;
    // Return: A copy of the top element.
    virtual const E& topValue() const = 0;
    // Return: The number of elements in the stack.
    virtual int length() const = 0;
};

// Linked stack implementation
template <typename E>
class LStack : public Stack<E>
{
private:
    Link<E>* top; // Pointer to first element
    int size;     // Number of elements
public:
    LStack() // Constructor
    {
        top = NULL;
        size = 0;
    }
    ~LStack() { clear(); } // Destructor
    void clear()
    { // Reinitialize
        while (top != NULL)
        { // Delete link nodes
            Link<E>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }
    void push(const E& it)
    { // Put "it" on stack
        top = new Link<E>(it, top);
        size++;
    }
    E pop()
    { // Remove "it" from stack
        E it = top->element;
        Link<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
    }
    const E& topValue() const
    { // Return top value
        return top->element;
    }
    int length() const { return size; } // Return length
};
