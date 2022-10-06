#include "LinkedList.h"

#include <iostream>
#include <stdexcept>

LinkedList::LinkedList()
    : m_Head(nullptr)
{
}

LinkedList::LinkedList(const LinkedList& other)
    : LinkedList()
{
    if (other.m_Head != nullptr)
    {
        m_Head = new Node(other.m_Head->value);

        Node* currNode = m_Head;
        Node* otherNode = other.m_Head;

        while (otherNode->next != nullptr)
        {
            currNode->next = new Node(otherNode->next->value);
            currNode = currNode->next;
            otherNode = otherNode->next;
        }
    }
}

LinkedList::LinkedList(LinkedList&& other) noexcept
    : LinkedList()
{
    std::swap(m_Head, other.m_Head);
}

LinkedList::~LinkedList()
{
    delete m_Head;
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if (this != &other)
    {
        m_Head = nullptr;

        if (other.m_Head != nullptr)
        {
            m_Head = new Node(other.m_Head->value);

            Node* currNode = m_Head;
            Node* otherNode = other.m_Head;

            while (otherNode->next != nullptr)
            {
                currNode->next = new Node(otherNode->next->value);
                currNode = currNode->next;
                otherNode = otherNode->next;
            }
        }
    }

    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept
{
    if (this != &other)
        std::swap(m_Head, other.m_Head);

    return *this;
}

int& LinkedList::operator[](int index)
{
    if (index < 0 || m_Head == nullptr)
        throw std::out_of_range("Index out of range!");

    Node* currNode = m_Head;

    int i = 0;
    while (currNode != nullptr)
    {
        if (i == index)
            return currNode->value;

        currNode = currNode->next;
        i++;
    }

    throw std::out_of_range("Index out of range!");
}

const int& LinkedList::operator[](int index) const
{
    if (index < 0 || m_Head == nullptr)
        throw std::out_of_range("Index out of range!");

    Node* currNode = m_Head;

    int i = 0;
    while (currNode != nullptr)
    {
        if (i == index)
            return currNode->value;

        currNode = currNode->next;
        i++;
    }

    throw std::out_of_range("Index out of range!");
}

int* LinkedList::search(int value)
{
    Node* currNode = m_Head;

    while (currNode != nullptr)
    {
        if (currNode->value == value)
            return &currNode->value;

        currNode = currNode->next;
    }

    return nullptr;
}

const int* LinkedList::search(int value) const
{
    if (m_Head == nullptr)
        return nullptr;

    Node* currNode = m_Head;

    while (currNode != nullptr)
    {
        if (currNode->value == value)
            return &currNode->value;

        currNode = currNode->next;
    }

    return nullptr;
}

void LinkedList::insertFront(int value)
{
    Node* oldHead = m_Head;
    m_Head = new Node(value, oldHead);
}

void LinkedList::insertBack(int value)
{
    if (m_Head == nullptr)
    {
        m_Head = new Node(value);
        return;
    }

    Node* currNode = m_Head;

    while (currNode->next != nullptr)
        currNode = currNode->next;

    currNode->next = new Node(value);
}

void LinkedList::remove(int value)
{
    if (m_Head == nullptr)
        return;

    Node* currNode = m_Head;

    if (currNode->value == value)
    {
        m_Head = m_Head->next;
        currNode->next = nullptr;
        delete currNode;
        return;
    }

    while (currNode->next != nullptr)
    {
        if (currNode->next->value == value)
        {
            Node* tempNode = nullptr;
            if (currNode->next->next != nullptr)
                tempNode = currNode->next->next;

            currNode->next->next = nullptr;
            delete currNode->next;

            if (tempNode != nullptr)
                currNode->next = tempNode;

            return;
        }

        currNode = currNode->next;
    }
}

void LinkedList::sort()
{
    if (m_Head == nullptr)
        return;

    Node* currNode = m_Head;
    Node* insideNode = m_Head->next;

    if (insideNode == nullptr)
        return;

    while (currNode != nullptr && currNode->next != nullptr)
    {
        insideNode = currNode->next;

        while (insideNode != nullptr)
        {
            if (currNode->value > insideNode->value)
            {
                currNode->value ^= insideNode->value;
                insideNode->value ^= currNode->value;
                currNode->value ^= insideNode->value;
            }

            insideNode = insideNode->next;
        }

        currNode = currNode->next;
    }
}

void LinkedList::print() const
{
    Node* currNode = m_Head;

    while (currNode != nullptr)
    {
        std::cout << currNode->value << " ";
        currNode = currNode->next;
    }

}

int LinkedList::read(int index) const
{
    if (index < 0 || m_Head == nullptr)
        throw std::out_of_range("Index out of range!");

    Node* currNode = m_Head;

    int i = 0;
    while (currNode != nullptr)
    {
        if (i == index)
            return currNode->value;

        currNode = currNode->next;
        i++;
    }

    throw std::out_of_range("Index out of range!");
}
