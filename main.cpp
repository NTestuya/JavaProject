#include <iostream>
//#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

//read file from input.txt
//read all contents in file
//form output and place it into output text
class Java2CD
{
private:
    std::fstream infile;
    std::fstream outfile;
    std::string class1,class2;
    std::string CopySTR;
public:
    Java2CD();
    ~Java2CD();
    bool OpenFile(std::string inputfilename, std::string container);
    bool DetectExtends(std::string container);
    bool DetectClasses(std::string container);
    bool ManipulateFile(std::string outputfilename, std::string container);
};
Java2CD::Java2CD()
{

}
Java2CD::~Java2CD()
{
    infile.close();
    outfile.close();
}
bool Java2CD::OpenFile(std::string inputfilename, std::string container)
{

    std::stringstream stream;
    infile.open(inputfilename.c_str()/*,  std::fstream::in | std::fstream::out*/);
    if (infile.is_open())
    {
        //reads file and places container into string
        while (!infile.eof())
        {
        getline(infile, container);
        container.insert(0, CopySTR);
        std::cout<<container <<std::endl;

        }
        if (!container.empty())
            {
                std::cout << "File opened successfully, extracted into string" << std::endl;
            }
        else
            {
                std::cout<< "There are no contents in the string." <<std::endl;
                return false;
            }
    }
    else
    {
        std::cout<< inputfilename << " file not open" << std::endl;
        infile.close();
        return false;
    }
    infile.close();
    return true;
}
/*
std::string DetectClasses(std::string container)
{
    if (container == "")
    {
        std::cout<<"String is empty" << std::endl;
        return 0;
    }

    std::string mainclass, subclass,opt;
    int pos = container.find_first_of("class");
    mainclass = container.substr(pos+1);
    int posInitclass = container.find_first_of("new");
    subclass = container.substr(posInitclass+1);
    opt = subclass + " -->" + mainclass;

    return opt;
}
*/

bool Java2CD::DetectClasses(std::string container)
{
    container=CopySTR;
    if (container.empty())
    {
        std::cout<<"String is empty" << std::endl;
        return false;
    }

    std::string mainclass, subclass,opt;
    mainclass =class1;
    subclass=class2;
    int pos = container.find_first_of("class");
    mainclass = container.substr(pos+1);
    int posInitclass = container.find_first_of("new");
    subclass = container.substr(posInitclass+1);
    opt = subclass + " -->" + mainclass;

    return true;
}
bool Java2CD::DetectExtends(std::string container)
{
    container=CopySTR;
    if (container.empty())
    {
        std::cout<<"No string detected" << std::endl;
        return false;
    }
    std::string mainclass=class2;
    std::string subclass=class1;
    std::string opt;
    int pos = container.find_first_of("extends");
    class1 = container.substr(pos+1);
    class2 = container.substr(0, pos);
    opt = class1 +"<|---"+ class2;

    return true;

}
/*
std::string DetectExtends(std::string container)
{
    if (container == "")
    {
        std::cout<<"No string detected" << std::endl;
        return 0;
    }
    std::string class1;
    std::string class2;
    std::string opt;
    int pos = container.find_first_of("extends");
    class1 = container.substr(pos+1);
    class2 = container.substr(0, pos);
    opt = class1 +"<|---"+ class2;

    return opt;

}*/
bool Java2CD::ManipulateFile(std::string outputfilename, std::string container)
{
    std::string Extends, Subclass;

    CopySTR = container;
    outfile.open(outputfilename.c_str(), std::ios::in | std::ios::out | std::ios::app );
    if (outfile.is_open())
    {
        Extends= DetectExtends(CopySTR);
        Subclass=DetectClasses(CopySTR);

        std::cout<<Extends<<std::endl;
        if (Extends.empty() || Subclass.empty())
        {
            std::cout<< "Output strings are empty" << std::endl;
            return false;
        }
        std::cout << "String successfully extracted to file"<<std::endl;
        outfile<<Extends << Subclass;

    }
    else
    {
        std::cout<< "File didn't open" << std::endl;
        outfile.close();
        return false;
    }
    outfile.close();
    return true;
}
int main()
{
    std::string holder;
    Java2CD swag;
    swag.OpenFile("JavaCodeInput.txt", holder);
    swag.ManipulateFile("output.txt", holder);
    return 0;
}
