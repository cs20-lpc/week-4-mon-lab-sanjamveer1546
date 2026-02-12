#include "LinkedList.hpp"
#include <string>

template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &copyObj)
    : head(nullptr)
{
    copy(copyObj);
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rightObj)
{
    if (this != &rightObj)
    {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
void LinkedList<T>::append(const T &elem)
{
    Node *n = new Node(elem);

    if (head == nullptr)
    {
        head = n;
    }
    else
    {
        Node *curr = head;

        while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        curr->next = n;
    }

    this->length++;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node *prev = nullptr;

    while (head != nullptr)
    {
        prev = head;
        head = head->next;
        delete prev;
    }

    this->length = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T> &copyObj)
{
    // start as empty
    head = nullptr;
    this->length = 0;

    // if source is empty, done
    if (copyObj.head == nullptr)
    {
        return;
    }

    // copy first node
    head = new Node(copyObj.head->value);
    Node *currNew = head;
    Node *currSrc = copyObj.head->next;

    // copy remaining nodes
    while (currSrc != nullptr)
    {
        currNew->next = new Node(currSrc->value);
        currNew = currNew->next;
        currSrc = currSrc->next;
    }

    this->length = copyObj.length;
}

template <typename T>
T LinkedList<T>::getElement(int position) const
{
    if (position < 0 || position >= this->length)
    {
        throw string("getElement: error, position out of bounds");
    }

    Node *curr = head;

    for (int i = 0; i < position; i++)
    {
        curr = curr->next;
    }

    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const
{
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T &elem)
{
    // valid insert positions: [0, length]
    if (position < 0 || position > this->length)
    {
        throw string("insert: error, position out of bounds");
    }

    // insert at head
    if (position == 0)
    {
        head = new Node(elem, head);
        this->length++;
        return;
    }

    // find node before insertion position
    Node *prev = head;
    for (int i = 0; i < position - 1; i++)
    {
        prev = prev->next;
    }

    prev->next = new Node(elem, prev->next);
    this->length++;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position)
{
    // valid remove positions: [0, length-1]
    if (position < 0 || position >= this->length)
    {
        throw string("remove: error, position out of bounds");
    }

    Node *victim = nullptr;

    // remove head
    if (position == 0)
    {
        victim = head;
        head = head->next;
    }
    else
    {
        // find node before victim
        Node *prev = head;
        for (int i = 0; i < position - 1; i++)
        {
            prev = prev->next;
        }

        victim = prev->next;
        prev->next = victim->next;
    }

    delete victim;
    this->length--;
}

template <typename T>
void LinkedList<T>::replace(int position, const T &elem)
{
    if (position < 0 || position >= this->length)
    {
        throw string("replace: error, position out of bounds");
    }

    Node *curr = head;

    for (int i = 0; i < position; i++)
    {
        curr = curr->next;
    }

    curr->value = elem;
}

template <typename T>
ostream &operator<<(ostream &outStream, const LinkedList<T> &myObj)
{
    if (myObj.isEmpty())
    {
        outStream << "List is empty, no elements to display.\n";
    }
    else
    {
        typename LinkedList<T>::Node *curr = myObj.head;
        while (curr != nullptr)
        {
            outStream << curr->value;
            if (curr->next != nullptr)
            {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
