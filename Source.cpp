// This is a PA3 assigned in Data Comm class Fall 2018
// Professor : Dr. Maxwell Young
// Author    : Deepak Chapagain
// Date      : 12/02/2018
//---------------------------------------------------------------//
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <random>

using namespace std;

//------------------Random Number generator---------------------
int RNG(int min, int max)
{
	int rand_int;
	rand_int = rand() % ((max + 1) - min) + min;
	//cout<<rand_int<<endl;
	return rand_int;
}//End RNG()

int firstNonRepeating(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		int j;
		for (j = 0; j<n; j++)
			if (i != j && arr[i] == arr[j])
				break;
		if (j == n)
			return arr[i];
	}// end for
	return -1;
} // end firstnonrepeating

void write_latency(int latency, int devices, char s)
{
	std::string l = std::to_string(latency);
	std::string d = std::to_string(devices);
	l = d + '\t' + l + '\n';
	//l = "Devices: " + d + '\t' + "Latency: " + l + '\n';
	char const* pchar = l.c_str();
	FILE* file;
	if (s == 'l')
	{
		file = fopen("linearLatency.txt", "a+");
	}
	else if (s == 'b')
	{
		file = fopen("binaryLatency.txt", "a+");
	}
	else
	{
		file = fopen("logLatency.txt", "a+");
	}
	fseek(file, 0, SEEK_END);
	fputs(pchar, file);
	fclose(file);
}//end write_latency

void protocol_simulator(char cmd)
{
	srand(time(NULL));
	int * window;
	int num_slots = 1;
	window = new int[num_slots];
	int * random_slot;
	int min = 0, max = 0, var =2;
	bool status = true;
	int latency = 0;
	int unsuccess = 0;
	int average = 0;
	int z = 0;

	for (int i = 5; i <= 5; i += 5)
	{
		z = i;
		while (z > 0)
		{
			for (int n = 0; n < 10; n++)
			{
				update_window:
				random_slot = new int[z];
				for (int j = 0; j < z; j++)
				{
					if(cmd=='l')
						{
							random_slot[j] = RNG(0, (max) + 1);
							max = max + 1;
						}
					else if(cmd=='b')
					{
						random_slot[j] = RNG(0, (max) + 1);
						max = max *2;
					}else
					{
						//cout<<"var: "<<var<<endl;
						var = (1+(1/log2(var)))*var;
						random_slot[j] = RNG(0, var + 1);
						max = var;
					}
				}//end for
				if (firstNonRepeating(random_slot, z) == -1)
				{
					unsuccess++;
					for (int a = 0; a <= max; a++)
					{
						latency += 1;
					}
					
					goto update_window;
				}
				if (z == 1)
				{
					average = (latency)+firstNonRepeating(random_slot, z) + 1 + average;
				}
			}//for tarils
			var=2;
			z--;

		}//while_end
			cout<<"Devices: "<<i<<endl;
			//cout << "Average Latency: " << (average / 10) << endl;
			write_latency(average / 10, i, cmd);
			cout << "------------------" << endl;
			average = 0;
			//var = 2;
		
	}//for
}
int main() 
{
	//Remove old data
	remove("linearLatency.txt");
	remove("binaryLatency.txt");
	remove("logLatency.txt");
	//call simulator
	protocol_simulator('l');
	protocol_simulator('b');
	protocol_simulator('g');
	cout<<"Done...!"<<endl;

}//main

//-------------------------------End of file--------------------