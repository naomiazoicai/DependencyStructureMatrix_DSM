#include "L3_Azoicai_Naomi_DSM.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
template class DSM<bool>;
template class DSM<int>;
template class DSM<float>;
template class DSM<double>;


/// Default constructor of templated class DSM
/// \tparam Type
/// \param elementCount
template<typename Type>
DSM<Type>::DSM(int elementCount) :elementCount(elementCount), capacity(elementCount*2 + 1)
{
    if (elementCount < 0)
    {
        throw std::invalid_argument("Element count cannot be negative");
    }

    matrix = new Type*[capacity];
    //this->elementCount = elementCount;
    //elementNames = new string[elementCount];
    for (int row = 0;  row < capacity;  row++)
    {
        matrix[row] = new Type[capacity];
        //initialize the matrix with no links
        for (int column = 0; column < capacity; column++)
        {
            matrix[row][column] = 0;
        }
    }
    //allocate space for the elementNames array
    elementNames = new string[capacity];
}

/// Constructor with two parameters of templated class DSM
/// \tparam Type
/// \param elementNames
/// \param elementCount
template<typename Type>
DSM<Type>::DSM(string *_elementNames, int elementCount): elementCount(elementCount), capacity(elementCount * 2 + 1)
{
    if (elementCount < 0)
    {
        throw std::invalid_argument("Element count cannot be negative");
    }

    matrix = new Type*[capacity];

    for (int row = 0;  row < capacity;  row++)
    {
        matrix[row] = new Type[capacity];
        for (int column = 0; column < capacity; column++)
        {
            matrix[row][column] = 0;
        }
    }
    //allocate space for the elementNames array
    elementNames = new string[capacity];

    for (int row = 0; row < elementCount; row++)
    {
        //fill the elementNames Array
        elementNames[row] = _elementNames[row];
    }
}

/// Resize the matrix array to a new capacity
/// \tparam Type
/// \param newCapacity
template<typename Type>
void DSM<Type>::resizeMatrix(int newCapacity)
{
    if (newCapacity < this->elementCount)
    {
        throw std::out_of_range("Index out of range");
    }

    auto *newMatrix = new Type *[newCapacity];
    for (int row = 0; row < newCapacity; row++)
    {
        newMatrix[row] = new Type[newCapacity];
        for (int column = 0; column < newCapacity; column++)
        {
            if (row < this->elementCount && column < this->elementCount)
            {
                //copying the old elements
                newMatrix[row][column] = matrix[row][column];
            }
            else
            {
                //set weight 0 for the new elements
                newMatrix[row][column] = 0;
            }
        }
    }

    //deallocate matrix
    for (int row = 0; row < this->elementCount; row++)
    {
        delete[] matrix[row];
    }
    delete[] matrix;
    matrix = newMatrix;
    capacity = newCapacity;
}

/// resize method for the elementNames array
/// \tparam Type
/// \param newCapacity
template<typename Type>
void DSM<Type>::resizeElementNames(int newCapacity)
{
    if (newCapacity < this->elementCount)
    {
        throw std::out_of_range("Index out of range");
    }
    auto *newArray = new string[newCapacity];
    for (int row = 0; row < this->elementCount; row++)
    {
        newArray[row] = elementNames[row];
    }
    delete[] elementNames;
    elementNames = newArray;
    capacity = newCapacity;
}

/// method for matrix and elementNames resize
/// \tparam Type
template<typename Type>
void DSM<Type>::automaticResize()
{
    if (this->elementCount >= this->capacity)
    {
        //resize up
        resizeElementNames(capacity * 2);
        resizeMatrix(capacity * 2);
    }
    else if (this->elementCount <= this->capacity / 4 && this->capacity >= 10)
    {
        //resize down
        resizeElementNames(capacity / 2);
        resizeMatrix(capacity / 2);
    }
}


/// returns the size of the dsm
/// \tparam Type
/// \return
template<typename Type>
int DSM<Type>::size()
{
    return elementCount;
}

///getter method for the element at a certain index
/// \tparam Type
/// \param index
/// \return
template<typename Type>
string DSM<Type>::getName(int index)
{
    if (index >= 0 && index < this->elementCount)
    {
        return elementNames[index];
    }
    throw std::out_of_range("Invalid index!!!");
}

///setter method for the element at a certain index
/// \tparam Type
/// \param index
/// \param elementName
template<typename Type>
void DSM<Type>::setElementName(int index, string elementName)
{
    if (index >= 0 && index < this->elementCount)
    {
        elementNames[index] = elementName;
    }

}

/// getter method for index
/// \tparam Type
/// \param str
/// \return
template<typename Type>
int DSM<Type>::getIndex(const string &str)
{
    for (int index = 0; index < this->elementCount; index++)
    {
        if (elementNames[index] == str)
        {
            return index;
        }
    }
    return -1;  // element not found in DSM
}

/// adds a link between two elements in the dsm
/// \tparam Type
/// \param fromElement
/// \param toElement
/// \param weight
template<typename Type>
void DSM<Type>::addLink(const string &fromElement, const string &toElement, Type weight)
{
    //check if fromElement and toIndex is in the DSM
    int fromIndex = getIndex(fromElement);
    int toIndex = getIndex(toElement);

    if(fromIndex == -1)
    {
        elementNames[elementCount] = fromElement;
        fromIndex = elementCount;
        elementCount++;
        automaticResize();
    }

    if(toIndex == -1)
    {
        elementNames[elementCount] = toElement;
        toIndex = elementCount;
        elementCount++;
        automaticResize();
    }
        //add link to matrix
    matrix[fromIndex][toIndex] = weight;
}

/// deletes the link between two specified elements in the DSM
/// \tparam Type
/// \param fromElement
/// \param toElement
template<typename Type>
void DSM<Type>::deleteLink(const string& fromElement, const string& toElement)
{
    int fromIndex = -1, toIndex = -1;

    //loop through each row of the DSM
    for (int row = 0; row < this->elementCount;  row++)
    {
        //if the current element is the fromElement, set fromIndex to the current row index
        if (elementNames[row] == fromElement)
        {
            fromIndex = row;
        }

        //if the current element is the toElement, set toIndex to the current row index
        if (elementNames[row] == toElement)
        {
            toIndex = row;
        }
    }

    //if both fromIndex and toIndex were found, set the corresponding value in the matrix to 0
    if (fromIndex != -1 && toIndex != -1)
    {
        matrix[fromIndex][toIndex] = 0;
    }
}


/// returns true if there is a link between two specified elements in the DSM, otherwise false
/// \tparam Type
/// \param fromElement
/// \param toElement
/// \return
template<typename Type>
bool DSM<Type>::hasLink(const string& fromElement, const string& toElement)
{
    int fromIndex = -1, toIndex = -1;

    //iterate through the element names in the DSM
    for (int row = 0; row < this->elementCount;  row++)
    {
        //if the current element name matches the starting element, set fromIndex to the current row
        if (elementNames[row] == fromElement)
        {
            fromIndex = row;
        }

        //if the current element name matches the ending element, set toIndex to the current row
        if (elementNames[row] == toElement)
        {
            toIndex = row;
        }
    }

    //if both starting and ending indexes have been set, and the matrix element at those indexes is not zero, return true
    if (fromIndex != -1 && toIndex != -1 && matrix[fromIndex][toIndex] != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// returns the weight of the link between two specified elements in the DSM
/// \tparam Type
/// \param fromElement
/// \param toElement
/// \return
template<typename Type>
int DSM<Type>::linkWeight(const string& fromElement, const string& toElement) {
    int fromIndex = -1, toIndex = -1;
    for (int index = 0; index < this->elementCount;  index++)
    {
        //loop through all the rows of the DSM matrix and check if the current row's element name matches the "from" element name
        if (elementNames[index] == fromElement)
        {
            //if it matches, store the row index
            fromIndex = index;
        }

        //check if the current rows element name matches the "to" element name
        if (elementNames[index] == toElement)
        {
            //if it matches, store the row index
            toIndex = index;
        }
    }
    if (fromIndex != -1 && toIndex != -1)
    {
        //if both the "from" and "to" elements were found, return the weight of the link between the elements
        return matrix[fromIndex][toIndex];
    }
    else
    {
        //if one or both elements were not found
        return -1;
    }
}

//the column is from where the relation comes, and the row is where it goes
///returns the number of "to"-links
/// \tparam Type
/// \param elementName
/// \return
template<typename Type>
int DSM<Type>::countToLinks(const string& elementName)
{
    int count = 0;
    int index = -1;

    for (int column = 0; column < this->elementCount;  column++)
    {
        //loop through all the rows of the DSM matrix and check if the element name matches the current row's name
        if (elementNames[column] == elementName)
        {
            //if it matches, store the row index
            index = column;
            break;
        }
    }
    //if the element was found
    if (index != -1)
    {
        for (int row = 0; row < this->elementCount; row++)
        {
            //loop through all the columns of the DSM matrix and check if the current element in the DSM matrix is linked
            if (matrix[row][index] != 0)
            {
                //if it is, increment the count of links
                count++;
            }
        }
    }
    return count;
}



///returns the number of "from"-links
/// \tparam Type
/// \param elementName
/// \return
template<typename Type>
int DSM<Type>::countFromLinks(const string& elementName)
{
    int count = 0;
    int index = -1;
    for (int row = 0; row < this->elementCount;  row++)
    {
        //loop through all the rows of the DSM matrix and check if the element name matches the current row's name
        if (elementNames[row] == elementName)
        {
            //if it matches, store the row index
            index = row;
            break;
        }
    }
    //if the element was found
    if (index != -1)
    {
        //loop through all the columns of the DSM matrix and check if the current element in the DSM matrix is linked
        for (int column = 0; column < this->elementCount; column++)
        {
            if (matrix[index][column] != 0)
            {
                //if it is, increment the count of links
                count++;
            }
        }
    }
    return count;
}


/// returns the total number of links in the DSM
/// \tparam Type
/// \return
template<typename Type>
int DSM<Type>::countAllLinks()
{
    this->elementCount = elementCount;
    int count = 0;
    for (int row = 0; row < this->elementCount;  row++)
    {
        for (int column = 0; column < this->elementCount; column++)
        {
            //if the matrix element is not 0, there is a link
            if (matrix[row][column] != 0)
            {
                count++;
            }
        }
    }
    return count;
}


//
//template<typename Type>
//void DSM<Type>::printDSM() {
//        std::cout << "  ";
//
//    //loop through the elementNames array and print each element's name
//    for (int row = 0; row < this->elementCount;  row++)
//    {
//        std::cout << elementNames[row] << " ";
//    }
//        std::cout << std::endl;
//
//    //loop through each row in the matrix
//    for (int row = 0; row < this->elementCount;  row++)
//        {
//            //print the element name for the current row
//            std::cout << elementNames[row] << " ";
//
//            //loop through each column in the current row and print its corresponding value in the matrix
//            for (int column = 0; column < this->elementCount; column++)
//            {
//                std::cout << matrix[row][column] << " ";
//            }
//            std::cout << std::endl;
//        }
//    }

/// prints the dsm
/// \tparam Type
template<typename Type>
void DSM<Type>::printDSM()
{
    const int fieldWidth = 10;
    const char borderChar = '-';
    const char verticalChar = '|';

    //print the column headers
    std::cout << std::setw(fieldWidth) << ' ';
    for (int i = 0; i < this->elementCount; i++)
    {
        std::cout << std::setw(fieldWidth) << elementNames[i];
    }
    std::cout << std::endl;

    //print the top border
    std::cout << std::setfill(borderChar) << std::setw((fieldWidth + 1) * (elementCount + 1)) << "" << std::endl;

    //print the matrix
    for (int row = 0; row < this->elementCount; row++)
    {
        std::cout << std::setfill(' ') << std::setw(fieldWidth) << elementNames[row] << verticalChar;
        for (int column = 0; column < this->elementCount; column++)
        {
            std::cout << std::setw(fieldWidth) << matrix[row][column];
        }
        std::cout << std::endl;
    }

    //print the bottom border
    std::cout << std::setfill(borderChar) << std::setw((fieldWidth + 1) * (elementCount + 1)) << "" << std::endl;
}


/// destructor to free up memory
/// \tparam Type
template<typename Type>
DSM<Type>::~DSM()
{
    for (int row = 0;  row < this->elementCount;  row++)
    {
        delete[] matrix[row];
    }
    delete[] matrix;
    delete[] elementNames;
}

/// copy-constructor
/// \tparam Type
/// \param other
template<typename Type>
DSM<Type>::DSM(const DSM<Type>& other): elementCount(other.elementCount), capacity(other.capacity)
{
    //elementCount = other.elementCount;
    matrix = new Type*[capacity];
    elementNames = new string[capacity];

    for (int row = 0; row < elementCount; row++)
    {
        matrix[row] = new Type[elementCount];
        for (int column = 0; column < elementCount; column++)
        {
            matrix[row][column] = other.matrix[row][column];
        }
        elementNames[row] = other.elementNames[row];
    }
}

/// assignment operator
/// \tparam Type
/// \param other
/// \return
template<typename Type>
DSM<Type>& DSM<Type>::operator=(const DSM<Type>& other)
{
    if (this != &other)
    {
        DSM<Type> temp(other);          // create a temporary object using the copy constructor
        std::swap(matrix, temp.matrix);
        std::swap(elementNames, temp.elementNames);
        std::swap(elementCount, temp.elementCount);
        std::swap(capacity, temp.capacity);
    }
    return *this;
}


//template<typename Type>
//void DSM<Type>::writeToFile(string *elementNames, int _elementCount, const string& fileName)
//{
//    bool printed = false;
//    std::ofstream outFile;
//    outFile.open(fileName);
//
//    Type **matrix = getDSM();  //pointer to dsm
//
//    for (int row = 0; row < elementCount; row++)
//    {
//        for (int column = 0; column < elementCount; column++)
//        {
//            outFile<<elementNames[row]<<","<<matrix[row][column]<<","<<elementNames[column]<<std::endl;
//            printed = true;
//        }
//    }
//
//    outFile.close();
//}
//
//template<typename Type>
//bool DSM<Type>::writtenToFile(const string fileName)
//{
//    //const string fileName = "print.txt";
//    std::ofstream outFile;
//    outFile.open(fileName);
//    if (!outFile.is_open())
//    {
//        return false;
//    }
//
//    string fromElement, toElement;
//    int weight;
//
//    for (int row = 0; row < this->elementCount; ++row)
//    {
//        fromElement = elementNames[row];
//        for (int column = 0; column < this->elementCount; ++column)
//        {
//            if (row != column)
//            {
//                outFile << elementNames[row] << "," << matrix[row][column] << "," << elementNames[column] << std::endl;
//            }
//        }
//    }
//    outFile.close();
//    return true;
//}

//template<typename Type>
//Type ** DSM<Type>::getDSM() { return matrix;}