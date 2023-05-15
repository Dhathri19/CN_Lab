/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int MAX_FRAMES = 10;
const int TIMEOUT = 3;

// Structure for a frame
struct Frame {
    int number;
    string data;
};

// Function to simulate sending a frame
bool sendFrame(Frame frame) {
    // Generate a random wait time
    int wait_time = rand() % 3 + 1;
    cout << "\t\t" << wait_time << ", ";

    // Simulate transmission delay
    usleep(1000000);

    // Simulate acknowledgement delay
    usleep(1000000);

    // Simulate acknowledgement loss
    bool ack_received = rand() % 2;

    // Print acknowledgement result
    if (ack_received) {
        cout << "Yes\t\t\tNo" << endl;
    } else {
        cout << "No\t\t\tResend" << endl;
    }

    return ack_received;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int num_frames;
    cout << "Enter the number of frames to be transmitted: ";
    cin >> num_frames;

    Frame frames[MAX_FRAMES];

    // Generate random data for each frame
    for (int i = 0; i < num_frames; i++) {
        // Generate random two-digit number between 10 and 99
        frames[i].number = i + 1;
        frames[i].data = to_string(rand() % 90 + 10);
    }

    cout << "\nFrame_No\tData\tWaiting_Time (Sec)\tAcknowledgement\tResend" << endl;

    // Transmit each frame and wait for acknowledgement
    for (int i = 0; i < num_frames; i++) {
        bool ack_received = false;
        int resend_count = 0;

        while (!ack_received && resend_count < 3) {
            cout << "\n" << frames[i].number << "\t\t" << frames[i].data << "\t";

            // Send the frame to the receiver
            ack_received = sendFrame(frames[i]);

            // Resend the frame if acknowledgement not received
            if (!ack_received) {
                resend_count++;
                cout << frames[i].number << " (Resend " << resend_count << ")";
            }
        }
    }

    return 0;
}
