//Ayman Wahbani 209138155
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;


unsigned int countSpaces(const string &s) { // counts white spaces in a thread
    	unsigned int counter = 0;
    	for (unsigned int i = 0; i < s.size(); ++i)  /* for (char c: s) */
        	if (s[i] == ' ')	/* if (c == ' ')*/
        	    counter++;
	return counter;
}

char **convertStringsToArray(const string &s, const string &proc) { // converts from a string to a array of strings using space seperation
	unsigned int counter = countSpaces(s);
	stringstream sstream(s);  string temp;
    	char **array = new char *[counter + 2];
    
    	array[counter + 1] = (char *)0;
    	array[0] = new char[proc.length()];
    	strncpy(array[0], proc.c_str(), proc.length());

    	counter = 1;
    	while (sstream.good()){
		sstream >> temp;
        	array[counter] = new char[temp.length()];
        	strncpy(array[counter], temp.c_str(), temp.length());
        	counter++;
    	}
	return array;
}


void commond(const string &procName, char** cargs, vector<pid_t> & jobs){
	int status;	
	pid_t pid = fork(),wite;
        if (pid == 0) {
            if (execv(procName.c_str(), cargs)) {
              	perror("Execv Error"); exit(-1);
            }
        }
        else {
		if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1) {
	                perror("waitpid"); exit(-1);
	            }
            	if (WIFEXITED(status) && WEXITSTATUS(status) != 255) {
                	jobs.push_back(cpid);
                	cout << "The PID of " << procName << " is " << pid << "\n";
            	}
	}
}
int main(int argc, char *argv[]) {
	string input,procName;
	size_t pos = input.find(" ");
  	int status;
    	vector<pid_t> jobs;
    	char **cargs = nullptr;

    	cout << "*************************************************************************"<<endl;
    	cout << "***** Ayman's shell *****"<<endl;
    	cout << "Write like this: pathname param"<<endl;
    	cout << "Example : [/bin/ls -l] or [/bin/ls] or [/bin/gedit] ...."<<endl;
    	cout << "If we want see the history; write 'jobs'"<<endl; 
    	cout << "*************************************************************************"<<endl;

    	while (1) {
		cout << " >> " ;
        	getline(std::cin, input);
		if (input.compare("jobs") == 0) {
            	for (unsigned int i = 0; i < jobs.size(); ++i)
                	std::cout << i + 1 << "\t" << jobs[i] << "\n";
            		continue;
        	}
        	if (pos != string::npos){
            		procName = input.substr(0, pos);
            		cargs = convertStringsToArray(input.substr(pos + 1), procName);
        	}
        	else {
            		procName = input;
            		cargs = new char *[2];
            		cargs[0] = new char[procName.length()];
            		strncpy(cargs[0], procName.c_str(), procName.length());            
			cargs[1] = (char*) 0; // cargs[ 1 ] =NULL;
        	}
		commond(procName,cargs,jobs);
	}    
	return 0;
}
