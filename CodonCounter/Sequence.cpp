#include "Sequence.h"

Sequence::Sequence(){}
Sequence::~Sequence(){}

/// Constructor that takes a title string as well as a dna sequence string
Sequence::Sequence( QString title , QString seq ) : title(title) , textSequence(seq)
{
    reverseComplement = this->_calculateReverseComplement();
    this->_findORFs(1);
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
void Sequence::_findORFs( int minimumLength )
{
    // Clear previous ORF results
    mORFs.clear();

    // Store our temporary ORF info
    bool frame_in_orf[] = { false , false , false , false , false , false }; // keep track of each frame - 0-2 = +1, +2 , +3 3-5 = -1 , -2 , -3
    ORF frame_current_orf[] = { ORF() , ORF() , ORF() , ORF() , ORF() , ORF() };

    QString neg1 = "";
    // Loop through our sequence in triplets
    int div3 = textSequence.length()/3;
    for( int i = 0; i < div3; i++ ){

        // Loop through frames
        for( int j = 0; j <= 5; j++){
            int currIndex = 0;
            QString triple = "";

            // Adjust our indexes based on whether we are using direct strand or reverse complement
            if( j < 3 ){
                currIndex = (i*3)+j;
                triple  = textSequence.mid(currIndex , 3);
            }
            else
            {
                currIndex = (i*3)+(j-3);
                triple = reverseComplement.mid(currIndex , 3);
            }

            if(frame_in_orf[j]){

                // Found STOP codon, writing ORF
                if(triple.contains(QRegExp("(TAA|TAG|TGA|taa|tag|tga)"))){
                    if( frame_current_orf[j].text.length() > 6 + minimumLength ){
                        frame_in_orf[j] = false;
                        frame_current_orf[j].endpos = currIndex+3; // frame + end of triplet
                        frame_current_orf[j].text += triple;

                        // Adjust our frame to match proper frame numbering
                        if( j < 3){
                            frame_current_orf[j].frame = j+1;
                        }
                        else
                        {
                            frame_current_orf[j].frame = -j+2;
                        }

                        mORFs.append(frame_current_orf[j]);
                        frame_current_orf[j] = ORF();
                     }
                }
                // We are in an ORF, so keep on cat-ing text
                else
                {
                    frame_current_orf[j].text += triple;
                }

            }
            else if(!frame_in_orf[j])
            {
                // We aren't in an ORF and we found a start tag, so now we are!
                if(triple.contains(QRegExp("(ATG|atg)")) ){
                    frame_in_orf[j] = true;
                    frame_current_orf[j].startpos = currIndex;
                    frame_current_orf[j].text = triple;
                }
            }
        }
    }

    qDebug() << "----------------";
    for(int k = 0; k < mORFs.length() ; k++ )
    {
        qDebug() << "ORF: " << mORFs[k].frame << " " << mORFs[k].text << " " << mORFs[k].startpos << " " << mORFs[k].endpos;
    }


}

/// Output basic sequence information to string.
QString Sequence::ToString(){
    QString s;
    s += "Title: " + this->title + "\r\n"
      + "Seq: " + this->textSequence + "\r\n"
      + "RComplement: " + this->reverseComplement + "\r\n";

    return s;
}
