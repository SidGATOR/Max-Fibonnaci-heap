#include "hashtagcounter.h"
#include "maxHASHfib.h"

int value_extractor(string input)
{
	int position,end;
	char strKEY[20];
	string::size_type sz;
	end = input.length();
	size_t eofKEY;
	if(input.find(' ') != string::npos)
	{
	   position = input.find(' ');
	   eofKEY = input.copy(strKEY,end-position,position+1);
	}
	else
	{
	   position = 0;
	   eofKEY = input.copy(strKEY,end-position,position);
	}
	strKEY[eofKEY] = '\0';
	int key = stoi(strKEY, &sz);
	return key;
}

string key_extractor(string input)
{
	int position,end;
	position = input.find(' ');
	input.resize(position);
	return input;

}

int main(int argc, char **argv)
{
	node* p;
	string line;
	char *file = argv[1];
	ifstream hashtagTable (file);
	std::unordered_map<std::string, node*> hm;
	node *E;
	E = retHEADnode();
	remove("output.txt"); //Interim file
	remove("finalO.txt"); //Final output
	if(hashtagTable.is_open())
	{
	  while( getline(hashtagTable,line))
	  {
		if(line.find(' ') != string::npos)
		{
		  if(line[0] == '#')
		  {
		    int value = value_extractor(line);
			string key = key_extractor(line);
			//Check if the Key,Value pair exists in hashmap
			if(hm.find(key) != hm.end())
			{
				
				node* address;
				node* updateE;
				address = hm[key];
				int key_to_increase = address->key;
				increaseKEY(E, address, key_to_increase, value);
			//	displayTREE(E);

			}
			//Insert new nodes//
			else
			{
				p = createNODE(value);
				node* address = p;
				hm[key] = address;
				E = insertNODE(E, p);
			//	displayTREE(E);	
			}
		  }
		}
		//Check if reached end of file//
		else if(line[0] == 's' || line[0] == 'S')
		{
			remove("output.txt");
			cout<<"Completed..."<<endl;
			exit(1);
		}
		else
		{
		  remove("output.txt");
		  ofstream finP ("finalO.txt", ios::app);
		  int value = value_extractor(line);
		  node *maxPUSH[value];
		  ifstream outP ("output.txt");
		  outP.is_open();
		  //Perform removeMAX operation as many times read from the file//
		  for(int i =0;i<value;i++)
		  {
			//If values to remove are more that the nodes in the heap
			if(E == NULL)
			{
				string inPKEY;
				outP.is_open();
				int i =0;
				while(getline(outP, inPKEY))
				{
					p = createNODE((maxPUSH[i])->key);
					p->child = NULL;
					p->degree = 0;
					node* address = p;
					hm[inPKEY] = address;
					E = insertNODE(E, p);
		//			displayTREE(E);
					i++;
				}
				outP.close();
				remove("output.txt");
				break;
			}

			//Remove the maximum node and insert into output and finalO file. output file is used for reinsertion into heap
			maxPUSH[i] = removeMAX(E);
			std::unordered_map<std::string, node*>::iterator it;
			node* hashVALUE = (maxPUSH[i]);
			string hashKEY;
			
			for(it=hm.begin();it!=hm.end();++it)
			{
				if((it->second)== hashVALUE)
				{
					hashKEY = it->first;
					break;
				}
			}
			ofstream outP ("output.txt", ios::app);
			outP.is_open();
			finP.is_open();
			if(outP.is_open())
			{
				outP << hashKEY <<"\n";	
				finP << hashKEY.substr(1,string::npos) <<",";	
			}
		    E = retHEADnode();	
		//	displayTREE(E);
		}
		finP <<endl;
		outP.close();
		finP.close();

		//Reinsert the nodes removed back into the heap//
		string inPKEY;
		ifstream inP ("output.txt");
		inP.is_open();
		int i =0;
		while(getline(inP, inPKEY))
		{
			p = createNODE((maxPUSH[i])->key);
			p->child = NULL;
			p->degree = 0;
			node* address = p;
			hm[inPKEY] = address;
			E = insertNODE(E, p);
		//	displayTREE(E);
			i++;
		}
		inP.close();
		}

		
	  }
	hashtagTable.close();
	}
	else
	{
		cout<<"Unable to read"<<endl;
	}
return 0;

}

