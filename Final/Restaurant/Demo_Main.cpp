//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"


int main()
{
	/*Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	delete pRest;*/
	List<int> L;
	L.insert(0,1);
	L.insert(1,5);
	Node<int>* ptr=L.getHead();
	while(ptr)
	{
		cout<<ptr->getItem()<<" ";
		ptr=ptr->getNext();
	}

	system("pause");	
	return 0;
}
