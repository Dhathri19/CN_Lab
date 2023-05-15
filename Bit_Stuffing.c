#include <stdio.h>

int main()
{
    printf("\t\t\tBIT STUFFING\n\n");
    int n;
    printf("Enter the value of N: ");
    scanf("%d",&n);
    
    int arr[n];
    int temp[100];
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    
    int j = 0;
    
    int count = 0;
    
    for(int i = 0; i < n; i += 1)
    {
        if(arr[i] == 1)     //only if the value is 1 do we need to check for the consecutive ones otherwise just assign
        {
            count = 1;      //we've already encountered a 1 in the array
            
            temp[j] = arr[i];       //copying from the input array to the output array
            
            for(int k = i + 1; arr[k] == 1 && k < n && count < 5; k++)
            {
                j += 1;
                temp[j] = arr[i];       //copying from the input array to the output array
                count += 1;
                
                if(count == 5)
                {
                    j += 1;
                    temp[j] = 0;
                }
                
                i = k;
            }
        }
        
        else
        {
            temp[j] = arr[i];
        }
        
        j += 1;
    }
    
    for(int i = 0; i < j; i++)
    {
        printf("%d ", temp[i]);
    }
}
