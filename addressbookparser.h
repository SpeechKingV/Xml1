#ifndef ADDRESSBOOKPARSER_H
#define ADDRESSBOOKPARSER_H
#include <QString>
#include <QXmlAttributes>
#include <QDebug>

class AddressBookParser : public QXmlDefaultHandler
{
private:

    QString m_strText;

public:

    bool startElement(const QString&,
                      const QString&,
                      const QString&,
                      const QXmlAttributes& attrs
                      );
    bool EndElement(const QString&,
                      const QString&,
                      const QString& str)
    {
        if( str != "contact" && str != "addressbook")
        {
            qDebug() << "TagName: " << str
                     << "\tText: "  << m_strText;
        }

    }

    bool characters(const QString& strText)
    {
        m_strText = strText;

        return true;
    }

    bool fatalError(const QXmlParseException& exception);

};

bool startElement(const QString&,
                  const QString&,
                  const QString&,
                  const QXmlAttributes& attrs
                  )
{
    for (int i = 0; i < attrs.count(); i++ )
    {
        if(attrs.localName(i) == "number")
        {
            qDebug() << "Attr:" << attrs.value(i);
        }

    }
    return true;

}

bool fatalError(const QXmlParseException& exception)
{
    qDebug() << "Line: " << exception.lineNumber()
             << ";/tColumn: " << exception.columnNumber()
             << ";/tMessage: " << exception.message();
    return false;
}

#endif // ADDRESSBOOKPARSER_H
