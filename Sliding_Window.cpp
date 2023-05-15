/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int MAX_FRAMES = 100;
const int TIMEOUT = 3;

struct Frame {
    int number;
    string data;
    bool ack_received;
};

bool sendFrame(Frame frame) {
    int wait_time = rand() % 3 + 1;
    cout << "\t\t" << wait_time << ", ";

    usleep(1000000);

    usleep(1000000);

    bool ack_received = rand() % 2;

    if (ack_received) {
        cout << "Yes\t\t\tNo" << endl;
    } else {
        cout << "No\t\t\tResend" << endl;
    }

    return ack_received;
}

int main() {
    srand(time(NULL)); 

    int num_frames, window_size;
    cout << "Enter the number of frames to be transmitted: ";
    cin >> num_frames;
    cout << "Enter the window size: ";
    cin >> window_size;

    Frame frames[MAX_FRAMES];

    // Generate random data for each frame
    for (int i = 0; i < num_frames; i++) {
        // Generate random two-digit number between 10 and 99
        frames[i].number = i + 1;
        frames[i].data = to_string(rand() % 90 + 10);
        frames[i].ack_received = false;
    }

    cout << "\nFrame_No\tData\tWaiting_Time (Sec)\tAcknowledgement\tResend" << endl;

    int base = 0, next_seq_no = 0;
    while (base < num_frames) {
        // Send frames in window
        for (int i = base; i < min(base + window_size, num_frames); i++) {
            if (!frames[i].ack_received) {
                cout << "\n" << frames[i].number << "\t\t" << frames[i].data << "\t";

                // Send the frame to the receiver
                bool ack_received = sendFrame(frames[i]);

                if (ack_received) {
                    frames[i].ack_received = true;
                }

                next_seq_no++;
            }
        }

        while (base < num_frames && frames[base].ack_received) {
            base++;
        }
    }

    return 0;
}
