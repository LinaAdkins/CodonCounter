#include "Sequence.h"

Sequence::Sequence(){}
Sequence::~Sequence(){}

/// Constructor that takes a title string as well as a dna sequence string
Sequence::Sequence( QString title , QString seq ) : title(title) , textSequence(seq)
{
    reverseComplement = this->_calculateReverseComplement();
    this->_findORFs();
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

/// Get the positions of ORFs for this sequence by checking frames
void Sequence::_findORFs()
{
    // Our +1 , +2 , +3 , -1 , -2 , -3 frames respectively
    QString s1 , s2 , s3;
    QString r1 , r2 , r3;

    int div3 = textSequence.length()/3;
    int mod3 = textSequence.length()%3;

    for( int i = 0; i < div3; i++ ){

        // +1 , +2 , +3
        s1 += textSequence.mid(i*3 , 3) + " ";
        s2 += textSequence.mid((i*3)+1, 3) + " ";
        s3 += textSequence.mid((i*3)+2 , 3 ) + " ";

        // -1 , -2 , -3
        r1 += reverseComplement.mid(i*3 , 3) + " ";
        r2 += reverseComplement.mid((i*3)+1, 3) + " ";
        r3 += reverseComplement.mid((i*3)+2 , 3 ) + " ";



    }

    qDebug() << "s1: " + s1;
    qDebug() << "r1: " + r1;
    qDebug() << "------------------------";
    qDebug() << "s2: " + s2;
    qDebug() << "r2: " + r2;
    qDebug() << "------------------------";
    qDebug() << "s3: " + s3;
    qDebug() << "r3: " + r3;
    qDebug() << "------------------------";

}

/// Output basic sequence information to string.
QString Sequence::ToString(){
    QString s;
    s += "Title: " + this->title + "\r\n"
      + "Seq: " + this->textSequence + "\r\n"
      + "RComplement: " + this->reverseComplement + "\r\n";

    return s;
}
