#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <algorithm> // For std::reverse


/// Operate on a sequence of DNA
class Sequence
{
public:
    struct ORF{
        QString text;
        int startpos;
        int endpos;
    };

    Sequence::Sequence();
    Sequence::Sequence( QString title , QString seq );
    Sequence::~Sequence();
    QString ToString();
    QList<ORF> mORFs;


private:
    QString title;
    QString textSequence;
    QString reverseComplement;
    QString Sequence::_calculateReverseComplement();
    void Sequence::_findORFs();

};

#endif // SEQUENCE_H
