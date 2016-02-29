#include "Sequence.h"

Sequence::Sequence(){}
Sequence::~Sequence(){}

/// Constructor that takes a title string as well as a dna sequence string
Sequence::Sequence( QString title , QString seq ) : title(title) , textSequence(seq)
{
    reverseComplement = this->_calculateReverseComplement();
}

/// Gets the reverse complement of this DNA sequence
QString Sequence::_calculateReverseComplement(){

    QString c;

    // Map basic nucleotides to their complements
    for(int i=0; i<= textSequence.size(); i++)
    {
        // Todo: Handle probabilistic complements
        switch(textSequence[i].toLatin1()){
            case 'A':
                c += 'T';
                break;
            case 'a':
                c += 't';
                break;
            case 'T':
                c += 'A';
                break;
            case 't':
                c += 'a';
                break;
            case 'G':
                c += 'C';
                break;
            case 'g':
                c += 'c';
                break;
            case 'C':
                c += 'G';
                break;
            case 'c':
                c += 'g';
                break;
            default:
                break;
    }

    }

    // Now we reverse

    QByteArray b = c.toLatin1();
    char *d = b.data();
    std::reverse( d , d+c.length() );
    c = QString(d);

    return c;

}

/// Output basic sequence information to string.
QString Sequence::ToString(){
    QString s;
    s += "Title: " + this->title + "\r\n"
      + "Seq: " + this->textSequence + "\r\n"
      + "RComplement: " + this->reverseComplement + "\r\n";

    return s;
}
