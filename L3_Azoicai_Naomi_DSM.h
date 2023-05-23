#ifndef LAB3_OOP_L3_AZOICAI_NAOMI_DSM_H
#define LAB3_OOP_L3_AZOICAI_NAOMI_DSM_H

#endif //LAB3_OOP_L3_AZOICAI_NAOMI_DSM_H
#pragma once
#include <string>
using std::string;

template<typename Type>     //define a template class DSM, where Type can be any data type
class DSM{
private:
    Type **matrix;      // a 2D array (matrix) of Type data type
    string *elementNames;
    int elementCount;
    int capacity;

public:
    /// Default constructor of templated class DSM
    /// \tparam Type
    /// \param elementCount
    explicit DSM(int elementCount);

    /// Constructor with two parameters of templated class DSM
    /// \tparam Type
    /// \param elementNames
    /// \param elementCount
    DSM(string *_elementNames, int _elementCount);

    /// copy-constructor
    /// \tparam Type
    /// \param other
    DSM(const DSM &other);

    /// destructor to free up memory
    /// \tparam Type
    ~DSM();

    /// returns the size of the dsm
    /// \tparam Type
    /// \return
    int size();

    ///getter method for the element at a certain index
    /// \tparam Type
    /// \param index
    /// \return
    string getName(int index);


    ///setter method for the element at a certain index
    /// \tparam Type
    /// \param index
    /// \param elementName
    void setElementName(int index, string elementName);

    /// adds a link between two elements in the dsm
    /// \tparam Type
    /// \param fromElement
    /// \param toElement
    /// \param weight
    void addLink(const string& fromElement, const string& toElement, Type weight);

    /// deletes the link between two specified elements in the DSM
    /// \tparam Type
    /// \param fromElement
    /// \param toElement
    void deleteLink(const string& fromElement, const string& toElement);

    /// returns true if there is a link between two specified elements in the DSM, otherwise false
    /// \tparam Type
    /// \param fromElement
    /// \param toElement
    /// \return
    bool hasLink(const string& fromElement, const string& toElement);

    /// returns the weight of the link between two specified elements in the DSM
    /// \tparam Type
    /// \param fromElement
    /// \param toElement
    /// \return
    int linkWeight(const string& fromElement, const string& toElement);

    ///returns the number of "to"-links
    /// \tparam Type
    /// \param elementName
    /// \return
    int countToLinks(const string& elementName);

    ///returns the number of "from"-links
    /// \tparam Type
    /// \param elementName
    /// \return
    int countFromLinks(const string& elementName);

    /// returns the total number of links in the DSM
    /// \tparam Type
    /// \return
    int countAllLinks();

    /// prints the dsm
    /// \tparam Type
    void printDSM();


    /// getter method for index
    /// \tparam Type
    /// \param str
    /// \return
    int getIndex(const string &str);


    /// Resize the matrix array to a new capacity
    /// \tparam Type
    /// \param newCapacity
    void resizeMatrix(int newCapacity);


    /// resize method for the elementNames array
    /// \tparam Type
    /// \param newCapacity
    void resizeElementNames(int newCapacity);

    /// method for matrix and elementNames resize
    /// \tparam Type
    void automaticResize();

    //void writeToFile(string *elementNames, int _elementCount, const string& fileName);

    //Type **getDSM();

    //bool writtenToFile(const string fileName);

    /// assignment operator
    /// \tparam Type
    /// \param other
    /// \return
    DSM<Type>& operator=(const DSM<Type>& other);

};



