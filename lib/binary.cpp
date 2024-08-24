#include<set>
#include<vector>
#include<math.h>
#include<stdio.h>
#include<fstream>

int getIndex(int element, std::set<int> alphabet);
std::vector<int> binaryReadSeq(std::ifstream& in, int len, std::set<int> alphabet);
void binaryWritePSD(std::ofstream& out, std::vector<double> psd, int bound);
void binaryWriteSeq(std::ofstream& out, std::vector<int> seq, std::set<int> alphabet);

int getIndex(int element, std::set<int> alphabet) {
    int i = 0;
    for(int num : alphabet) {
        if(num == element) {
            return i;
        }
        i++;
    }

    return -1;
}

std::vector<int> binaryReadSeq(std::ifstream& in, int len, std::set<int> alphabet) {
    std::vector<int> seq;

    std::vector<int> index_alphabet;
    for(int element : alphabet) {
        index_alphabet.push_back(element);
    }

    if(alphabet.size() > 256) {
        //TODO: write the case for compression factors > 256 (only possible for order v >= 128)
        printf("ERROR: alphabet size is larger than 256. Edge case not written yet.\n");
    } else {

        //TODO: make sure the last padded byte is accounted for
        const int bits_per_element = (int)ceil(log(alphabet.size()));
        const int elements_per_byte = 8 / bits_per_element;
        const int bytes = (int)ceil(len * bits_per_element / 8.0);
        for(int i = 0; i < bytes; i++) {
            char byte;
            in.get(byte);

            int decimal = (int)byte;

            for(int j = 0; j < elements_per_byte && seq.size() < len; j++) {
                int index = decimal % alphabet.size(); 

                decimal = decimal / alphabet.size();

                seq.push_back(index_alphabet[index]);
            }
        }
    }
    return seq;
}

void binaryWritePSD(std::ofstream& out, std::vector<double> psd, int bound) {
    const int bits_per_psd = (int)ceil(log(bound));

    if(bits_per_psd > 8) {
        //TODO: write the case for bound > 256 (only possible for order v >= 128)
    } else {
        for(size_t i = 0; i < psd.size(); i++) {
            out << (char)rint(psd[i]);
        }
    }
}

void binaryWriteSeq(std::ofstream& out, std::vector<int> seq, std::set<int> alphabet) {

    if(alphabet.size() > 256) {
        //TODO: write the case for compression factors > 256 (only possible for order v >= 128)
        printf("ERROR: alphabet size is larger than 256. Edge case not written yet.\n");
    } else {
        const int bits_per_element = (int)ceil(log(alphabet.size()));
        const int elements_per_byte = 8 / bits_per_element;
        //Pad the sequence so that the below loop will write the last byte
        while(seq.size() % elements_per_byte != 0) {
            seq.push_back(*alphabet.begin());
        }

        std::vector<int> subseq;

        //TODO: Make sure the loop prints the last few elements of the sequence
        for(size_t i = 0; i < seq.size(); i++) {
            subseq.push_back(seq[i]);

            if(subseq.size() == elements_per_byte) {
                int byte = 0;

                for(size_t j = 0; j < subseq.size(); j++) {
                    byte += getIndex(subseq[j], alphabet) * (int)pow(alphabet.size(), j);
                }
                out << (char)byte;

                subseq.clear();
            }
        }
    }

}