#include <iostream>
#include <cassert>
#include "L3_Azoicai_Naomi_DSM.h"

///unit test for size() method
void test_size()
{   std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.printDSM();

    assert(dsm.size() == 8);
    std::cout << "Size test successful!" << std::endl;
}

///unit test for getName() method
void test_getName()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    assert(dsm.getName(1) == "one");
    std::cout << "GetName test successful!" << std::endl;
}

///unit test for setElementName() method
void test_setElementName()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.setElementName(0, "ZERO");
    assert(dsm.getName(0) == "ZERO");
    std:: cout<<"SetElementName test successful!"<< std:: endl;
    dsm.printDSM();
}

///unit test for addLink() method
void test_addLink()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.addLink("one", "two", 4);
    assert(dsm.hasLink("one", "two") == true);
    std::cout << "Add link test successful!" << std::endl;

    dsm.addLink("one", "three", 7);
    assert(dsm.hasLink("one", "three") == true);
    std::cout<<"Second add link test successful!"<< std::endl;

    dsm.printDSM();
}

///unit test for deleteLink() method
void test_deleteLink()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.addLink("one", "two", 4);

    dsm.deleteLink("one", "two");
    assert(dsm.hasLink("one", "two") == false);
    std::cout<<"Delete link test successful!"<< std::endl;
}

/// unit test for linkWeight() method
void test_linkWeight()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.addLink("one", "three", 7);

    assert(dsm.linkWeight("one", "three") == 7);
    std::cout<<"Link weight test successful!"<< std::endl;
}

///unit test for countToLinks() method
void test_countToLinks()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.addLink("one", "three", 7);

    assert(dsm.countToLinks("three") == 1);
    std::cout<<"CountToLinks test successful!"<< std::endl;
}

///unit test for countFromLinks() method
void test_countFromLinks()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.addLink("one", "two", 4);

    dsm.addLink("one", "three", 7);

    assert(dsm.countFromLinks("one") == 2);
    std::cout<<"CountFromLinks test successful!"<< std::endl;
}

///unit test for countAllLinks() method
void test_countAllLinks()
{
    std::string test_names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> dsm(test_names, 8);

    dsm.addLink("one", "two", 4);

    dsm.addLink("one", "three", 7);

    assert(dsm.countAllLinks() == 2);
    std::cout<<"CountAllLinks test successful!"<< std::endl;
}

void test_double()
{
    std::string test_names1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<float> dsm1(test_names1, 8);
    dsm1.addLink("one", "two", 4.44);
    dsm1.printDSM();

}


void testAll()
{
    test_size();
    test_getName();
    test_setElementName();
    test_addLink();
    test_deleteLink();
    test_linkWeight();
    test_countToLinks();
    test_countFromLinks();
    test_countAllLinks();
    test_double();

}

void myDSM()
{

    std::string names[] = {"primer", "concealer", "foundation", "powder", "bronzer", "blush", "highlighter", "mascara", "gloss", "mattifying spray"};
    DSM<int> dsm1(names,10);

    dsm1.printDSM();

    dsm1.addLink("concealer", "primer", 10);
    dsm1.addLink("foundation", "primer", 10);
    dsm1.addLink("powder", "primer", 10);
    dsm1.addLink("bronzer", "primer", 10);
    dsm1.addLink("blush", "primer", 10);
    dsm1.addLink("highlighter", "primer", 10);

    dsm1.addLink("foundation", "concealer", 7);
    dsm1.addLink("powder", "concealer", 7);
    dsm1.addLink("bronzer", "concealer", 7);
    dsm1.addLink("blush", "concealer", 7);
    dsm1.addLink("highlighter", "concealer", 7);
    dsm1.addLink("mattifying spray", "concealer", 7);

    dsm1.addLink("powder", "foundation", 7);
    dsm1.addLink("bronzer", "foundation", 5);
    dsm1.addLink("blush", "foundation", 5);
    dsm1.addLink("highlighter", "foundation", 5);
    dsm1.addLink("mattifying spray", "foundation", 7);

    dsm1.addLink("bronzer", "powder", 5);
    dsm1.addLink("blush", "powder", 5);
    dsm1.addLink("highlighter", "powder", 5);
    dsm1.addLink("mattifying spray", "powder", 7);

    dsm1.addLink("bronzer", "bronzer", 5);
    dsm1.addLink("highlighter", "bronzer", 5);
    dsm1.addLink("mattifying spray", "bronzer", 7);

    dsm1.addLink("bronzer", "blush", 5);
    dsm1.addLink("highlighter", "blush", 5);
    dsm1.addLink("mattifying spray", "blush", 7);

    dsm1.addLink("bronzer", "highlighter", 5);
    dsm1.addLink("blush", "highlighter", 5);
    dsm1.addLink("mattifying spray", "highlighter", 7);

    dsm1.addLink("mattifying spray", "mascara", 10);

    dsm1.addLink("mattifying spray", "gloss", 10);


    dsm1.printDSM();
}

//void test_writeToFile()
//{
//    std::string test_names1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
//    DSM<int> matrix(test_names1, 8);
//    matrix.addLink("one", "two", 4);
//    std::string fileName = "print.txt";
//    bool success = matrix.writtenToFile(fileName);
//    assert(success);
//
//    std::cout<<"bravo1!";
//    matrix.writtenToFile(test_names1, 8, "print.txt");
//    assert(matrix.writtenToFile(test_names1, 8, "print.txt")==true);
//    std::cout<<"bravo2!";
//}


void demo()
{
    std::string test_names1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    DSM<int> matrix(test_names1, 8);

    string fromElement, toElement;
    int weight;

    std::cout << "Enter the name of the fromElement: ";
    std::cin >> fromElement;

    std::cout << "Enter the name of the toElement: ";
    std::cin >> toElement;

    std::cout << "Enter the weight: ";
    std::cin >> weight;

    matrix.addLink(fromElement, toElement, weight);
    //std::cout<<matrix.hasLink(fromElement, toElement);

    std::cout<<"The count of to-links is ";
    std::cout<<matrix.countToLinks(toElement)<<std::endl;

    std::cout<<"The count of from-links is ";
    std::cout<<matrix.countFromLinks(fromElement)<<std::endl;

    std::cout<<"The count of all links is ";
    std::cout<<matrix.countAllLinks()<<std::endl;

    std::cout<<"The matrix looks like this: "<<std::endl;
    matrix.printDSM();

}

int main() {
    testAll();
    //test_writeToFile();
    myDSM();
    demo();
    return 0;

}