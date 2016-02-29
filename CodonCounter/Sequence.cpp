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

    // Keep states for gene parsing
    bool s1_inORF = false;

    // Store our temporary ORF info
    ORF s1_ORF; ORF s2_ORF; ORF s3_ORF;

    int div3 = textSequence.length()/3;

    for( int i = 0; i < div3; i++ ){

        // +1 , +2 , +3
        QString f1 = textSequence.mid(i*3 , 3);

        // Actions for when we are in a potential orf
        if(s1_inORF){

            // Since we thought we were already in an ORF and we've hit a start codon, clear our orf stats for now.
            if(f1 == "ATG"){
                s1_ORF.text = "";
                s1_ORF.startpos = i*3;
            }
            else if(f1.contains(QRegExp("(TAA|TAG|TGA|taa|tag|tga)")) ){
                s1_inORF = false;
                s1_ORF.endpos = i*3+3;

                qDebug() << "ORF: " + s1_ORF.text + " startpos: " + QString::number(s1_ORF.startpos) + " endpos: " + QString::number(s1_ORF.endpos);
            }
            else{
                s1_ORF.text  += f1 + " ";
            }
        }
        else if( !s1_inORF ){
            if(f1.contains(QRegExp("(ATG|atg)")) ) {
                s1_inORF = true;
                s1_ORF.startpos = i*3;
                qDebug() << "FOUND ATG TAG!";
            }
        }

       /* s1 += textSequence.mid(i*3 , 3) + " ";
        s2 += textSequence.mid((i*3)+1, 3) + " ";
        s3 += textSequence.mid((i*3)+2 , 3 ) + " ";

        // -1 , -2 , -3
        r1 += reverseComplement.mid(i*3 , 3) + " ";
        r2 += reverseComplement.mid((i*3)+1, 3) + " ";
        r3 += reverseComplement.mid((i*3)+2 , 3 ) + " ";*/



    }

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
