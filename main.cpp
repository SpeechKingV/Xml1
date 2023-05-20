#include <QtXml>
#include <QApplication>
#include "addressbookparser.h"

int main(int argc, char *argv[])
{
    AddressBookParser handler;
    QFile file("addressbook.xml");
    QXmlInputSource source(&file);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(source);

    return 0;
}
