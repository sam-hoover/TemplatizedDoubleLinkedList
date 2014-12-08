// dblLinkedList_Driver.cpp

#include <string>
#include "dblLinkedList.h"
#include "characters.h"

int main() {
	try {
		int data[3] = {1, 2, 3};
		dblLinkedList<int> DLL(data);
		dblLinkedList<double> DDLL;
		DDLL.push_back(1.1);
		DDLL.push_back(2.2);
		DDLL.push_back(3.3);
		DDLL.print();
	} catch (out_of_range e) {
		cout << "ERROR: YOU BAD!!! :: " << e.what() << '\n';
		cin.get();
		return(EXIT_FAILURE); // 1
	} catch (exception e) {
		cout << "ERROR: YOU BAD!!! :: " << e.what() << '\n';
		cin.get();
		return(EXIT_FAILURE); // 1
	}
	cin.get();
	return(0);
}