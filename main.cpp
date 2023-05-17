#include <QtXml>
#include <QApplication>

void traverseNode(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();

            if(!domElement.isNull())
            {
                if(domElement.tagName() == "contact")
                {
                    qDebug() << "Attr: " << domElement.attribute("number","");
                }
                else
                {
                    qDebug() << "TagName: " << domElement.tagName() << "\tText: " << domElement.text();
                }
            }
        }

        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

QDomElement makeElement(QDomDocument& domDoc,
                        const QString& strName,
                        const QString& strAttr = QString(),
                        const QString& strText = QString())
{
    QDomElement domElement = domDoc.createElement(strName);

    if(!strAttr.isEmpty())
    {
        QDomAttr domAttr = domDoc.createAttribute("number");
        domAttr.setValue(strAttr);
        domElement.appendChild(domAttr);
    }

    if(!strText.isEmpty())
    {
        QDomText domText = domDoc.createTextNode(strText);
        domElement.appendChild(domText);
    }

    return domElement;
}

QDomElement contact(QDomDocument& domDoc,
                    const QString& strName,
                    const QString& strPhone,
                    const QString& strEmail)
{
    static int nNumber = 1;

    QDomElement domElement = makeElement(domDoc,"contact",QString().setNum(nNumber));

    domElement.appendChild(makeElement(domDoc,"name","",strName));
    domElement.appendChild(makeElement(domDoc,"phone","",strPhone));
    domElement.appendChild(makeElement(domDoc,"email","",strEmail));

    nNumber++;

    return domElement;
}

int main()
{
    QDomDocument doc("addressbook");
    QDomElement domElement = doc.createElement("addressbook");
    doc.appendChild(domElement);

    QDomElement contact1 = contact(doc,"Slava",  "+7 9962479052","Slava.08ml@gmail.com");

    QDomElement contact2 = contact(doc,"Olesya", "+7 9962479615","olesya.2000sp@gmail.com");

    QDomElement contact3 = contact(doc,"Mother", "+7 9969611995","irasp2018@gmail.com");

    domElement.appendChild(contact1);
    domElement.appendChild(contact2);
    domElement.appendChild(contact3);

    QFile file("addressbook.xml");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << doc.toString();
        if(doc.setContent(&file))
        {
            QDomElement domElement2 = doc.documentElement();
            traverseNode(domElement2);
        }
        file.close();
    }

    return 0;
}
