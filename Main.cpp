#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

void parse_node(xml_node<> *node = NULL);

int main(int argc, char **argv)
{
    std::string fileName(".NET Framework 4.6.xml");
    ifstream is(fileName);
    stringstream ss;
    ss << is.rdbuf();
    std::string xml = ss.str();

    char *pContent = new char[xml.length() + 1];
    memset(pContent, 0, xml.length() + 1);
    memcpy(pContent, xml.c_str(), xml.length());
    xml_document<> doc;    // character type defaults to char
    doc.parse<0>(pContent);    // 0 means default parse flags

    xml_node<> *node = doc.first_node();
    
    //parse document recursively
    parse_node(node);

    return 0;
}

void parse_node(xml_node<> *node )
{
    if ( NULL == node)
    {
        return;
    }
    //parse self
    cout << "************    name=" << node->name() << " ";
    if ( node_data == node->type() )
    {
        cout << "value=" << node->value();
    }
    cout << endl;
    //parse attributes
    for (xml_attribute<> *attr = node->first_attribute();
        attr; attr = attr->next_attribute())
    {
        cout << "attribute name=" << attr->name() << " ";
        cout << "value=" << attr->value() << endl;
    }
    //parse brothers
    if ( node->next_sibling() )
    {
        parse_node(node->next_sibling());
    }
    //parse children
    if ( node->first_node())
    {
        parse_node(node->first_node());
    }
}