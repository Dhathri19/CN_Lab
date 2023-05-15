
#include <iostream>

using namespace std;

string xorfinder(string encoded , string divs)							
{
    int divslen = divs.length();
    
    for (int i = 0 ; i <= (encoded.length() - divslen); )			
    {															
        for( int j=0 ; j < divslen ; j++)								
        {
            encoded[i+j] = encoded[i+j] == divs[j] ? '0' : '1' ;			
        }
    for( ; i< encoded.length() && encoded[i] != '1' ; i++) ;
    
    }
    
    return encoded;
}

int main()
{
    int n, p;
    string divs, data, encoded;
    cout << "Enter the number of bits in input data: ";
    cin >> n;
    
    cout << "Enter the number of bits in the polynomial generator: ";
    cin >> p;
    
    cout << "Enter the data: ";
    cin >> data;
    
    cout << "Enter the divisor: ";
    cin >> divs;
    
    encoded += data;	

    // Append p-1 zeros to the input data
    for (int i = 0; i < p - 1; i++) {
        encoded += '0';		
    }
    
    encoded = xorfinder(encoded , divs);	

    cout<<"CRC value: ";
	cout<<encoded.substr(encoded.length() - p + 1)<<endl;					
	
	cout<<"Transmitted data: ";
	cout<<data + encoded.substr(encoded.length() - p + 1)<<endl;    					
	
    string msg;	
    
    cout << "Enter the received data: ";
    cin >> msg;
	
	msg = xorfinder(msg , divs);											
	
	for( char i : msg.substr(msg.length() - p + 1))					
		if( i != '0' )
			{	
				cout<<"Error in communication "<<endl;						
			}
	
	cout<<"No Error !"<<endl;											

    return 0;
}


