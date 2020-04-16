#include "RequestReader.h"
#include "ResponseOutput.h"

int main() {
    int turnID; Reader::readIn(turnID);
    StateContainer basicState;
    for(int i=1; i<turnID; i++) {
        Reader::readRequest(basicState);
    }
    Output::Response(basicState, Reader::readRequest(basicState));
    return 0;
}