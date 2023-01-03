#include "vector.hpp"
#include <string>
using std::cout;
using std::endl;
int _ratio = 1000;


#define TESTED_TYPE int
#define TESTED_NAMESPACE ft


int main() 
{
	ft::vector<int>vector;
	ft::vector<int> v;
	ft::vector<int> tmp;
	tmp.assign(2600 * _ratio, 1);
	vector.assign(4200 * _ratio, 7);
	vector.insert(vector.begin(), tmp.begin(), tmp.end());
	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector[i]);
	}
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	for(size_t i = 0; i < v.size(); i++)
		cout << v.at(i) << " ";
	cout << endl;

	/*ft::vector<std::string> vct(8);
	ft::vector<std::string> vct2;
	ft::vector<std::string>::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);

	std::cout << "push_back():\n" << std::endl;
	vct.push_back("One long string");
	vct2.push_back("Another long string");

	cout << vct.size() << endl;
	cout << vct2.size() << endl;
*/

    /*ft::vector<int> alice;
	alice.push_back(1);
	alice.push_back(2);
	alice.push_back(3);

    ft::vector<int> bob;
	
    bob.push_back(8);
	bob.push_back(9);
	bob.push_back(10);
	ft::vector<int> eve;
	eve.push_back(1);
	eve.push_back(2);
	eve.push_back(3);

	
	for (int i = 0; i < 3; i++){
		cout << "eve: " << eve[i] << " bob: " << bob[i] << endl;
	}
	//eve.swap(bob);
	cout << "after swap" << endl;
	for (int i = 0; i < 3; i++){
		cout << "eve: " << eve[i] << " bob: " << bob[i] << endl;
	}

    std::cout << std::boolalpha;

    // Compare non equal containers
    std::cout << "alice == bob returns " << (alice == bob) << '\n';
    std::cout << "alice != bob returns " << (alice != bob) << '\n';
    std::cout << "alice <  bob returns " << (alice < bob) << '\n';
    std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns " << (alice > bob) << '\n';
    std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

    std::cout << '\n';

    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << '\n';
    std::cout << "alice != eve returns " << (alice != eve) << '\n';
    std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    std::cout << "alice >= eve returns " << (alice >= eve) << '\n';*/


	/*std::vector<int>x(10);
	ft::vector<int> b(10);

	for (int i = 0; i < 10; i++){
		b[i] = i;
	}
	ft::vector<int> a(b.begin(), b.end());
	ft::vector<int> c(a);
	ft::vector<int> t(10);
	t.insert(t.begin(), a.begin(), a.end());

	a.erase(a.begin(), a.begin() + 4);
	ft::vector<int>::iterator start;
	ft::vector<int>::iterator stop;

	start = a.begin();
	stop = a.end();

	while(start != stop)
		cout << *start++ << endl;

	try{
		cout << a.at(11) << endl;
	}
	catch (std::exception &e){
		cout << e.what() << endl;
	}



	for (size_t i = 0; i < a.size(); i++)
		cout << ": '"<< a[i] << "' ";
	cout << endl;
	for (size_t i = 0; i < b.size(); i++)
		cout << ": '" << b[i] << "' ";
	cout << endl;
	for (size_t i = 0; i < c.size(); i++)
		cout << ": '" << c[i] << "' ";
	cout << endl;
	system("leaks ft_vector");*/
}